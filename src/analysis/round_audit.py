"""Audit whether every cell has complete trajectory data through round 5.

Motivation: the healing-round budget is defined by experiment configuration
(``config/experiment.yaml -> experiment.max_rounds``), so every program must
have usable data through that many rounds (or must have reached a terminal
state before then). This audit reports, per cell, how many programs are
complete through the configured round cap and enumerates every program that
is not, with the reason.
"""
from __future__ import annotations

import json
import os
from pathlib import Path

from src.config import max_healing_rounds

REPO = Path(__file__).resolve().parents[2]
COLL = REPO / "collected_code_6"
RES = REPO / "results"
# Reporting cap: how many healing rounds the experiment configuration allows.
CAP = max_healing_rounds()

STATIC_SUFFIXES = [".gcc.txt", ".clang.txt", ".cppcheck.txt", ".flawfinder.txt"]
# .test.txt and .fuzz.txt are written for every analyzed program (they also
# carry "not compilable" / "no findings" markers). .asan.txt is written ONLY
# when the sanitizer oracle produced findings, so its absence means "no
# oracle findings", not "missing data" -- it must not be required here.
DYNAMIC_REQUIRED = [".test.txt", ".fuzz.txt"]
DYNAMIC_OPTIONAL = [".asan.txt"]


def gate_suffixes(slug: str) -> list[str]:
    suf = list(STATIC_SUFFIXES)
    if "dynamic" in slug:
        suf += DYNAMIC_REQUIRED
    return suf


def listdir_names(d: Path) -> set[str]:
    try:
        return set(os.listdir(d))
    except FileNotFoundError:
        return set()


def audit_cell(model: str, slug: str) -> dict:
    cell = COLL / model / slug
    mf = RES / model / f"{slug}.manifest.json"
    out = {
        "model": model, "slug": slug, "n": 0, "complete": 0,
        "heal_failed": 0, "missing_healed": 0, "missing_reports": 0,
        "missing_fuzz": 0, "needs_beyond_cap": 0,
        "examples": {"missing_healed": [], "missing_reports": [],
                     "missing_fuzz": [], "heal_failed": []},
    }
    if not mf.is_file():
        out["no_manifest"] = True
        return out
    manifest = json.loads(mf.read_text())
    outcomes = manifest.get("outcomes", {})
    suf = gate_suffixes(slug)
    fuzz_cell = "dynamic" in slug

    # cache directory listings for rounds 0..CAP
    round_files: dict[int, set[str]] = {}
    round_files[0] = listdir_names(cell / "heal_0")
    for r in range(1, CAP + 1):
        round_files[r] = listdir_names(cell / f"heal_{r}" / "healed")

    out["n"] = len(outcomes)
    for base, v in outcomes.items():
        outcome = v.get("outcome") if isinstance(v, dict) else v
        rounds = v.get("rounds_to_clean") if isinstance(v, dict) else None

        if outcome == "heal_failed":
            out["heal_failed"] += 1
            if len(out["examples"]["heal_failed"]) < 5:
                out["examples"]["heal_failed"].append(f"{base}@r{rounds}")
            continue

        if outcome == "clean_at_start":
            # needs round-0 analysis reports
            missing = [s for s in suf if f"{base}{s}" not in round_files[0]]
            if missing:
                out["missing_reports"] += 1
                if len(out["examples"]["missing_reports"]) < 5:
                    out["examples"]["missing_reports"].append(f"{base}@r0{','.join(missing)}")
            else:
                out["complete"] += 1
            continue

        if outcome == "clean" and isinstance(rounds, int):
            if rounds > CAP:
                out["needs_beyond_cap"] += 1  # complete data, but exceeds the cap
            need = min(rounds, CAP)
        else:  # not_cleaned (or unknown): require data through the cap
            need = CAP

        ok = True
        for r in range(1, need + 1):
            if f"{base}.c" not in round_files[r]:
                out["missing_healed"] += 1
                if len(out["examples"]["missing_healed"]) < 5:
                    out["examples"]["missing_healed"].append(f"{base}@r{r}")
                ok = False
                break
        if not ok:
            continue

        # report completeness for EVERY round of the trajectory, not just the
        # last: an intermediate round with a missing report means that round's
        # repair feedback was incomplete, which changes the trajectory.
        gaps: list[tuple[int, list[str]]] = []
        for r in range(1, need + 1):
            miss = [s for s in suf if f"{base}{s}" not in round_files[r]]
            if miss:
                gaps.append((r, miss))
        if gaps:
            r0, miss = gaps[0]
            if fuzz_cell and all(m == [".fuzz.txt"] for _, m in gaps):
                out["missing_fuzz"] += 1
                if len(out["examples"]["missing_fuzz"]) < 5:
                    out["examples"]["missing_fuzz"].append(f"{base}@r{r0}")
            else:
                out["missing_reports"] += 1
                if len(out["examples"]["missing_reports"]) < 5:
                    out["examples"]["missing_reports"].append(
                        f"{base}@r{r0}:{','.join(miss)}")
            continue

        out["complete"] += 1
    return out


def main() -> None:
    cells: list[dict] = []
    for model_dir in sorted(COLL.iterdir()):
        if not model_dir.is_dir():
            continue
        for slug_dir in sorted(model_dir.iterdir()):
            if not slug_dir.is_dir() or "legacy" in slug_dir.name:
                continue
            cells.append(audit_cell(model_dir.name, slug_dir.name))

    lines = [f"# Round-{CAP} Data-Completeness Audit", "",
             f"Scope: every non-legacy cell in `collected_code_6`; a program is",
             f"**complete** if it has full analysis artifacts through round {CAP}",
             "(or reached its terminal state earlier).", ""]
    lines.append("| Model | Cell | n | complete | heal_failed | missing_healed | "
                 "missing_reports | missing_fuzz | needs_beyond_cap |")
    lines.append("|---|---|---:|---:|---:|---:|---:|---:|---:|")
    tot = {k: 0 for k in ["n", "complete", "heal_failed", "missing_healed",
                          "missing_reports", "missing_fuzz", "needs_beyond_cap"]}
    for c in cells:
        for k in tot:
            tot[k] += c.get(k, 0)
        lines.append(
            f"| {c['model']} | {c['slug']} | {c['n']} | {c['complete']} | "
            f"{c['heal_failed']} | {c['missing_healed']} | {c['missing_reports']} | "
            f"{c['missing_fuzz']} | {c['needs_beyond_cap']} |")
    lines.append(f"| **TOTAL** | --- | **{tot['n']}** | **{tot['complete']}** | "
                 f"{tot['heal_failed']} | {tot['missing_healed']} | "
                 f"{tot['missing_reports']} | {tot['missing_fuzz']} | "
                 f"{tot['needs_beyond_cap']} |")
    lines.append("")
    lines.append("## Problem cells (any non-complete programs)")
    lines.append("")
    any_bad = False
    for c in cells:
        bad = (c["heal_failed"] + c["missing_healed"] + c["missing_reports"]
               + c["missing_fuzz"])
        if bad:
            any_bad = True
            lines.append(f"### {c['model']} / {c['slug']} — {bad} incomplete of {c['n']}")
            for k in ["heal_failed", "missing_healed", "missing_reports", "missing_fuzz"]:
                if c[k]:
                    lines.append(f"- **{k}**: {c[k]}"
                                 + (f" — e.g. {', '.join(c['examples'][k])}"
                                    if c["examples"][k] else ""))
            lines.append("")
    if not any_bad:
        lines.append("None — every program in every audited cell has complete "
                     f"data through round {CAP}.")
    out = RES / "round_audit.md"
    out.write_text("\n".join(lines) + "\n")
    print(f"cells audited: {len(cells)}")
    print("TOTALS:", json.dumps(tot))
    print(f"written -> {out}")


if __name__ == "__main__":
    main()
