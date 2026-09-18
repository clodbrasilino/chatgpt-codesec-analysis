"""Data-level audit of annotation fidelity in the main s+d+fuzz cells.

Verifies, for every stored annotated source (heal_N/to_be_healed/*.c), that it
faithfully reflects the tool report files of the code it was derived from
(heal_{N-1}/healed for N>=2, heal_0 for N=1), using the SAME parsing and
injection code as the pipeline (src/pipeline/comment_inject.py).

Classification per (model, round, basename):
  MATCH        stored annotation == re-simulated injection from current reports
  FUZZ-GAP     stored lacks >=1 fuzz message implied by current reports
  TEST-GAP     stored lacks >=1 test/oracle message implied by current reports
  STATIC-GAP   stored lacks >=1 static message implied by current reports
  EXTRA        stored has messages not implied by current reports
  ORPHAN       stored exists but current reports have no injectable findings
  MISSING      current reports have findings but no stored annotation

Also audits outcome soundness from the manifests:
  clean_at_start -> heal_0 reports must be free of injectable findings
  clean at r     -> heal_r/healed reports must be free of injectable findings
  not_cleaned    -> last annotated round's healed reports must HAVE findings

Output: results/annotation_audit.md
"""
from __future__ import annotations

import json
import sys
from collections import Counter
from pathlib import Path

REPO = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(REPO))

from src.pipeline.comment_inject import (  # noqa: E402
    add_comments_to_weak_source,
    extract_standard_messages,
    _PROBLEM_RE,
)

SLUG = "feedback-static+dynamic-r0-t1.0-p1.0"
MODELS = [
    "deepseek-v4-pro", "qwen-max", "glm-5.1", "kimi-k3",
    "openai-gpt56-sol", "claude-fable-5", "gemini-3-pro",
]
SUFFIXES = [".gcc.txt", ".clang.txt", ".cppcheck.txt", ".flawfinder.txt",
            ".asan.txt", ".fuzz.txt", ".test.txt"]
PRE_FUZZ_CUTOFF = 20260915  # mtime (YYYYMMDD) separating run eras

FUZZ_MARKERS = ("AFL crash", "Fuzzing found")
TEST_MARKERS = ("test case",)


def findings_for(src_dir: Path, basename: str) -> dict[int, list[str]]:
    """Replicate comment_inject.get_problems_weaknesses for one file."""
    errors: dict[int, list[str]] = {}
    for suffix in SUFFIXES:
        p = src_dir / (basename + suffix)
        if p.is_file():
            for msg in extract_standard_messages(p.read_text(errors="replace")):
                if msg["line"] <= 0:
                    continue
                errors.setdefault(msg["line"], []).append(msg["message"])
    return errors


def stored_messages(text: str) -> Counter:
    """Extract messages from ' * ...' lines of comment blocks."""
    c: Counter = Counter()
    for line in text.splitlines():
        s = line.strip()
        if s.startswith("* ") and "Possible weaknesses" not in s:
            c[s[2:]] += 1
    return c


def normalize_blocks(text: str) -> str:
    """Order-insensitive canonical form: sort messages within each block.

    The injector iterates a Python set() per line, so block-internal message
    order is non-deterministic across processes; only the message multiset
    and placement are semantically meaningful.
    """
    out: list[str] = []
    block: list[str] = []
    in_block = False
    for line in text.splitlines():
        if "Possible weaknesses found:" in line:
            in_block = True
            block = [line]
        elif in_block and line.strip() == "*/":
            block.append(line)
            out.extend([block[0]] + sorted(block[1:-1]) + [block[-1]])
            in_block = False
        elif in_block:
            block.append(line)
        else:
            out.append(line)
    return "\n".join(out)


def sim_messages(errors: dict[int, list[str]]) -> Counter:
    c: Counter = Counter()
    for msgs in errors.values():
        for m in set(msgs):
            c[m] += 1
    return c


def gap_class(missing: list[str]) -> str | None:
    for m in missing:
        if any(k in m for k in FUZZ_MARKERS):
            return "FUZZ-GAP"
    for m in missing:
        if any(k in m for k in TEST_MARKERS):
            return "TEST-GAP"
    for m in missing:
        if any(k in m for k in ("UBSan", "ASan")):
            return "ORACLE-GAP"
    if missing:
        return "STATIC-GAP"
    return None


def audit_model(model: str) -> dict:
    cell = REPO / "collected_code_6" / model / SLUG
    rounds = sorted(
        int(d.name.split("_")[1])
        for d in cell.glob("heal_*")
        if d.is_dir() and d.name != "heal_0" and (d / "to_be_healed").is_dir()
    )
    counts: Counter = Counter()
    examples: dict[str, list[str]] = {}
    era_counts: Counter = Counter()
    last_active = 0

    def add(kind: str, key: str) -> None:
        counts[kind] += 1
        examples.setdefault(kind, [])
        if len(examples[kind]) < 6:
            examples[kind].append(key)

    for r in rounds:
        tbe = cell / f"heal_{r}" / "to_be_healed"
        src_dir = cell / "heal_0" if r == 1 else cell / f"heal_{r-1}" / "healed"
        stored_files = {p.stem: p for p in tbe.glob("problem-*.c")}
        fresh_here = any(
            p.stat().st_mtime >= 1789000000 for p in stored_files.values()
        )  # ~2026-09-15 in epoch seconds; sets last_active conservatively
        # find last active round via mtime below instead

        # (1) stored files
        for base, sp in sorted(stored_files.items()):
            if not _PROBLEM_RE.match(base):
                continue
            key = f"{model}/heal_{r}/{base}"
            mtime = sp.stat().st_mtime
            era = "fuzz" if mtime >= 1789027200 else "pre-fuzz"  # 2026-09-15 UTC approx
            errors = findings_for(src_dir, base)
            if not errors:
                add("ORPHAN", key)
                era_counts[(era, "ORPHAN")] += 1
                continue
            src = src_dir / f"{base}.c"
            if not src.is_file():
                add("NO-SOURCE", key)
                era_counts[(era, "NO-SOURCE")] += 1
                continue
            expected = add_comments_to_weak_source(
                src.read_text(errors="replace"), errors)
            actual = sp.read_text(errors="replace")
            if normalize_blocks(expected) == normalize_blocks(actual):
                add("MATCH", key)
                era_counts[(era, "MATCH")] += 1
            else:
                missing = list((sim_messages(errors) - stored_messages(actual)).elements())
                extra = list((stored_messages(actual) - sim_messages(errors)).elements())
                kind = gap_class(missing)
                if kind is None and extra:
                    kind = "EXTRA"
                if kind is None:
                    kind = "MISMATCH-OTHER"
                add(kind, key)
                era_counts[(era, kind)] += 1

        # (2) missing annotations: findings but no stored file
        if src_dir.is_dir():
            for p in sorted(src_dir.glob("problem-*.c")):
                base = p.stem
                if not _PROBLEM_RE.match(base):
                    continue
                if base in stored_files:
                    continue
                if findings_for(src_dir, base):
                    add("MISSING", f"{model}/heal_{r}/{base}")

        # track last active (fuzz-era) round
        for sp in stored_files.values():
            if sp.stat().st_mtime >= 1789027200:
                last_active = max(last_active, r)

    # ---- outcome soundness ----
    mani_path = REPO / "results" / model / f"{SLUG}.manifest.json"
    outcome_counts: Counter = Counter()
    outcome_examples: dict[str, list[str]] = {}

    def oadd(kind: str, key: str) -> None:
        outcome_counts[kind] += 1
        outcome_examples.setdefault(kind, [])
        if len(outcome_examples[kind]) < 6:
            outcome_examples[kind].append(key)

    if mani_path.is_file():
        mani = json.loads(mani_path.read_text())
        for base, rec in mani.get("outcomes", {}).items():
            r = rec.get("rounds_to_clean")
            out = rec.get("outcome")
            key = f"{model}/{base}({out}@r{r})"
            if out == "clean_at_start":
                if findings_for(cell / "heal_0", base):
                    oadd("clean_at_start-with-findings", key)
                else:
                    oadd("OK-clean_at_start", key)
            elif out == "clean":
                d = cell / f"heal_{r}" / "healed"
                if not (d / f"{base}.c").is_file():
                    oadd("clean-no-artifact", key)
                elif findings_for(d, base):
                    oadd("clean-with-findings", key)
                else:
                    oadd("OK-clean", key)
            elif out == "not_cleaned":
                # Last round where the file was BOTH annotated and repaired
                # (to_be_healed-only rounds are pre-fuzz-run leftovers with an
                # empty healed/ dir and must be ignored).
                last_r = 0
                for rr in rounds:
                    tbe_f = cell / f"heal_{rr}" / "to_be_healed" / f"{base}.c"
                    hea_f = cell / f"heal_{rr}" / "healed" / f"{base}.c"
                    if tbe_f.is_file() and hea_f.is_file():
                        last_r = rr
                if last_r == 0:
                    oadd("not_cleaned-no-round", key)
                    continue
                d = cell / f"heal_{last_r}" / "healed"
                if not (d / f"{base}.c").is_file():
                    oadd("not_cleaned-no-artifact", key)
                elif not findings_for(d, base):
                    oadd("NOT_CLEANED-BUT-DETECTION-FREE", key)
                else:
                    oadd("OK-not_cleaned", key)
            else:
                oadd(f"other:{out}", key)

    return {
        "counts": counts,
        "era_counts": era_counts,
        "examples": examples,
        "outcome_counts": outcome_counts,
        "outcome_examples": outcome_examples,
        "last_active_round": last_active,
    }


def main() -> None:
    lines = ["# Annotation audit — main s+d+fuzz cells", ""]
    total: Counter = Counter()
    total_out: Counter = Counter()
    for model in MODELS:
        res = audit_model(model)
        c = res["counts"]
        total.update(c)
        total_out.update(res["outcome_counts"])
        lines.append(f"## {model} (last fuzz-era round: {res['last_active_round']})")
        lines.append("")
        lines.append("| class | count |")
        lines.append("|---|---|")
        for k in ["MATCH", "FUZZ-GAP", "TEST-GAP", "ORACLE-GAP", "STATIC-GAP",
                  "EXTRA", "MISMATCH-OTHER", "ORPHAN", "MISSING", "NO-SOURCE"]:
            if c.get(k):
                lines.append(f"| {k} | {c[k]} |")
        lines.append("")
        era = res["era_counts"]
        if era:
            lines.append("By file era (pre-fuzz = mtime < 2026-09-15):")
            lines.append("")
            lines.append("| era | class | count |")
            lines.append("|---|---|---|")
            for (e, k), v in sorted(era.items()):
                lines.append(f"| {e} | {k} | {v} |")
            lines.append("")
        oc = res["outcome_counts"]
        lines.append("Outcome soundness:")
        lines.append("")
        lines.append("| check | count |")
        lines.append("|---|---|")
        for k, v in sorted(oc.items()):
            lines.append(f"| {k} | {v} |")
        lines.append("")
        for kind, exs in res["examples"].items():
            if kind in ("MATCH",):
                continue
            lines.append(f"Examples `{kind}`: {', '.join(exs)}")
        for kind, exs in res["outcome_examples"].items():
            if kind.startswith("OK"):
                continue
            lines.append(f"Examples `{kind}`: {', '.join(exs)}")
        lines.append("")
    lines.append("## TOTAL across 7 models")
    lines.append("")
    lines.append("| class | count |")
    lines.append("|---|---|")
    for k, v in sorted(total.items()):
        lines.append(f"| {k} | {v} |")
    lines.append("")
    lines.append("Outcome totals:")
    lines.append("")
    lines.append("| check | count |")
    lines.append("|---|---|")
    for k, v in sorted(total_out.items()):
        lines.append(f"| {k} | {v} |")
    lines.append("")
    out = REPO / "results" / "annotation_audit.md"
    out.write_text("\n".join(lines))
    print(f"written {out}")
    print("TOTALS:", dict(total))
    print("OUTCOMES:", dict(total_out))


if __name__ == "__main__":
    main()
