"""Findings -> CWE mapping (extends v1 ``data_preprocessing.py``).

Keeps v1's token -> CWE mapping for the static analyzers verbatim (so v1
and v2 numbers stay comparable) and adds mappings for the NEW dynamic
channel findings (ASan/UBSan error kinds and oracle test failures).

Pillar rollup uses ``cwe2`` exactly like v1 (walk ChildOf relations up to
the CWE-1000 view root).

Outputs tidy rows: {model, cell, problem, sample, cwe, pillar, tool, frequency}.
Run directly to write results/cwes_by_problem.csv for every cell.
"""
from __future__ import annotations

import csv
import re
from collections import Counter
from pathlib import Path

import pandas as pd

from ..pipeline.comment_inject import extract_standard_messages

REPO_ROOT = Path(__file__).resolve().parents[2]
CODE_ROOT = REPO_ROOT / "collected_code_6"
RESULTS_ROOT = REPO_ROOT / "results"

# ---------------------------------------------------------------------------
# v1 static-analyzer token mapping (unchanged from data_preprocessing.py)
# ---------------------------------------------------------------------------
V1_CWE_MAPPING: dict[int, list[str]] = {
    20: ["(CWE-120, CWE-20)."],
    119: ["[arrayIndexOutOfBounds]", "(CWE-119!/CWE-120)."],
    120: ["(CWE-120, CWE-20)", "(CWE-119!/CWE-120)", "(CWE-120)"],
    123: ["[-Wanalyzer-write-to-string-literal]"],
    124: ["[CWE-124]"],
    126: ["(CWE-126)", "[-Wanalyzer-out-of-bounds]"],
    127: ["[-Wanalyzer-out-of-bounds]"],
    129: ["[negativeIndex]"],
    190: ["[integerOverflow]", "(CWE-190)"],
    369: ["[zerodiv]"],
    401: ["[-Wanalyzer-malloc-leak]", "[memleak]"],
    457: [
        "[uninitvar]", "[legacyUninitvar]", "[uninitStructMember]",
        "[-Wanalyzer-use-of-uninitialized-value]", "[uninitdata]",
        "undeclared (first use in this function)",
    ],
    467: ["[-Wsizeof-array-argument]"],
    476: ["[-Wanalyzer-null-dereference]", "[-Wanalyzer-null-argument]"],
    562: ["[-Wreturn-local-addr]"],
    590: ["[-Wanalyzer-free-of-non-heap]"],
    628: ["[invalidFunctionArg]"],
    690: ["[-Wanalyzer-possible-null-dereference]"],
    704: ["[-Wint-conversion]"],
    758: [
        "[-Wimplicit-function-declaration]",
        "[-Wbuiltin-declaration-mismatch]",
        "conflicting types for",
        "unknown type name",
    ],
    787: ["excess elements in array initializer"],
    843: ["[-Wincompatible-pointer-types]"],
    1260: ["[overlappingWriteFunction]"],
}

# dynamic channel: ASan error kinds (from harness _parse_sanitizer output)
ASAN_CWE: dict[str, int] = {
    "heap-buffer-overflow": 787,
    "stack-buffer-overflow": 787,
    "global-buffer-overflow": 787,
    "heap-use-after-free": 416,
    "stack-use-after-scope": 787,
    "stack-use-after-return": 825,
    "dynamic-stack-buffer-overflow": 787,
    "container-overflow": 787,
    "allocation-size-too-big": 770,
    "heap-buffer-underflow": 787,
    "double-free": 415,
    "unknown-crash": 758,
    "SEGV": 758,          # wild pointer dereference
    "stack-overflow": 674,
    "null-dereference": 476,
    "timeout": 400,       # hardening: unbounded loop; not a true CWE
}

# dynamic channel: UBSan runtime errors (message prefixes)
UBSAN_CWE: list[tuple[str, int]] = [
    ("null pointer passed as argument", 690),
    ("signed integer overflow", 190),
    ("unsigned integer overflow", 190),
    ("division by zero", 369),
    ("out of bounds", 787),
    ("index out of bounds", 125),
    ("load of value", 457),          # load of misaligned/uninitialized
    ("float-cast-overflow", 190),
    ("shift exponent", 190),
]

# dynamic channel: oracle test failures = functional defect (no direct CWE)
TEST_FAILURE_CWE = 758  # "Reliance on Undefined, Unspecified, or Implementation-Defined Behavior"
                         # only used for crash/sanitizer-backed failures; plain
                         # wrong answers stay unmapped (see map_test_message).

_FLAIR_RE = re.compile(r"\(CWE-[^)]*\)")
_PROBLEM_RE = re.compile(r"^problem-(\d+)(-s(\d+))?$")


def _pillar_cache() -> dict[int, int]:
    global _PILLARS
    if _PILLARS is None:
        _PILLARS = {}
    return _PILLARS


_PILLARS: dict[int, int] | None = None


def get_cwe_pillar(cwe: int) -> int:
    """Walk ChildOf relations to the pillar (same logic as v1)."""
    cache = _pillar_cache()
    if cwe in cache:
        return cache[cwe]
    from cwe2.database import Database
    from cwe2.weakness import Weakness

    db = Database()
    current = db.get(cwe)
    father = _find_father(current)
    while father:
        current = db.get(father)
        father = _find_father(current)
    pillar = int(str(current.cwe_id).split("-")[-1])
    cache[cwe] = pillar
    return pillar


def _find_father(cwe) -> int | None:
    if not hasattr(cwe, "related_weaknesses"):
        return None
    for related in cwe.related_weaknesses.split("::"):
        if related == "":
            continue
        parts = related.split(":")
        if len(parts) >= 6 and parts[1] == "ChildOf" and parts[5] == "1000":
            return int(parts[3])
    return None


def map_static_message(message: str, tool: str) -> list[int]:
    """CWE ids for one static-analyzer finding line (v1 semantics)."""
    cwes: list[int] = []
    for cwe, tokens in V1_CWE_MAPPING.items():
        for tok in tokens:
            if tok in message:
                cwes.append(cwe)
                break
    # flawfinder hits carry explicit CWE tags -> take them directly
    if tool == "flawfinder":
        for tag in _FLAIR_RE.findall(message):
            for part in re.findall(r"CWE-(\d+)", tag):
                cwes.append(int(part))
    return sorted(set(cwes))


def map_dynamic_message(message: str, channel: str) -> list[int]:
    """CWE ids for one dynamic finding line (.asan.txt / .fuzz.txt / .test.txt)."""
    if channel in ("asan", "fuzz"):
        if "ASan: " in message:
            kind = message.split("ASan: ", 1)[1].split(" ", 1)[0].strip()
            if kind in ASAN_CWE:
                return [ASAN_CWE[kind]]
        for prefix, cwe in UBSAN_CWE:
            if "UBSan: " in message and prefix in message:
                return [cwe]
        if "crash (signal" in message or "memory-safety defect" in message:
            return [758]
        return []
    if channel == "test":
        # Test-failure lines say "test case N failed: expected ..., got ..."
        # -> functional defect, not a CWE-classifiable weakness. Only
        # sanitizer-backed failures (reported on .asan.txt) get a CWE.
        return []
    return []


def cell_cwe_counts(cell_dir: Path) -> list[dict]:
    """Tidy CWE rows for one cell dir (uses heal_0 reports only)."""
    heal0 = cell_dir / "heal_0"
    if not heal0.is_dir():
        return []
    counter: Counter[tuple] = Counter()
    for report in sorted(heal0.glob("problem-*.txt")):
        name = report.name
        m = _PROBLEM_RE.match(name.split(".")[0])
        if not m:
            continue
        pid, sample = int(m.group(1)), int(m.group(3) or 1)
        for tool in ("gcc", "clang", "cppcheck", "flawfinder", "asan", "fuzz", "test"):
            if name.endswith(f".{tool}.txt"):
                break
        else:
            continue
        try:
            text = report.read_text(errors="ignore")
        except OSError:
            continue
        for msg in extract_standard_messages(text):
            if msg["line"] <= 0:
                continue
            if tool in ("gcc", "clang", "cppcheck", "flawfinder"):
                cwes = map_static_message(msg["message"], tool)
            else:
                cwes = map_dynamic_message(msg["message"], tool)
            for cwe in cwes:
                counter[(pid, sample, cwe, tool)] += 1
    rows = []
    for (pid, sample, cwe, tool), freq in sorted(counter.items()):
        rows.append(
            {
                "problem": pid,
                "sample": sample,
                "cwe": cwe,
                "pillar": get_cwe_pillar(cwe),
                "tool": tool,
                "frequency": freq,
            }
        )
    return rows


def all_cells_cwes(code_root: Path | None = None) -> pd.DataFrame:
    code_root = code_root or CODE_ROOT
    frames = []
    for model_dir in sorted(code_root.iterdir()):
        if not model_dir.is_dir():
            continue
        for cell_dir in sorted(model_dir.iterdir()):
            if not (cell_dir / "heal_0").is_dir():
                continue
            rows = cell_cwe_counts(cell_dir)
            if rows:
                df = pd.DataFrame(rows)
                df.insert(0, "cell", cell_dir.name)
                df.insert(0, "model", model_dir.name)
                frames.append(df)
    if not frames:
        return pd.DataFrame(
            columns=["model", "cell", "problem", "sample", "cwe", "pillar", "tool", "frequency"]
        )
    return pd.concat(frames, ignore_index=True)


if __name__ == "__main__":
    df = all_cells_cwes()
    out = RESULTS_ROOT / "cwes_by_problem.csv"
    out.parent.mkdir(parents=True, exist_ok=True)
    df.to_csv(out, index=False)
    print(f"{len(df)} rows -> {out}")
    if len(df):
        print(
            df.groupby("cwe")["frequency"].sum()
            .sort_values(ascending=False).head(10).to_string()
        )
