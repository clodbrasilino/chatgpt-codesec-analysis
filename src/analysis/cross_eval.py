"""Cross-evaluation: run each channel on the OTHER arm's final code.

For every model, both single-channel arms repair the same 4,200
programs (200-problem vulnerable-prone subset x 3 samples; the
dynamic-only cells import the round-0 code of the static-only cells).
To place all arms on a common criterion we evaluate:

  direction A (static on dynamic finals):
      the four static analyzers on the FINAL version of every program
      of the dynamic-only cells -> how much static residue does a
      dynamic-only termination leave?

  direction B (dynamic on static finals):
      tests + sanitizer oracle (NO fuzzing -- scope decision) on the
      FINAL version of every program of the static-only cells ->
      does static-only termination imply dynamic cleanliness?

FINAL version = the latest .c across heal_0 and heal_1..5/healed for
each program (round-0 code when never repaired).

Outputs land under cross_eval/{model}/{from_dynamic|from_static}/
(sources + reports), progress in results/cross_eval_progress.json.

Usage:
  python -m src.analysis.cross_eval static  <model>
  python -m src.analysis.cross_eval dynamic <model>
"""
from __future__ import annotations

import json
import re
import shutil
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(REPO))
from src.pipeline import static as st                     # noqa: E402
from src.pipeline.run_experiment import _run_dynamic      # noqa: E402

R = REPO / "results"
S_SLUG = "feedback-static-r0-t1.0-p1.0"
D_SLUG = "feedback-dynamic-r0-t1.0-p1.0"
ROUNDS = 5
OUTROOT = REPO / "cross_eval"
KEY_RE = re.compile(r"^problem-(?:\d+)(?:-s\d+)?$")
PROGRESS = R / "cross_eval_progress.json"


def final_source(cell_dir: Path, base: str) -> Path | None:
    """Latest .c for base across heal_0 and heal_1..5/healed."""
    best = None
    candidates = [(0, cell_dir / "heal_0" / f"{base}.c")]
    for r in range(1, ROUNDS + 1):
        candidates.append((r, cell_dir / f"heal_{r}" / "healed" / f"{base}.c"))
    for _, p in candidates:          # rounds ascend: last existing wins
        if p.is_file():
            best = p
    return best


def gather(model: str, src_slug: str, bases: set[str], outdir: Path) -> int:
    outdir.mkdir(parents=True, exist_ok=True)
    cell = REPO / "collected_code_6" / model / src_slug
    n = 0
    for base in sorted(bases):
        src = final_source(cell, base)
        if src is None:
            continue
        dst = outdir / f"{base}.c"
        if not dst.exists() or dst.stat().st_size != src.stat().st_size:
            shutil.copyfile(src, dst)
        n += 1
    return n


def run_direction(direction: str, model: str) -> None:
    dyn_man = json.load(open(R / model / f"{D_SLUG}.manifest.json"))
    bases = {k for k in dyn_man["outcomes"] if KEY_RE.match(k)}
    outdir = OUTROOT / model / ("from_dynamic" if direction == "static"
                                else "from_static")
    src_slug = D_SLUG if direction == "static" else S_SLUG
    n = gather(model, src_slug, bases, outdir)
    print(f"[{model}/{direction}] gathered {n} final sources -> {outdir}",
          flush=True)
    if direction == "static":
        counts = st.analyze(str(outdir),
                            tools=["gcc", "clang", "cppcheck", "flawfinder"],
                            compile_gate=True)
    else:
        counts = _run_dynamic(str(outdir), model, fuzz=False)
    prog = json.loads(PROGRESS.read_text()) if PROGRESS.is_file() else {}
    prog.setdefault(model, {})[direction] = {"programs": n,
                                             "counts": str(counts)}
    PROGRESS.write_text(json.dumps(prog, indent=1))
    print(f"[{model}/{direction}] done: {counts}", flush=True)


if __name__ == "__main__":
    if len(sys.argv) != 3 or sys.argv[1] not in ("static", "dynamic"):
        print(__doc__)
        sys.exit(2)
    run_direction(sys.argv[1], sys.argv[2])
