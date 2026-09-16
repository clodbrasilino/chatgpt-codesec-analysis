"""Dynamic analysis orchestrator (the "dynamic" feedback channel).

For every ``problem-{id}[-s{k}].c`` in a directory:

- runs the sanitizer test oracle (ASan+UBSan, LINK or CLI interface) and
  writes ``.test.txt`` (functional pass/fail) and ``.asan.txt`` (memory /
  undefined-behavior findings in the standard
  ``file:line:col:severity:message`` format);
- optionally fuzzes stdin/argv-consuming programs with AFL++ and writes
  ``.fuzz.txt``.

Report basenames share the source basename so comment injection
(``feedback_channels.dynamic``) picks them up unchanged.
"""
from __future__ import annotations

import os
import re
from concurrent.futures import ThreadPoolExecutor, as_completed
from pathlib import Path

import yaml
from tqdm import tqdm

from ..harness.find_function import detect_input_consumption
from ..harness.mbpp_loader import SPEC_DIR, HarnessSpec
from ..harness.run import run_one
from .fuzzer import fuzz_program

PROBLEM_RE = re.compile(r"^problem-(\d+)(-s(\d+))?$")
TEST_SUFFIX = ".test.txt"
ASAN_SUFFIX = ".asan.txt"
FUZZ_SUFFIX = ".fuzz.txt"


def _load_dynamic(path: str = "config/tools.yaml") -> dict:
    with open(path) as f:
        return yaml.safe_load(f).get("dynamic", {})


def _spec_for(task_id: int) -> HarnessSpec | None:
    p = SPEC_DIR / str(task_id) / "spec.json"
    if not p.exists():
        return None
    try:
        return HarnessSpec.load(task_id)
    except Exception:  # noqa: BLE001
        return None


def _write_report(src: str, suffix: str, lines: list[str]) -> None:
    if not lines:
        return
    out = src[:-2] + suffix
    with open(out, "w") as f:
        f.write("\n".join(lines) + "\n")


def _compilable(src: str, clang: str | None) -> bool:
    """Fast plain-compile pre-check (syntax only, no sanitizers/driver).

    Non-compilable code must never be executed and must not burn driver-combo
    attempts: its compile errors are already fed back to the LLM through the
    static gate (.gcc.txt), which is the designated healing channel for them.
    If the check itself errors, fall through to the normal path.
    """
    import shutil as _sh
    import subprocess as _sp

    cc = clang or _sh.which("clang") or "/usr/bin/clang"
    try:
        p = _sp.run([cc, "-fsyntax-only", "-w", src],
                    capture_output=True, timeout=30)
        return p.returncode == 0
    except Exception:  # noqa: BLE001
        return True


def _fuzz_section(
    src: str,
    task_id: int,
    sample: int,
    basename: str,
    fuzz_budget: int,
    afl_bin: str,
    afl_cc: str,
    clang: str | None,
    afl_lib: str | None,
) -> list[str]:
    """Run the AFL++ pass for one file and ALWAYS write a .fuzz.txt marker.

    The marker (line-0 info lines are never comment targets) distinguishes
    'fuzzed, nothing found' / 'no fuzzable interface' from 'not fuzzed yet',
    which makes fuzz-aware caching idempotent.
    """
    if not _compilable(src, clang):
        _write_report(src, FUZZ_SUFFIX,
                      [f"{basename}.c:0:0: info: not fuzzed - not compilable"])
        return []
    if not detect_input_consumption(Path(src).read_text(errors="replace")):
        _write_report(src, FUZZ_SUFFIX,
                      [f"{basename}.c:0:0: info: no fuzzable input interface"])
        return []
    findings = fuzz_program(
        src, task_id, sample,
        afl_bin=afl_bin, afl_cc=afl_cc, clang=clang,
        budget=fuzz_budget, afl_lib=afl_lib,
    )
    if findings:
        lines = [
            f"{basename}.c:{f['line']}:{f['col']}:{f['severity']}:{f['message']}"
            for f in findings
        ]
    else:
        lines = [f"{basename}.c:0:0: info: fuzzed - no sanitizer findings"]
    _write_report(src, FUZZ_SUFFIX, lines)
    return lines


def _process_one(
    src: str,
    timeout: float,
    mem_mb: int,
    fuzz: bool,
    fuzz_budget: int,
    afl_bin: str,
    afl_cc: str,
    clang: str,
    afl_lib: str | None = None,
) -> tuple[str, int]:
    m = PROBLEM_RE.match(Path(src).stem)
    if not m:
        return "skip", 0
    task_id, sample = int(m.group(1)), int(m.group(3) or 1)
    basename = Path(src).stem

    # Fuzz-aware caching: a file is fully done when its .test.txt exists AND
    # (fuzz off, or its .fuzz.txt marker exists). Partially-done files only
    # run the missing part — a fuzz-only pass never re-runs the test oracle.
    test_done = os.path.exists(src[:-2] + TEST_SUFFIX)
    fuzz_done = os.path.exists(src[:-2] + FUZZ_SUFFIX)
    if test_done and (not fuzz or fuzz_done):
        return "already-done", 0
    if test_done and fuzz and not fuzz_done:
        _fuzz_section(src, task_id, sample, basename, fuzz_budget,
                      afl_bin, afl_cc, clang, afl_lib)
        return "fuzz-only", 1

    # Non-compilable code is never executed and never analyzed dynamically:
    # skip straight to the marker report. The compile errors themselves are
    # returned to the LLM as healing feedback via the static channel
    # (.gcc.txt), so 'not compilable' is an outcome the model must heal.
    if not _compilable(src, clang):
        _write_report(src, TEST_SUFFIX, [
            f"{basename}.c:0:0: error: not compilable - dynamic analysis "
            "skipped; compile errors are reported by the static channel"
        ])
        if fuzz:
            _write_report(src, FUZZ_SUFFIX,
                          [f"{basename}.c:0:0: info: not fuzzed - not compilable"])
        return "not-compilable", 1

    spec = _spec_for(task_id)

    if spec is None:
        _write_report(src, TEST_SUFFIX, [f"{basename}.c:0:0: error: no harness spec (unparseable task)"])
        if fuzz:
            _write_report(src, FUZZ_SUFFIX,
                          [f"{basename}.c:0:0: info: not fuzzed - no harness spec"])
        return "no-spec", 1

    outcome = run_one(Path(src), spec, timeout=timeout, mem_mb=mem_mb)

    # ---- functional test report (.test.txt) ----
    test_lines: list[str] = []
    if outcome.mode == "none":
        test_lines.append(f"{basename}.c:0:0: error: no testable interface ({'; '.join(outcome.notes)})")
    elif not outcome.compiled:
        test_lines.append(f"{basename}.c:0:0: error: could not compile under sanitizers ({'; '.join(outcome.notes)})")
    elif outcome.mode == "cli":
        test_lines.append(f"{basename}.c:0:0: info: CLI mode exercised via stdin")
    elif outcome.test_failures:
        for f_ in outcome.test_failures:
            test_lines.append(
                f"{basename}.c:{outcome.func_line}:0: error: test case {f_['case']} failed: "
                f"expected {f_['expected']}, got {f_['got']}"
            )
    else:
        n = len(spec.test_cases)
        test_lines.append(f"{basename}.c:0:0: info: all {n} test cases passed")
    _write_report(src, TEST_SUFFIX, test_lines)

    # ---- sanitizer findings (.asan.txt) ----
    asan_lines = [
        f"{basename}.c:{f['line']}:{f['col']}:{f['severity']}:{f['message']}"
        for f in outcome.asan_findings
    ]
    _write_report(src, ASAN_SUFFIX, asan_lines)

    # ---- fuzzing (.fuzz.txt) ----
    fuzz_lines: list[str] = []
    if fuzz and not fuzz_done:
        fuzz_lines = _fuzz_section(src, task_id, sample, basename, fuzz_budget,
                                   afl_bin, afl_cc, clang, afl_lib)

    return "ok", len(asan_lines) + len(test_lines) + len(fuzz_lines)


def analyze_dynamic(
    source_dir: str,
    task_ids: set[int] | None = None,
    timeout: float | None = None,
    fuzz: bool = False,
    workers: int = 4,
    clang: str | None = None,
) -> dict:
    """Run the dynamic channel over every .c in source_dir. Returns counts."""
    cfg = _load_dynamic()
    timeout = timeout if timeout is not None else float(cfg.get("timeout_s", 5))
    mem_mb = int(cfg.get("mem_limit_mb", 512))
    fuzz_budget = int(cfg.get("fuzz_budget_s", 60))
    afl_bin = cfg.get("afl_bin", "afl-fuzz")
    afl_cc = cfg.get("afl_cc", "afl-clang-fast")
    afl_lib = cfg.get("afl_lib")

    files = [f for f in sorted(os.listdir(source_dir)) if f.endswith(".c")]
    # Skip fully-analyzed files — makes chain restarts cheap. Without fuzz a
    # .test.txt report marks a processed file; with fuzz BOTH the test report
    # and the .fuzz.txt marker must exist (partially-done files fall through
    # and only the missing part runs inside _process_one).
    def _fully_done(fname: str) -> bool:
        base = os.path.join(source_dir, fname[:-2])
        if not os.path.exists(base + TEST_SUFFIX):
            return False
        return (not fuzz) or os.path.exists(base + FUZZ_SUFFIX)

    files = [f for f in files if not _fully_done(f)]
    if task_ids is not None:
        files = [
            f for f in files
            if (m := PROBLEM_RE.match(Path(f).stem)) and int(m.group(1)) in task_ids
        ]
    if not files:
        return {}

    counts: dict[str, int] = {}
    with ThreadPoolExecutor(max_workers=workers) as pool:
        futures = {
            pool.submit(_process_one, os.path.join(source_dir, f), timeout, mem_mb, fuzz, fuzz_budget, afl_bin, afl_cc, clang, afl_lib): f
            for f in files
        }
        for fut in tqdm(as_completed(futures), total=len(futures), desc="Dynamic analysis: "):
            try:
                kind, n = fut.result()
                counts[kind] = counts.get(kind, 0) + 1
            except Exception as ex:  # noqa: BLE001
                print(f"[warn] dynamic analysis failed for a file: {ex}")
    return counts


if __name__ == "__main__":
    import sys

    src_dir = sys.argv[1]
    fuzz = "--fuzz" in sys.argv
    print(analyze_dynamic(src_dir, fuzz=fuzz))
