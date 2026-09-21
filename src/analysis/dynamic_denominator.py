"""Dynamic-analysis denominator: compiled/executed programs per model.

Motivation: the dynamic sub-channels (tests, sanitizer oracle, fuzzer)
only observe programs that compile under the sanitizer build and
execute. This script computes that denominator so dynamic detection
counts can be turned into detection rates among executable programs.

Semantics verified from artifacts (main cells, rounds 0-5):
  - a version compiled  <=>  {base}.o exists in that round dir
    (tests and fuzzing write "could not compile" / "not fuzzed -
    not compilable" markers otherwise; .test.txt/.fuzz.txt exist for
    every program regardless)
  - executed <=> compiled (the harness runs the test suite under
    sanitizers on every program that compiles)
  - fuzzable <=> .fuzz.txt lacks BOTH "not fuzzed - not compilable"
    and "no fuzzable input interface"

Dynamic detection sets are recomputed here via
channel_contribution.audit_model so numerator and denominator share
one artifact.
"""
from __future__ import annotations

import os
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(REPO))
from src.analysis.channel_contribution import MODELS, MAIN, CAP, audit_model  # noqa: E402


def round_dirs(cell: Path) -> list[Path]:
    dirs = [cell / "heal_0"]
    for r in range(1, CAP + 1):
        d = cell / f"heal_{r}" / "healed"
        if d.is_dir():
            dirs.append(d)
    return dirs


def main() -> None:
    agg = dict(n=0, comp0=0, comp_any=0, fuzz_any=0, dyn=0, tests=0,
               oracle=0, fuzzdet=0, fuzzdet_fuzzable=0)
    lines = ["# Dynamic-analysis denominator: compiled/executed programs",
             "",
             "Main cells, rounds 0-5. compiled = .o produced under the",
             "sanitizer build; executed = compiled (test harness runs every",
             "compiled program); fuzzable = .fuzz.txt lacks 'not compilable'",
             "and 'no fuzzable input interface'. Dynamic detected = tests |",
             "oracle | fuzzer findings (gate-injectable).", "",
             "| Model | programs | compiled r0 | executed (any version) | "
             "fuzzable (any version) | dynamic detected | rate among executed |",
             "|---|---:|---:|---:|---:|---:|---:|"]
    for model in MODELS:
        cell = REPO / "collected_code_6" / model / MAIN
        programs = {b[:-2] for b in os.listdir(cell / "heal_0")
                    if b.endswith(".c")}
        comp0 = comp_any = fuzz_any = 0
        for base in programs:
            has_o = False
            fuzzable = False
            for d in round_dirs(cell):
                if (d / f"{base}.o").is_file():
                    has_o = True
                    f = d / f"{base}.fuzz.txt"
                    if f.is_file():
                        t = f.read_text(errors="replace")
                        if ("no fuzzable input interface" not in t
                                and "not compilable" not in t):
                            fuzzable = True
            comp0 += (cell / "heal_0" / f"{base}.o").is_file()
            comp_any += has_o
            fuzz_any += fuzzable

        sets, prog_set, asan_ub, f_attr, f_sig = audit_model(model)
        n = len(prog_set)
        tests = sets[".test.txt"]
        oracle = sets[".asan.txt"]
        fuzzdet = sets[".fuzz.txt"]
        dyn = tests | oracle | fuzzdet
        rate = 100 * len(dyn) / comp_any if comp_any else 0.0
        lines.append(
            f"| {model} | {n} | {comp0} | {comp_any} | {fuzz_any} | "
            f"{len(dyn)} | {rate:.1f}% |")

        agg["n"] += n
        agg["comp0"] += comp0
        agg["comp_any"] += comp_any
        agg["fuzz_any"] += fuzz_any
        agg["dyn"] += len(dyn)
        agg["tests"] += len(tests)
        agg["oracle"] += len(oracle)
        agg["fuzzdet"] += len(fuzzdet)
        print(f"done {model}", file=sys.stderr)

    # aggregate needs unique (model, program) pairs; comp counts are per
    # model so pairs are unique across models by construction
    rate = 100 * agg["dyn"] / agg["comp_any"] if agg["comp_any"] else 0.0
    lines.append(
        f"| **Aggregate** | {agg['n']} | {agg['comp0']} | "
        f"{agg['comp_any']} | {agg['fuzz_any']} | {agg['dyn']} | "
        f"{rate:.1f}% |")
    lines.append("")
    lines.append(f"Sub-channel detections (aggregate pairs): tests "
                 f"{agg['tests']}, oracle {agg['oracle']}, fuzzer "
                 f"{agg['fuzzdet']}.")
    lines.append(f"Compiled at round 0 (aggregate): {agg['comp0']}/{agg['n']} "
                 f"({100*agg['comp0']/agg['n']:.1f}%).")

    out = REPO / "results" / "dynamic_denominator.md"
    out.write_text("\n".join(lines) + "\n")
    print(f"written -> {out}")


if __name__ == "__main__":
    main()
