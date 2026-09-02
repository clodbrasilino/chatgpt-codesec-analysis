"""Per-cell metric extraction for the FSE 2027 extension.

A *cell* is one experimental configuration (model x feedback x temp x top_p)
stored under ``collected_code_6/{model}/{cell_slug}/`` with the outcome
manifest at ``results/{model}/{cell_slug}.manifest.json``.

This module turns the raw artifacts into a tidy metrics table:

- generation metrics: n_generated, n_compilable (compile gate ``.o``)
- defect metrics: initial flagged rate overall and per analyzer tool
- repair metrics: clean_at_start / rounds_to_clean / not_cleaned,
  overall clean rate, mean+median rounds to clean
- dynamic metrics (when present): oracle test-failure rate, sanitizer
  finding rate, fuzz finding rate

Run directly, it scans every cell and writes ``results/metrics.csv``.
"""
from __future__ import annotations

import json
import re
from collections import Counter
from pathlib import Path

import pandas as pd

from ..pipeline.comment_inject import STATIC_SUFFIXES, DYNAMIC_SUFFIXES

REPO_ROOT = Path(__file__).resolve().parents[2]
CODE_ROOT = REPO_ROOT / "collected_code_6"
RESULTS_ROOT = REPO_ROOT / "results"

_PROBLEM_RE = re.compile(r"^problem-(\d+)(-s(\d+))?$")
TOOLS = ["gcc", "clang", "cppcheck", "flawfinder"]
DYN_CHANNELS = ["test", "asan", "fuzz"]


def _has_findings(report: Path) -> bool:
    """True when the report contains at least one 5-token finding line."""
    try:
        text = report.read_text(errors="ignore")
    except OSError:
        return False
    for line in text.splitlines():
        tokens = line.split(":")
        if len(tokens) >= 5:
            try:
                if int(tokens[1]) > 0:
                    return True
            except ValueError:
                continue
    return False


def _list_sources(cell_dir: Path) -> list[str]:
    """Basenames of generated .c files (problem-N or problem-N-sK)."""
    return sorted(
        f.name[:-2]
        for f in cell_dir.glob("problem-*.c")
        if _PROBLEM_RE.match(f.name[:-2])
    )


def _round_flagged(root: Path, round_no: int) -> set[str]:
    tbe = root / f"heal_{round_no}" / "to_be_healed"
    if not tbe.is_dir():
        # heal_0 flag status is derived from reports, not a to_be_healed dir
        return set()
    return {f.name[:-2] for f in tbe.glob("problem-*.c")}


def cell_metrics(model: str, slug: str, root: Path | None = None) -> dict | None:
    """Compute the metric row for one cell; None when artifacts are absent."""
    root = root or (CODE_ROOT / model / slug)
    if not root.is_dir():
        return None
    heal0 = root / "heal_0"
    sources = _list_sources(heal0)
    if not sources:
        return None

    m: dict = {
        "model": model,
        "cell": slug,
        "n_generated": len(sources),
    }

    # ---- compile gate ----
    m["n_compilable"] = sum(1 for b in sources if (heal0 / f"{b}.o").exists())
    m["compile_rate"] = round(m["n_compilable"] / len(sources), 4)

    # ---- initial findings per tool ----
    flagged_by_tool: dict[str, set[str]] = {}
    for tool in TOOLS:
        flagged = {
            b for b in sources
            if _has_findings(heal0 / f"{b}.{tool}.txt")
        }
        flagged_by_tool[tool] = flagged
        m[f"flagged_{tool}"] = len(flagged)

    initial_flagged: set[str] = set().union(*flagged_by_tool.values()) if flagged_by_tool else set()

    # ---- dynamic channels at heal_0 (if measured) ----
    for chan in DYN_CHANNELS:
        flagged = {
            b for b in sources
            if _has_findings(heal0 / f"{b}.{chan}.txt")
        }
        m[f"flagged_{chan}"] = len(flagged)
        if chan == "test":
            # test.txt exists for every dynamically-testable file; an *error*
            # line means a failure. Also count info-passed files.
            passed = failed = absent = 0
            for b in sources:
                report = heal0 / f"{b}.test.txt"
                if not report.exists():
                    absent += 1
                elif _has_findings(report):
                    failed += 1
                else:
                    passed += 1
            m["oracle_absent"] = absent
            m["oracle_passed"] = passed
            m["oracle_failed"] = failed
            tested = passed + failed
            m["oracle_pass_rate"] = round(passed / tested, 4) if tested else None

    # initial defect rate: flagged by any static or dynamic channel
    dyn_flagged: set[str] = set()
    for chan in DYN_CHANNELS:
        dyn_flagged |= {
            b for b in sources if _has_findings(heal0 / f"{b}.{chan}.txt")
        }
    initial_all = initial_flagged | dyn_flagged
    m["initial_flagged"] = len(initial_all)
    m["initial_defect_rate"] = round(len(initial_all) / len(sources), 4)
    m["initial_defect_rate_static_only"] = round(
        len(initial_flagged) / len(sources), 4
    )

    # ---- repair outcomes from the manifest ----
    manifest_path = RESULTS_ROOT / model / f"{slug}.manifest.json"
    rounds_to_clean: list[int] = []
    n_clean_at_start = n_cleaned = n_not_cleaned = n_heal_failed = 0
    max_rounds = None
    if manifest_path.exists():
        manifest = json.loads(manifest_path.read_text())
        max_rounds = manifest["cell"].get("max_rounds")
        for base, out in manifest["outcomes"].items():
            if out["outcome"] == "clean_at_start":
                n_clean_at_start += 1
            elif out["outcome"] == "clean":
                n_cleaned += 1
                rounds_to_clean.append(out["rounds_to_clean"])
            elif out["outcome"] == "heal_failed":
                n_heal_failed += 1
            else:
                n_not_cleaned += 1
    m.update(
        {
            "clean_at_start": n_clean_at_start,
            "cleaned": n_cleaned,
            "not_cleaned": n_not_cleaned,
            "heal_failed": n_heal_failed,
            "max_rounds": max_rounds,
        }
    )
    if rounds_to_clean:
        s = pd.Series(rounds_to_clean)
        m["mean_rounds_to_clean"] = round(float(s.mean()), 3)
        m["median_rounds_to_clean"] = round(float(s.median()), 3)
    total = n_clean_at_start + n_cleaned + n_not_cleaned
    if total:
        m["final_clean_rate"] = round((n_clean_at_start + n_cleaned) / total, 4)

    # ---- still-flagged survival per round (fraction flagged at heal_N) ----
    # heal_0 uses the union of reports; heal_N uses to_be_healed contents.
    survival: dict[int, int] = {0: len(initial_all)}
    for heal_dir in sorted(root.glob("heal_*")):
        rm = re.match(r"heal_(\d+)$", heal_dir.name)
        if not rm:
            continue
        n = int(rm.group(1))
        if n == 0:
            continue
        flagged = _round_flagged(root, n)
        if flagged:
            survival[n] = len(flagged)
    m["survival_counts"] = json.dumps(survival)

    return m


def all_cells(code_root: Path | None = None) -> list[dict]:
    code_root = code_root or CODE_ROOT
    rows = []
    for model_dir in sorted(code_root.iterdir()):
        if not model_dir.is_dir():
            continue
        for cell_dir in sorted(model_dir.iterdir()):
            if not cell_dir.is_dir():
                continue
            row = cell_metrics(model_dir.name, cell_dir.name, cell_dir)
            if row:
                rows.append(row)
    return rows


def write_metrics(out: Path | None = None) -> Path:
    out = out or (RESULTS_ROOT / "metrics.csv")
    out.parent.mkdir(parents=True, exist_ok=True)
    df = pd.DataFrame(all_cells())
    df.to_csv(out, index=False)
    return out


if __name__ == "__main__":
    path = write_metrics()
    df = pd.read_csv(path)
    cols = [
        "model", "cell", "n_generated", "initial_defect_rate",
        "flagged_gcc", "flagged_clang", "flagged_cppcheck", "flagged_flawfinder",
        "clean_at_start", "cleaned", "not_cleaned", "final_clean_rate",
    ]
    print(df[[c for c in cols if c in df.columns]].to_string(index=False))
    print(f"\nwritten -> {path}")
