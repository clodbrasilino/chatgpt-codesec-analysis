"""Channel/subchannel contribution: programs detected per channel, by model.

Scope: main cells (full gate, s+d, non-thinking), rounds 0..5 (the
five-round analysis horizon). A program counts for a sub-channel if that
sub-channel produced at least one injectable finding (line > 0, the gate's
own criterion) on any version of the program within the horizon.

Sub-channels:
  static   : gcc, clang, cppcheck, flawfinder (aggregate + individuals)
  dynamic  : functional tests (failed test cases), sanitizer oracle
             (ASan / UBSan, from .asan.txt), fuzzer (attributed findings
             or signal-only crashes, from .fuzz.txt)
"""
from __future__ import annotations

import json
import os
import re
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(REPO))
from src.pipeline.comment_inject import extract_standard_messages  # noqa: E402

CAP = 5
MAIN = "feedback-static+dynamic-r0-t1.0-p1.0"
MODELS = ["claude-fable-5", "openai-gpt56-sol", "gemini-3-pro", "kimi-k3",
          "deepseek-v4-pro", "qwen-max", "glm-5.1"]
STATIC = [".gcc.txt", ".clang.txt", ".cppcheck.txt", ".flawfinder.txt"]
DYN = [".test.txt", ".asan.txt", ".fuzz.txt"]
COLS = STATIC + DYN


def has_finding(text: str, want: str | None = None) -> bool:
    # NB: parsed messages carry a leading space from the severity slot
    # ("file:line:col: error: message" -> " message"), so strip first.
    for msg in extract_standard_messages(text):
        if msg["line"] > 0:
            if want is None or msg["message"].lstrip().startswith(want):
                return True
    return False


def round_dirs(cell: Path) -> list[Path]:
    dirs = [cell / "heal_0"]
    for r in range(1, CAP + 1):
        d = cell / f"heal_{r}" / "healed"
        if d.is_dir():
            dirs.append(d)
    return dirs


def audit_model(model: str) -> tuple[dict, int]:
    cell = REPO / "collected_code_6" / model / MAIN
    programs = {b[:-2] for b in os.listdir(cell / "heal_0") if b.endswith(".c")}
    sets = {c: set() for c in COLS}
    asan_ub = {"ASan": set(), "UBSan": set()}
    fuzz_sig = set()
    fuzz_attr = set()
    for d in round_dirs(cell):
        names = {s: {f[: -len(s)] for f in os.listdir(d) if f.endswith(s)}
                 for s in COLS}
        for base in programs:
            for s in STATIC:
                if base in sets[s]:
                    continue
                f = d / f"{base}{s}"
                if f.is_file() and has_finding(f.read_text(errors="replace")):
                    sets[s].add(base)
            f = d / f"{base}.test.txt"
            if base not in sets[".test.txt"] and f.is_file():
                if has_finding(f.read_text(errors="replace"), want="test case"):
                    sets[".test.txt"].add(base)
            f = d / f"{base}.asan.txt"
            if f.is_file():
                text = f.read_text(errors="replace")
                if has_finding(text, want="ASan:"):
                    sets[".asan.txt"].add(base)
                    asan_ub["ASan"].add(base)
                if has_finding(text, want="UBSan:"):
                    sets[".asan.txt"].add(base)
                    asan_ub["UBSan"].add(base)
            f = d / f"{base}.fuzz.txt"
            if f.is_file():
                text = f.read_text(errors="replace")
                if has_finding(text, want="Fuzzing found a crash"):
                    sets[".fuzz.txt"].add(base)
                    fuzz_sig.add(base)
                if (has_finding(text, want="ASan:")
                        or has_finding(text, want="UBSan:")):
                    sets[".fuzz.txt"].add(base)
                    fuzz_attr.add(base)
                    if has_finding(text, want="ASan:"):
                        asan_ub["ASan"].add(base)
                    if has_finding(text, want="UBSan:"):
                        asan_ub["UBSan"].add(base)
    return sets, programs, asan_ub, fuzz_attr, fuzz_sig


def main() -> None:
    per_model = {}
    agg = {c: set() for c in COLS}
    agg_asan = {"ASan": set(), "UBSan": set()}
    agg_sig, agg_attr = set(), set()
    for model in MODELS:
        sets, programs, asan_ub, f_attr, f_sig = audit_model(model)
        per_model[model] = (sets, len(programs), asan_ub, f_attr, f_sig)
        for c in COLS:
            agg[c] |= {(model, b) for b in sets[c]}
        for k in asan_ub:
            agg_asan[k] |= {(model, b) for b in asan_ub[k]}
        agg_sig |= {(model, b) for b in f_sig}
        agg_attr |= {(model, b) for b in f_attr}
        print(f"done {model}", file=sys.stderr)

    n_agg = len({(m, b) for m in MODELS for b in
                 {f[:-2] for f in os.listdir(REPO / "collected_code_6" / m / MAIN / "heal_0")
                  if f.endswith(".c")}})

    def static_any(sets):
        return len(sets[".gcc.txt"] | sets[".clang.txt"] |
                   sets[".cppcheck.txt"] | sets[".flawfinder.txt"])

    def dyn_any(sets):
        return len(sets[".test.txt"] | sets[".asan.txt"] | sets[".fuzz.txt"])

    lines = ["# Channel and sub-channel contribution (five-round horizon)",
             "",
             "Programs (model x problem) with at least one finding of the",
             "sub-channel on any version from round 0 to round 5. Main cells,",
             "full gate, non-thinking. Aggregate = unique (model, program) pairs,",
             f"{n_agg} programs in total.", ""]
    lines.append("## Per model")
    lines.append("")
    lines.append("| Model | programs | STATIC any | gcc | clang | cppcheck | "
                 "flawfinder | DYN any | tests | oracle | ASan | UBSan | "
                 "fuzzer | any channel |")
    lines.append("|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|")
    for model in MODELS:
        sets, n, asan_ub, f_attr, f_sig = per_model[model]
        s_any, d_any = static_any(sets), dyn_any(sets)
        anyc = s_any + d_any
        lines.append(
            f"| {model} | {n} | {s_any} | {len(sets['.gcc.txt'])} | "
            f"{len(sets['.clang.txt'])} | {len(sets['.cppcheck.txt'])} | "
            f"{len(sets['.flawfinder.txt'])} | {d_any} | "
            f"{len(sets['.test.txt'])} | {len(sets['.asan.txt'])} | "
            f"{len(asan_ub['ASan'])} | {len(asan_ub['UBSan'])} | "
            f"{len(sets['.fuzz.txt'])} | {anyc} |")
    s_any = static_any(agg)
    d_any = dyn_any(agg)
    anyc = len(agg[".gcc.txt"] | agg[".clang.txt"] | agg[".cppcheck.txt"] |
               agg[".flawfinder.txt"] | agg[".test.txt"] | agg[".asan.txt"] |
               agg[".fuzz.txt"])
    lines.append(f"| **Aggregate** | {n_agg} | {s_any} | "
                 f"{len(agg['.gcc.txt'])} | {len(agg['.clang.txt'])} | "
                 f"{len(agg['.cppcheck.txt'])} | {len(agg['.flawfinder.txt'])} | "
                 f"{d_any} | {len(agg['.test.txt'])} | {len(agg['.asan.txt'])} | "
                 f"{len(agg_asan['ASan'])} | {len(agg_asan['UBSan'])} | "
                 f"{len(agg['.fuzz.txt'])} | {anyc} |")
    lines.append("")
    lines.append(f"Fuzzer split (aggregate): attributed findings "
                 f"{len(agg_attr)}, signal-only crashes {len(agg_sig)} "
                 f"(a program may appear in both).")
    lines.append("")
    lines.append("Notes: a program counts for a sub-channel if that sub-channel "
                 "produced at least one injectable finding on any version within "
                 "rounds 0-5; the oracle split (ASan/UBSan) is by report prefix; "
                 "fuzzer findings include replay-attributed sanitizer reports and "
                 "signal-only crashes.")

    out = REPO / "results" / "channel_contribution.md"
    out.write_text("\n".join(lines) + "\n")
    print(f"written -> {out}")


if __name__ == "__main__":
    main()
