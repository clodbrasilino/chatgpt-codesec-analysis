"""AFL++ fuzzing wrapper for stdin/argv-consuming generated programs.

Only programs whose ``main`` consumes input (scanf/fgets/gets/getchar/
argc/argv/fread/read) are fuzzed — self-contained function-only programs
are covered by the sanitizer test oracle instead (see ``harness/run.py``).

Pipeline per source file:

1. compile with ``afl-clang-fast`` (+ ASan via ``AFL_USE_ASAN=1``; falls
   back to instrumentation-only if the ASan build fails);
2. seed the corpus with the empty input and (when available) stdin
   serializations of the MBPP oracle arguments;
3. run ``afl-fuzz -V <budget>`` for up to ``budget`` seconds;
4. re-execute each crash input under the instrumented build, parse
   ASan/UBSan reports, and map findings back to source lines.

Degrades gracefully: if afl-fuzz is not installed the caller gets an empty
finding list (the primary dynamic channel, sanitizer test-runs, is
unaffected).
"""
from __future__ import annotations

import os
import re
import shutil
import subprocess
import tempfile
import time
from pathlib import Path

from ..harness.find_function import detect_input_consumption
from ..harness.mbpp_loader import SPEC_DIR, HarnessSpec
from ..harness.run import SANITIZERS, _parse_sanitizer, archive_scratch

REPO_ROOT = Path(__file__).resolve().parents[2]
AFL_ROOT = REPO_ROOT / "build" / "afl"  # AFL++ installation (bin/, lib/afl)
# Fuzz session scratch goes to the system temp dir: the host's bulk-delete
# guard kills the process when >=50 files inside a project path are deleted,
# and an AFL out/ queue easily holds 60+ files.
FUZZ_ROOT = Path(tempfile.gettempdir()) / "chatgpt-codesec-analysis" / "fuzz"


def _seeds_from_spec(spec: HarnessSpec | None, argv_mode: bool) -> list[bytes]:
    # AFL++ rejects zero-length test cases, so the fallback seed is a single
    # NUL byte rather than an empty file.
    seeds = [b"\x00"]
    if spec is None or argv_mode:
        return seeds
    for tc in spec.test_cases:
        # Best-effort stdin serialization: each arg on its own line.
        lines = []
        for a in tc.args:
            if isinstance(a, (list, tuple)):
                lines.append(" ".join(str(x) for x in a))
            else:
                lines.append(str(a))
        s = ("\n".join(lines)).encode()
        if s:
            seeds.append(s)
    return seeds


def fuzz_program(
    source: str,
    task_id: int,
    sample: int = 1,
    afl_bin: str = "afl-fuzz",
    afl_cc: str = "afl-clang-fast",
    clang: str | None = None,
    budget: int = 60,
    timeout: int = 5,
    afl_lib: str | None = None,
) -> list[dict]:
    """Fuzz one C file; return sanitizer findings mapped to source lines.

    Two-binary design (macOS 26 quirk): the LLVM toolchain that provides
    AFL instrumentation (Homebrew clang 21) has a broken ASan runtime on
    this OS, while the platform clang (Apple, CLT 26.6) has a working one.
    So we fuzz with an AFL-instrumented + UBSan build (crashes surface as
    signals / stack-protector aborts) and then *replay* every crash input
    under a platform-clang ASan+UBSan build for precise line attribution.
    """
    afl_fuzz = shutil.which(afl_bin) or (afl_bin if os.path.isfile(afl_bin) else None)
    if afl_fuzz is None:
        print("[warn] afl-fuzz not found; skipping fuzzing channel")
        return []
    afl_compiler = (
        shutil.which(afl_cc) or (afl_cc if os.path.isfile(afl_cc) else None)
        or shutil.which("afl-clang") or shutil.which("afl-gcc-fast")
    )
    if afl_compiler is None:
        print(f"[warn] {afl_cc} not found; skipping fuzzing channel")
        return []
    afl_fuzz = os.path.abspath(afl_fuzz)
    afl_compiler = os.path.abspath(afl_compiler)
    replay_cc = clang or shutil.which("clang") or "/usr/bin/clang"

    src = Path(source)
    basename = src.stem
    workdir = FUZZ_ROOT / basename
    if workdir.exists():
        shutil.rmtree(workdir)
    workdir.mkdir(parents=True, exist_ok=True)

    # --- fuzz build: AFL instrumentation + UBSan (never ASan; broken here) ---
    prog = workdir / "prog"
    env = dict(os.environ)
    if afl_lib:
        env["AFL_PATH"] = afl_lib  # compiler-rt objects + LLVM passes
    env["AFL_USE_UBSAN"] = "1"
    build_cmd = [afl_compiler, "-g", "-O1", "-w", str(src), "-o", str(prog)]
    p = subprocess.run(build_cmd, capture_output=True, text=True, env=env, timeout=180)
    if p.returncode != 0:
        env.pop("AFL_USE_UBSAN", None)
        p = subprocess.run(build_cmd, capture_output=True, text=True, env=env, timeout=180)
    if p.returncode != 0:
        print(f"[warn] AFL build failed for {basename}")
        return []

    # --- replay build: platform clang with the full sanitizer stack ---
    replay_prog = workdir / "replay"
    rp = subprocess.run(
        [replay_cc, "-g", "-O1", "-w", f"-fsanitize={SANITIZERS}",
         str(src), "-o", str(replay_prog)],
        capture_output=True, text=True, timeout=180,
    )
    have_replay = rp.returncode == 0

    # --- input interface ---
    tokens = detect_input_consumption(src.read_text(errors="replace"))
    argv_mode = any(t in tokens for t in ("argc", "argv"))
    spec = None
    sp = SPEC_DIR / str(task_id) / "spec.json"
    if sp.exists():
        try:
            spec = HarnessSpec.load(task_id)
        except Exception:  # noqa: BLE001
            spec = None
    seeds_dir = workdir / "seeds"
    seeds_dir.mkdir(exist_ok=True)
    for i, s in enumerate(_seeds_from_spec(spec, argv_mode)):
        (seeds_dir / f"seed{i}").write_bytes(s)

    # --- run AFL++ ---
    out_dir = workdir / "out"
    env["AFL_SKIP_CPUFREQ"] = "1"                    # no cpufreq sysfs on macOS
    env["AFL_I_DONT_CARE_ABOUT_MISSING_CRASHES"] = "1"  # macOS crash-report quirks
    env.setdefault("AFL_NO_UI", "1")                 # non-interactive runs
    cmd = [afl_fuzz, "-i", str(seeds_dir), "-o", str(out_dir), "-V", str(budget),
           "-m", "none", "-t", str(timeout * 1000 + 2000), "--", str(prog)]
    if argv_mode:
        cmd.append("@@")
    subprocess.run(cmd, capture_output=True, text=True, timeout=budget + 60, env=env)

    # --- replay crashes under the sanitizer build (fallback: signal report) ---
    # AFL++ >=4 auto-creates a per-session subdir ("default") when no -M/-S is
    # given, so crashes may live in out/crashes or out/default/crashes.
    crashes_dir = out_dir / "crashes"
    if not crashes_dir.exists():
        crashes_dir = out_dir / "default" / "crashes"
    findings: list[dict] = []
    seen: set[tuple] = set()
    # Fallback anchor for signal-only crashes: first function / main line.
    anchor_line = 1
    m = re.search(r"(?m)^\s*(?:int|void)\s+main\s*\(", src.read_text(errors="replace"))
    if m:
        anchor_line = src.read_text(errors="replace")[: m.start()].count("\n") + 1

    def _replay(binary: str, crash: Path) -> subprocess.CompletedProcess | None:
        try:
            if argv_mode:
                return subprocess.run(
                    [binary, str(crash)], capture_output=True, text=True,
                    timeout=timeout, env=env,
                )
            return subprocess.run(
                ["bash", "-c", f"exec '{binary}' < '{crash}'"],
                capture_output=True, text=True, timeout=timeout, env=env,
            )
        except subprocess.TimeoutExpired:
            return None

    if crashes_dir.exists():
        for crash in sorted(crashes_dir.iterdir()):
            if crash.name in ("README.txt",) or crash.stat().st_size == 0:
                continue
            reported = False
            if have_replay:
                r = _replay(str(replay_prog), crash)
                if r is not None:
                    for f in _parse_sanitizer(r.stderr + "\n" + r.stdout, basename):
                        key = (f["line"], f["col"], f["message"])
                        if key not in seen:
                            seen.add(key)
                            f["message"] = f"{f['message']} (AFL crash: {crash.name})"
                            findings.append(f)
                            reported = True
            if not reported:
                # Signal crash without sanitizer attribution (e.g. no replay
                # build or ASan did not flag it) — still record the defect.
                r = _replay(str(prog), crash)
                if r is not None and r.returncode < 0:
                    key = (anchor_line, 0, f"signal {-r.returncode}")
                    if key not in seen:
                        seen.add(key)
                        findings.append({
                            "line": anchor_line, "col": 0, "severity": "error",
                            "message": (
                                f"Fuzzing found a crash (signal {-r.returncode}) "
                                f"on input {crash.name}; likely memory-safety defect"
                            ),
                        })
    findings.sort(key=lambda f: (f["line"], f["col"]))

    # Permanent record: keep the whole session (fuzz + replay binaries, seeds,
    # AFL out/ queue, crash inputs, fuzzer_stats) under artifacts/ in the repo.
    # Merge-only — see archive_scratch for the no-deletion rationale.
    archive_scratch(workdir, src, "fuzz")

    return findings


if __name__ == "__main__":
    import sys

    src = sys.argv[1]
    task_id = int(sys.argv[2]) if len(sys.argv) > 2 else 0
    for f in fuzz_program(src, task_id):
        print(f"{f['line']}:{f['col']}: {f['severity']}: {f['message']}")
