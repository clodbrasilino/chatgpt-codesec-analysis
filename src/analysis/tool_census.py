"""Comprehensive analyzer-output census for CWE mapping review.

Scans all main-cell heal_0 reports and produces one consolidated list of
every distinct finding TYPE per tool (normalized), with dataset-wide counts,
an example, and the CURRENT CWE mapping (v1 base-paper tokens + this work's
dynamic extensions). Types with no mapping are flagged for discussion.

Output: results/tool_findings_census.md
"""
from __future__ import annotations

import re
from collections import Counter, defaultdict
from pathlib import Path

import sys
sys.path.insert(0, str(Path(__file__).resolve().parents[2]))

from src.pipeline.comment_inject import extract_standard_messages
from src.analysis.cwe_map import (
    ASAN_CWE, UBSAN_CWE, V1_CWE_MAPPING, map_static_message,
)

REPO = Path(__file__).resolve().parents[2]
CODE = REPO / "collected_code_6"
MODELS = ["deepseek-v4-pro", "qwen-max", "glm-5.1", "kimi-k3",
          "openai-gpt56-sol", "claude-fable-5", "gemini-3-pro"]
OUT = REPO / "results" / "tool_findings_census.md"


def norm_prefix(msg: str, n: int = 58) -> str:
    """Normalize a message into a type key: strip quoted identifiers/numbers."""
    s = msg.strip()
    s = re.sub(r"'[^']*'", "'X'", s)
    s = re.sub(r'"[^"]*"', '"X"', s)
    s = re.sub(r"\b\d+\b", "N", s)
    return s[:n].rstrip()


# per-tool type keys -------------------------------------------------------

def gcc_types(txt: str):
    out = []
    for m in extract_standard_messages(txt):
        if m["line"] <= 0:
            continue
        msg = m["message"]
        tag = re.search(r"\[(-W[\w.-]+)\]", msg)
        key = f"warning {tag.group(1)}" if tag else norm_prefix(msg)
        out.append((key, msg.strip()[:110]))
    return out


def clang_types(txt: str):
    out = []
    for m in extract_standard_messages(txt):
        if m["line"] <= 0:
            continue
        out.append((norm_prefix(m["message"]), m["message"].strip()[:110]))
    return out


def cppcheck_types(txt: str):
    out = []
    for m in extract_standard_messages(txt):
        if m["line"] <= 0:
            continue
        msg = m["message"].strip()
        tag = re.search(r"\[([\w.]+)\]$", msg)
        key = tag.group(1) if tag else norm_prefix(msg)
        out.append((key, msg[:110]))
    return out


def flawfinder_types(txt: str):
    # raw flawfinder format: path:line:  [level] (category) Function: ...
    out = []
    for line in txt.splitlines():
        m = re.search(r"\[(\d+)\] \(([\w -]+)\)\s+(.+?):", line)
        if m:
            out.append((f"level {m.group(1)} · {m.group(2)} · {m.group(3)}", line.strip()[:110]))
    return out


def asan_types(txt: str):
    out = []
    for m in extract_standard_messages(txt):
        if m["line"] <= 0:
            continue
        msg = m["message"].strip()
        m2 = re.match(r"(UBSan|ASan): (.+)", msg)
        if not m2:
            continue
        kind = m2.group(2)
        if m2.group(1) == "ASan":
            key = f"ASan: {kind}"
        else:
            key = f"UBSan: {norm_prefix(kind, 48)}"
        out.append((key, msg[:110]))
    return out


def test_types(txt: str):
    out = []
    for m in extract_standard_messages(txt):
        if m["line"] <= 0:
            continue
        msg = m["message"].strip()
        if "test case" in msg and "failed" in msg:
            out.append(("test case failure (wrong output)", msg[:110]))
    # outcome markers (line-0 info/error lines: never healing feedback,
    # but they define the oracle's interface taxonomy)
    for line in txt.splitlines():
        if "all" in line and "test cases passed" in line:
            out.append(("MARKER: all test cases passed (clean)", line.strip()[:110]))
        elif "CLI mode exercised" in line:
            out.append(("MARKER: CLI mode exercised via stdin (no functional oracle)", line.strip()[:110]))
        elif "no testable interface" in line:
            out.append(("MARKER: no testable interface (never executed)", line.strip()[:110]))
        elif "could not compile under sanitizers" in line:
            out.append(("MARKER: could not compile under sanitizers", line.strip()[:110]))
        elif "not compilable" in line:
            out.append(("MARKER: not compilable (skipped, heals via static channel)", line.strip()[:110]))
        elif "no harness spec" in line:
            out.append(("MARKER: no harness spec", line.strip()[:110]))
    return out


TOOLS = [
    ("gcc", ".gcc.txt", gcc_types, "gcc-15 -fanalyzer"),
    ("clang", ".clang.txt", clang_types, "clang --analyze + z3 crosscheck"),
    ("cppcheck", ".cppcheck.txt", cppcheck_types, "Cppcheck Premium 23.6 (bughunting)"),
    ("flawfinder", ".flawfinder.txt", flawfinder_types, "Flawfinder 2.0.19 (rule-based)"),
    ("sanitizer", ".asan.txt", asan_types, "ASan/UBSan runtime oracle"),
    ("tests", ".test.txt", test_types, "MBPP test-case oracle"),
]


def cwe_for(tool: str, key: str, example: str) -> str:
    """Current mapping for a finding type (v1 static tokens or dynamic ext)."""
    if tool == "sanitizer":
        if key.startswith("ASan: "):
            kind = key[6:].strip()
            cwe = ASAN_CWE.get(kind)
            return f"CWE-{cwe}" if cwe else "UNMAPPED"
        # UBSan prefix match
        for prefix, cwe in UBSAN_CWE:
            if prefix in key:
                return f"CWE-{cwe}"
        return "UNMAPPED"
    if tool == "tests":
        return "CWE-758 (crash-backed only; plain wrong answers unmapped)"
    # static tools: reuse map_static_message on the example message
    probe = example
    # flawfinder: reconstruct a tag-bearing message if possible
    cwes = map_static_message(probe, tool if tool != "sanitizer" else "gcc")
    if not cwes:
        # try the key itself (tokens like [checkId] often live in the key)
        cwes = map_static_message(key, tool)
    return ", ".join(f"CWE-{c}" for c in sorted(set(cwes))) if cwes else "UNMAPPED"


def main() -> None:
    census: dict[str, dict[str, dict]] = {t: defaultdict(lambda: {"n": 0, "ex": ""}) for t, _, _, _ in TOOLS}
    per_tool_files = Counter()

    # sanitizer: whole-dataset scan (findings are rare; include every cell and
    # healing round so the type list is exhaustive) — run ONCE
    for p in CODE.rglob("*.asan.txt"):
        per_tool_files["sanitizer"] += 1
        txt = p.read_text(errors="replace")
        for key, ex in asan_types(txt):
            d = census["sanitizer"][key]
            d["n"] += 1
            if not d["ex"]:
                d["ex"] = ex

    for model in MODELS:
        h0 = CODE / model / "feedback-static+dynamic-r0-t1.0-p1.0" / "heal_0"
        if not h0.is_dir():
            continue
        for tool, suf, fn, _ in TOOLS:
            if tool == "sanitizer":
                continue  # handled above
            for p in h0.glob(f"*{suf}"):
                per_tool_files[tool] += 1
                txt = p.read_text(errors="replace")
                for key, ex in fn(txt):
                    d = census[tool][key]
                    d["n"] += 1
                    if not d["ex"]:
                        d["ex"] = ex

    lines = [
        "# Analyzer Output Census — All Finding Types Across the Main Experiment",
        "",
        "**Scope:** heal_0 (initial generations) of all 7 main cells (974 × 3 samples each;",
        "6 completed cells + gemini's completed heal_0) — every report file parsed with",
        "the pipeline's own parsers. **Current CWE mapping** column = the v1/base-paper",
        "token mapping (static analyzers, kept verbatim from the ISE 2026 work) plus this",
        "work's dynamic-channel extensions (`src/analysis/cwe_map.py`). **UNMAPPED** rows",
        "and any mapping you want to revisit are the discussion agenda for the CWE-2026",
        "re-taxonomization.",
        "",
    ]
    for tool, suf, fn, label in TOOLS:
        entries = sorted(census[tool].items(), key=lambda kv: -kv[1]["n"])
        total = sum(v["n"] for _, v in entries)
        lines += [f"## {tool} — {label}", "",
                  f"{per_tool_files[tool]:,} report files scanned · **{total:,} findings** · "
                  f"**{len(entries)} distinct types**", "",
                  "| # | Finding type | Count | Example | Current CWE |", "|---|---|---|---|---|"]
        for i, (key, d) in enumerate(entries, 1):
            cwe = cwe_for(tool, key, d["ex"])
            flag = " ⚠️" if cwe == "UNMAPPED" else ""
            ex = d["ex"].replace("|", "\\|")[:95]
            lines.append(f"| {i} | `{key}` | {d['n']:,} | {ex} | {cwe}{flag} |")
        lines.append("")

    # summary of unmapped
    lines += ["## Unmapped types (discussion agenda)", ""]
    for tool, _, _, _ in TOOLS:
        unmapped = [(k, v) for k, v in census[tool].items()
                    if cwe_for(tool, k, v["ex"]) == "UNMAPPED"]
        if unmapped:
            lines.append(f"**{tool}:** " + "; ".join(f"`{k}` ({v['n']:,})" for k, v in
                                                    sorted(unmapped, key=lambda kv: -kv[1]["n"])))
            lines.append("")

    lines += ["## Notes for the CWE-2026 update", "",
              "- The static token mapping is the ISE 2026 base-paper mapping kept verbatim",
              "  for comparability; under CWE-2026 several entries will move (e.g. buffer",
              "  overflow family reorganizations, CWE-758 'Reliance on Undefined Behavior'",
              "  successor entries).",
              "- The dynamic mapping (ASan kinds, UBSan runtime errors) was added in this",
              "  work; several entries currently collapse to broad CWEs (e.g. all buffer",
              "  overflows → CWE-787) that CWE-2026 may want to split by memory region.",
              "- Test-case failures are mapped to CWE-758 only when crash/sanitizer-backed;",
              "  plain wrong answers are deliberately unmapped (functional defect, not a",
              "  memory-safety CWE) — a framing decision to revisit for the new taxonomy.",
              "- Flawfinder carries its own CWE tags in the raw output (parsed at mapping",
              "  time from `(CWE-xxx)` markers); the census rows show its rule category +",
              "  level as the type key.",
              ]

    OUT.write_text("\n".join(lines) + "\n")
    print(f"[census] wrote {OUT}")
    for tool, _, _, _ in TOOLS:
        n_types = len(census[tool])
        total = sum(v["n"] for v in census[tool].values())
        print(f"  {tool:10s} {total:7,d} findings, {n_types:4d} distinct types")


if __name__ == "__main__":
    main()
