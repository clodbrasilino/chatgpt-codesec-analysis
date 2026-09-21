"""Reprocess step 1: quarantine annotation-gap artifacts as .bak renames.

Identifies repair-round annotations whose stored content lacks findings present
in the current reports of the code they annotate (FUZZ/TEST/ORACLE/STATIC gaps
per the annotation audit semantics), and renames all trajectory artifacts of
the affected samples from their earliest gap round onward to <name>.bak.

A subsequent skip-existing rerun of the cell (the standard chain command)
then regenerates annotations, repairs, and reports for exactly those samples
with complete feedback, and rewrites the manifest.

Renames are in-place (no deletions — the bulk-delete guard is never touched);
the pre-reprocess trajectory stays recoverable via the .bak files and git.
"""
from __future__ import annotations

import sys
from pathlib import Path

REPO = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(REPO))

from src.analysis.annotation_audit import (  # noqa: E402
    MODELS,
    SLUG,
    findings_for,
    gap_class,
    normalize_blocks,
    sim_messages,
    stored_messages,
)
from src.pipeline.comment_inject import (  # noqa: E402
    _PROBLEM_RE,
    add_comments_to_weak_source,
)

GAP_KINDS = {"FUZZ-GAP", "TEST-GAP", "ORACLE-GAP", "STATIC-GAP"}
HEALED_SUFFIXES = [
    ".c", ".txt", ".o",
    ".gcc.txt", ".clang.txt", ".cppcheck.txt", ".flawfinder.txt",
    ".asan.txt", ".test.txt", ".fuzz.txt",
]


def quarantine_model(model: str, max_round: int | None = None) -> tuple[int, int]:
    """Quarantine gap artifacts for one model.

    ``max_round`` defaults to ``None`` = every healing round that exists on
    disk, so artifacts collected under an earlier, larger budget remain
    visible. Pass an explicit int to restrict the scan.
    """
    cell = REPO / "collected_code_6" / model / SLUG
    rounds = sorted(
        int(d.name.split("_")[1])
        for d in cell.glob("heal_*")
        if d.name != "heal_0" and (d / "to_be_healed").is_dir()
    )
    rounds = [r for r in rounds if r >= 1 and (max_round is None or r <= max_round)]

    affected: dict[str, int] = {}
    for r in rounds:
        tbe = cell / f"heal_{r}" / "to_be_healed"
        src_dir = cell / "heal_0" if r == 1 else cell / f"heal_{r-1}" / "healed"
        for sp in sorted(tbe.glob("problem-*.c")):
            base = sp.stem
            if not _PROBLEM_RE.match(base):
                continue
            errors = findings_for(src_dir, base)
            if not errors:
                continue
            src = src_dir / f"{base}.c"
            if not src.is_file():
                continue
            expected = add_comments_to_weak_source(
                src.read_text(errors="replace"), errors)
            actual = sp.read_text(errors="replace")
            if normalize_blocks(expected) == normalize_blocks(actual):
                continue
            missing = list(
                (sim_messages(errors) - stored_messages(actual)).elements())
            if gap_class(missing) in GAP_KINDS:
                affected[base] = min(affected.get(base, max_round + 1), r)

    renamed = 0
    lines = []
    for base, e in sorted(affected.items()):
        lines.append(f"{base} {e}")
        for r in range(e, max_round + 1):
            p = cell / f"heal_{r}" / "to_be_healed" / f"{base}.c"
            if p.is_file():
                bak = p.with_name(p.name + ".bak")
                if not bak.exists():
                    p.rename(bak)
                    renamed += 1
            hd = cell / f"heal_{r}" / "healed"
            for suf in HEALED_SUFFIXES:
                p = hd / f"{base}{suf}"
                if p.is_file():
                    bak = p.with_name(p.name + ".bak")
                    if not bak.exists():
                        p.rename(bak)
                        renamed += 1
    (REPO / "results" / f"reprocess_{model}.txt").write_text(
        "\n".join(lines))
    return len(affected), renamed


def main() -> None:
    total_samples = total_renamed = 0
    for model in MODELS:
        n, k = quarantine_model(model)
        total_samples += n
        total_renamed += k
        print(f"{model}: {n} samples quarantined, {k} artifacts renamed to .bak")
    print(f"TOTAL: {total_samples} samples, {total_renamed} renames")


if __name__ == "__main__":
    main()
