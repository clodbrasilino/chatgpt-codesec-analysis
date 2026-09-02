"""Compile-and-run oracle for generated C sources (dynamic testing).

Two testable interfaces are supported:

- LINK  — a target function matching an MBPP candidate name exists; we append
  a generated driver (single TU, the LLM's ``main`` renamed via ``-Dmain=``),
  compile with ASan+UBSan, execute, and compare serialized results against
  the reference-Python oracle.
- CLI   — no usable target function but the program reads stdin/argv; we
  compile it as-is with sanitizers and run it with a trivial input to detect
  startup crashes and memory errors (no functional oracle).

Everything is built under ``build/{task_id}/`` and never touches the source
tree. Reports (``.asan.txt`` / ``.test.txt``) are written by
:mod:`src.dyn.runner`; this module only produces :class:`RunOutcome`.
"""
from __future__ import annotations

import json
import os
import re
import shutil
import subprocess
import tempfile
import time
from dataclasses import dataclass, field
from pathlib import Path

from ..harness.driver_gen import build_combos, render_driver
from ..harness.find_function import detect_input_consumption, find_function
from ..harness.mbpp_loader import HarnessSpec
from ..harness.translate import kind_of

REPO_ROOT = Path(__file__).resolve().parents[2]
# Scratch lives in the system temp dir, NOT in the repo: the host's bulk-delete
# guard kills the pipeline when >=50 files inside a project path are deleted
# (LINK-mode harness dirs hold one combined_N.c per test case and can exceed
# that). System temp is unguarded.
BUILD_ROOT = Path(tempfile.gettempdir()) / "chatgpt-codesec-analysis" / "build"
# Permanent archive root (survives reboots, unlike the temp scratch). Every
# sanitizer build and AFL++ session is copied here after its run, keyed by the
# source's repo-relative path, so collected data stays analyzable later.
ARTIFACT_ROOT = Path(
    os.environ.get("DYN_ARCHIVE_ROOT") or (REPO_ROOT / "artifacts")
)
DEFAULT_CLANG = "/usr/bin/clang"


def archive_scratch(scratch: Path, source: Path, kind: str) -> Path | None:
    """Copy a scratch dir into the permanent artifact tree (additive only).

    Repo-side deletions are blocked by the host's bulk-delete guard, so the
    archive is *merged* (``dirs_exist_ok=True``) and never removed by the
    pipeline; re-runs of the same source overwrite same-named files and keep
    the rest (union of all sessions). Set ``DYN_ARCHIVE=none`` to disable
    (e.g. throwaway dry-runs).

    Layout: ``artifacts/<repo-relative source path minus .c>/<kind>/`` —
    e.g. ``artifacts/collected_code_6/qwen-max/feedback-.../heal_0/
    to_be_healed/problem-42/build/``. Sources outside the repo fall back to
    ``artifacts/adhoc/<stem>/``.
    """
    if os.environ.get("DYN_ARCHIVE", "1").strip().lower() in ("none", "0", "false", "off"):
        return None
    src = Path(source)
    try:
        key = src.resolve().relative_to(REPO_ROOT).with_suffix("")
    except ValueError:
        key = Path("adhoc") / src.stem
    dst = ARTIFACT_ROOT / key / kind
    try:
        dst.mkdir(parents=True, exist_ok=True)
        shutil.copytree(scratch, dst, dirs_exist_ok=True)
        return dst
    except OSError as ex:
        # Archival must never break an experiment run — warn and continue.
        print(f"[warn] artifact archive failed for {key}/{kind}: {ex}")
        return None

# Sanitizer set for dynamic builds. Override with DYN_SANITIZERS (comma
# separated, e.g. "undefined" when ASan is unavailable on the host OS —
# see macOS 26.x ASan breakage) or via config/tools.yaml dynamic.sanitizers.
SANITIZERS = os.environ.get(
    "DYN_SANITIZERS", "address,undefined"
).strip().strip(",")

_ASAN_ERR_RE = re.compile(r"ERROR: AddressSanitizer: (\S+)")
# macOS ASan frames print "file.c:line" (no column); Linux prints "file.c:line:col".
_ASAN_FRAME_RE = re.compile(r"([\w./-]+\.[ch]):(\d+)(?::(\d+))?")
_UBSAN_RE = re.compile(r"([\w./-]+\.[ch]):(\d+):(\d+): runtime error: (.+)")


@dataclass
class RunOutcome:
    mode: str = "none"  # link | cli | none
    compiled: bool = False
    matched: bool = False  # a combo satisfied every oracle case
    func_name: str | None = None
    func_line: int = 0
    asan_findings: list[dict] = field(default_factory=list)
    test_failures: list[dict] = field(default_factory=list)
    notes: list[str] = field(default_factory=list)


def _values_match(a, b) -> bool:
    """Value-level comparison (numbers with tolerance, everything else exact)."""
    if isinstance(a, bool) or isinstance(b, bool):
        return bool(a) == bool(b)
    if isinstance(a, (int, float)) and isinstance(b, (int, float)):
        return abs(float(a) - float(b)) <= 1e-6 * max(1.0, abs(float(a)), abs(float(b)))
    return a == b


def _matches(expected, got_text: str) -> bool:
    """Compare one serialized C result to the Python oracle value."""
    t = got_text.strip()
    if not t or t == "(null)":
        return False
    k = kind_of(expected)
    try:
        if k in ("int-list", "float-list", "str-list", "bool-list"):
            got = json.loads(t)  # driver prints JSON-compatible arrays
            if not isinstance(got, list) or len(got) != len(expected):
                return False
            return all(_values_match(e, g) for e, g in zip(expected, got))
        if k == "bool":
            return int(t) == (1 if expected else 0)
        if k == "int":
            return int(t) == expected
        if k == "float":
            return _values_match(float(t), expected)
        if k == "str":
            return t == expected
    except (ValueError, TypeError, json.JSONDecodeError):
        return False
    return False


def _parse_sanitizer(stderr: str, basename: str) -> list[dict]:
    """Extract ASan/UBSan findings that point into the problem source.

    ``basename`` is the file stem (e.g. ``problem-1``); report frames carry
    ``problem-1.c`` (possibly with a path prefix), so match on stem+ext.
    """
    findings: list[dict] = []
    seen: set[tuple] = set()

    def _ours(fname: str) -> bool:
        from pathlib import Path as _P

        return _P(fname).stem == basename

    for m in _UBSAN_RE.finditer(stderr):
        fname, line, col, msg = m.groups()
        if _ours(fname):
            key = (int(line), int(col), "UBSan: " + msg)
            if key not in seen:
                seen.add(key)
                findings.append(
                    {"line": int(line), "col": int(col), "severity": "medium", "message": f"UBSan: {msg}"}
                )
    for m in _ASAN_ERR_RE.finditer(stderr):
        kind = m.group(1)
        tail = stderr[m.end() : m.end() + 4000]
        for fm in _ASAN_FRAME_RE.finditer(tail):
            fname, line, col = fm.groups()
            if _ours(fname):
                col_i = int(col) if col else 0
                key = (int(line), col_i, f"ASan: {kind}")
                if key not in seen:
                    seen.add(key)
                    findings.append(
                        {"line": int(line), "col": col_i, "severity": "high", "message": f"ASan: {kind}"}
                    )
                break
    findings.sort(key=lambda f: (f["line"], f["col"]))
    return findings


def _run_cmd(cmd: list[str], timeout: float, mem_mb: int, stdin_data: bytes = b"") -> tuple[int, str, str]:
    """Run with wall-clock timeout + address-space cap (ulimit)."""
    bash = ["bash", "-c", f"ulimit -v {int(mem_mb) * 1024}; exec " + " ".join(f"'{c}'" for c in cmd)]
    try:
        p = subprocess.run(bash, capture_output=True, input=stdin_data, timeout=timeout)
        return p.returncode, p.stdout.decode(errors="replace"), p.stderr.decode(errors="replace")
    except subprocess.TimeoutExpired:
        return -9, "", "(timed out)"


def _try_link(
    source: Path,
    basename: str,
    func: dict,
    spec: HarnessSpec,
    cases: list,
    timeout: float,
    mem_mb: int,
    budget_s: float,
    build_dir: Path,
    clang: str,
) -> RunOutcome:
    out = RunOutcome(mode="link", func_name=func["name"], func_line=func["line"])
    combos = build_combos(cases)
    if not combos:
        out.notes.append("no signature combos generated (unsupported arg/return types)")
        return out

    deadline = time.monotonic() + budget_s
    first_compiled: RunOutcome | None = None
    for ci, combo in enumerate(combos):
        if time.monotonic() > deadline:
            out.notes.append(f"combo budget exhausted after {ci} attempts")
            break
        try:
            driver = render_driver(combo, cases, func["name"])
        except ValueError as ex:
            out.notes.append(str(ex))
            continue
        # Single TU: append the driver to the problem source so the compiler
        # sees the real definition (no extern, no implicit declarations).
        combined = build_dir / f"combined_{ci}.c"
        combined.write_text(source.read_text(errors="replace") + "\n" + driver)
        prog = build_dir / f"prog_{ci}"
        cmd = [
            clang,
            f"-fsanitize={SANITIZERS}",
            "-g",
            "-O1",
            "-w",
            f"-Dmain=__mbpp_disabled_main",
            str(combined),
            "-o",
            str(prog),
        ]
        comp = subprocess.run(cmd, capture_output=True, text=True, timeout=120)
        if comp.returncode != 0:
            continue  # signature mismatch -> try next binding
        if not out.compiled:
            out.compiled = True
            out.notes.append(f"first compilable combo: #{ci}")
            first_compiled = RunOutcome(mode="link", compiled=True, func_name=func["name"], func_line=func["line"])

        rc, stdout, stderr = _run_cmd([str(prog)], timeout, mem_mb)
        findings = _parse_sanitizer(stderr, basename)
        if findings:
            out.asan_findings = findings
            out.notes.append(f"sanitizer findings at combo #{ci}")

        # Functional comparison against the oracle.
        lines = [l for l in stdout.splitlines() if l.startswith("case")]
        got_map = {}
        for l in lines:
            if ":" in l:
                idx, _, val = l.partition(":")
                try:
                    got_map[int(idx[4:])] = val
                except ValueError:
                    continue
        failures = []
        for i, (_, expected) in enumerate(cases):
            if i not in got_map:
                failures.append({"case": i, "expected": repr(expected), "got": "<no output>"})
            elif not _matches(expected, got_map[i]):
                failures.append({"case": i, "expected": repr(expected), "got": got_map[i]})
        out.test_failures = failures
        if not failures:
            out.matched = True
            out.notes.append(f"all {len(cases)} cases passed at combo #{ci}")
            return out
    if first_compiled is not None:
        # Return the best-effort outcome: no combo satisfied every case, but
        # something compiled and ran, so keep its sanitizer findings.
        return out
    out.notes.append("no combo compiled (signature mismatch or broken code)")
    return out


def _try_cli(
    source: Path,
    basename: str,
    timeout: float,
    mem_mb: int,
    build_dir: Path,
    clang: str,
) -> RunOutcome:
    out = RunOutcome(mode="cli")
    prog = build_dir / "prog"
    cmd = [
        clang,
        f"-fsanitize={SANITIZERS}",
        "-g",
        "-O1",
        "-w",
        str(source),
        "-o",
        str(prog),
    ]
    comp = subprocess.run(cmd, capture_output=True, text=True, timeout=120)
    if comp.returncode != 0:
        out.notes.append("CLI program does not compile")
        return out
    out.compiled = True
    # Feed a trivial stdin so scanf/fgets-based programs terminate quickly.
    rc, stdout, stderr = _run_cmd([str(prog)], timeout, mem_mb, stdin_data=b"\n\n\n")
    out.asan_findings = _parse_sanitizer(stderr, basename)
    if rc == -9:
        out.notes.append("CLI run timed out")
    return out


def run_one(
    source: Path,
    spec: HarnessSpec,
    timeout: float = 5.0,
    mem_mb: int = 512,
    budget_s: float = 30.0,
    clang: str | None = None,
    keep_build: bool = False,
) -> RunOutcome:
    """Run the dynamic oracle for one generated C file."""
    clang = clang or shutil.which("clang") or DEFAULT_CLANG
    src_text = source.read_text(errors="replace")
    basename = source.stem  # problem-{id} or problem-{id}-s{k}
    build_dir = BUILD_ROOT / basename
    if build_dir.exists():
        shutil.rmtree(build_dir)
    build_dir.mkdir(parents=True, exist_ok=True)

    cases = [(tc.args, tc.expected) for tc in spec.test_cases]

    # Prefer LINK when a candidate function exists and we have oracle cases.
    func = None
    if cases:
        func = find_function(src_text, spec.fn_candidates)
    if func is not None:
        out = _try_link(source, basename, func, spec, cases, timeout, mem_mb, budget_s, build_dir, clang)
        archive_scratch(build_dir, source, "build")
        if not keep_build:
            shutil.rmtree(build_dir, ignore_errors=True)
        return out

    # CLI fallback: no usable target function. If the program is a
    # self-contained program (it has a main), run it as-is under sanitizers
    # with a trivial stdin to surface crashes / memory errors.
    if cases and func is None and _has_main(src_text):
        out = _try_cli(source, basename, timeout, mem_mb, build_dir, clang)
        archive_scratch(build_dir, source, "build")
        if not keep_build:
            shutil.rmtree(build_dir, ignore_errors=True)
        return out

    out = RunOutcome(mode="none")
    out.notes.append("no testable interface (no target function, no main)")
    if not keep_build:
        shutil.rmtree(build_dir, ignore_errors=True)
    return out


def _has_main(source: str) -> bool:
    return bool(re.search(r"(?m)^\s*(?:int|void|char|unsigned|signed|long|short)\s+main\s*\(", source))
