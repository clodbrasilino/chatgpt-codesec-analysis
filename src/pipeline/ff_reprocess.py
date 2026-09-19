"""Flawfinder reprocess stages 1-2: convert reports, quarantine trajectories.

Stage 1 — convert every raw .flawfinder.txt under collected_code_6 to the
normalized standard format (in place; no-hits reports become empty files,
matching the other analyzers). The qwen legacy cell is never touched.

Stage 2 — for every cell whose feedback includes the static channel
(feedback-static*), find each program's EARLIEST round whose feedback was
incomplete due to the flawfinder gap: the first round r such that the
flawfinder report of the round-(r-1) code contains at least one hit.
Rename all trajectory artifacts of that program from round r onward to
*.bak (or *.bak2 when a .bak already exists from the earlier gap
reprocess), so a skip-existing rerun regenerates them with complete
feedback. Programs that were detection-free at generation but have
round-0 flawfinder hits have no artifacts to rename; the rerun will
flag and repair them naturally.
"""
from __future__ import annotations

import re
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(REPO))

from src.pipeline.flawfinder_norm import extract_flawfinder_raw  # noqa: E402
from src.pipeline.comment_inject import extract_standard_messages  # noqa: E402

ROOT = REPO / "collected_code_6"
LEGACY_MARKER = "legacy"
HEALED_SUFFIXES = [
    ".c", ".txt", ".o",
    ".gcc.txt", ".clang.txt", ".cppcheck.txt", ".flawfinder.txt",
    ".asan.txt", ".test.txt", ".fuzz.txt",
]
RAW_HEADER = "Flawfinder version"


def has_hits(report: Path) -> bool:
    """True if the (converted or raw) flawfinder report has >=1 injectable hit."""
    try:
        text = report.read_text(errors="replace")
    except OSError:
        return False
    for msg in extract_standard_messages(text) + extract_flawfinder_raw(text):
        if msg["line"] > 0:
            return True
    return False


def stage1_convert() -> tuple[int, int]:
    converted = kept = 0
    for ff in ROOT.rglob("*.flawfinder.txt"):
        if LEGACY_MARKER in str(ff):
            continue
        try:
            text = ff.read_text(errors="replace")
        except OSError:
            continue
        if RAW_HEADER in text:
            from src.pipeline.flawfinder_norm import normalize_report
            base = ff.name[: -len(".flawfinder.txt")]
            ff.write_text(normalize_report(text, base))
            converted += 1
        else:
            kept += 1
    return converted, kept


def rename_with_suffix(p: Path) -> bool:
    for suf in (".bak", ".bak2", ".bak3"):
        bak = p.with_name(p.name + suf)
        if not bak.exists():
            p.rename(bak)
            return True
    return False


def stage2_quarantine_cell(cell: Path) -> tuple[int, int, int]:
    """Returns (programs_affected, programs_with_hits_at_r0, renames)."""
    affected: dict[str, int] = {}
    r0_hits: set[str] = set()
    # earliest affected round per program
    for ff in (cell / "heal_0").glob("*.flawfinder.txt"):
        base = ff.name[: -len(".flawfinder.txt")]
        if has_hits(ff):
            affected[base] = 1
            r0_hits.add(base)
    max_round = 10
    for r in range(1, max_round + 1):
        healed = cell / f"heal_{r}" / "healed"
        if not healed.is_dir():
            continue
        for ff in healed.glob("*.flawfinder.txt"):
            base = ff.name[: -len(".flawfinder.txt")]
            if base in affected:
                continue  # already quarantined from an earlier round
            if has_hits(ff):
                affected[base] = r + 1
    renames = 0
    lines = []
    for base, r0 in sorted(affected.items()):
        lines.append(f"{base} {r0}")
        for r in range(r0, max_round + 1):
            p = cell / f"heal_{r}" / "to_be_healed" / f"{base}.c"
            if p.is_file() and rename_with_suffix(p):
                renames += 1
            hd = cell / f"heal_{r}" / "healed"
            for suf in HEALED_SUFFIXES:
                p = hd / f"{base}{suf}"
                if p.is_file() and rename_with_suffix(p):
                    renames += 1
    slug = cell.parent.name + "__" + cell.name
    out = REPO / "results" / f"ff_reprocess_{slug}.txt"
    out.write_text("\n".join(lines))
    return len(affected), len(r0_hits), renames


def main() -> None:
    print("== stage 1: converting flawfinder reports ==", flush=True)
    converted, kept = stage1_convert()
    print(f"converted {converted} raw reports; {kept} already normalized",
          flush=True)

    print("== stage 2: quarantining affected trajectories ==", flush=True)
    cells = []
    for model_dir in sorted(ROOT.iterdir()):
        if not model_dir.is_dir():
            continue
        for cell in sorted(model_dir.iterdir()):
            if not cell.is_dir():
                continue
            name = cell.name
            if LEGACY_MARKER in name:
                continue
            if name.startswith("feedback-static"):
                cells.append(cell)
    tot_p = tot_r0 = tot_ren = 0
    for cell in cells:
        n, n0, k = stage2_quarantine_cell(cell)
        tot_p += n
        tot_r0 += n0
        tot_ren += k
        print(f"{cell.parent.name}/{cell.name}: affected={n} "
              f"(r0-hits={n0}) renames={k}", flush=True)
    print(f"TOTAL affected programs={tot_p} (with round-0 hits={tot_r0}), "
          f"renames={tot_ren}", flush=True)
    marker = Path("/tmp/ff_reprocess_started")
    marker.write_text("ok\n")


if __name__ == "__main__":
    main()
