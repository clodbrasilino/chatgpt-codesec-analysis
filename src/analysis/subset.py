"""Vulnerable-prone subset selection from EXISTING v1/v2 data (no API spend).

Score per problem combines:
1. generation-time findings across prior experiments (collected_code_3 GCC
   reports across rounds 1-4 + collected_code_5 clang reports + the
   k-mean-clustring CWE aggregation),
2. repair difficulty: the deepest heal round the problem reached before
   being cleaned (or being dropped) in the collected_code_3 round series,
3. multiplicity: findings across multiple distinct (cwe, tool) pairs.

Outputs results/vulnerable_subset.csv (problem_id, score, components) with the
full ranked list so any top-k cut (200/250/300) is recoverable.
"""
from __future__ import annotations

import csv
import re
from collections import Counter
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[2]

_TOKEN_RE = re.compile(r"^(\d+):(\d+):.*", re.MULTILINE)
_HEAL_DIR_RE = re.compile(r"^heal_(\d+)$")


def _count_findings_in_reports(report_files: list[Path]) -> Counter[int]:
    """Count 5-token warning lines per problem id."""
    counts: Counter[int] = Counter()
    for rf in report_files:
        m = re.match(r"problem-(\d+)\.", rf.name)
        if not m:
            continue
        pid = int(m.group(1))
        try:
            text = rf.read_text(errors="ignore")
        except OSError:
            continue
        for line in text.splitlines():
            if len(line.split(":")) >= 5:
                counts[pid] += 1
    return counts


def _max_heal_depth(round_dir: Path, problem_ids: set[int]) -> Counter[int]:
    """Deepest heal_N/to_be_healed containing the problem across one round series."""
    depth: Counter[int] = Counter()
    for heal_dir in round_dir.glob("heal_*"):
        m = _HEAL_DIR_RE.match(heal_dir.name)
        if not m:
            continue
        n = int(m.group(1))
        tbe = heal_dir / "to_be_healed"
        if not tbe.is_dir():
            continue
        for f in tbe.glob("problem-*.c"):
            pid = int(re.match(r"problem-(\d+)", f.name).group(1))
            if pid in problem_ids and depth[pid] < n:
                depth[pid] = n
    return depth


def compute_scores() -> dict[int, dict]:
    gen_counts: Counter[int] = Counter()
    components: dict[int, dict] = {}

    # 1) GCC reports in collected_code_3, rounds 1-4, first generation (heal_0)
    for round_dir in (REPO_ROOT / "collected_code_3").glob("round*"):
        heal0 = round_dir / "heal_0"
        if heal0.is_dir():
            gen_counts += _count_findings_in_reports(list(heal0.glob("problem-*.gcc.txt")))

    # 2) clang reports in collected_code_5 (round1/heal_0)
    for heal0 in (REPO_ROOT / "collected_code_5").glob("round*/heal_0"):
        gen_counts += _count_findings_in_reports(list(heal0.glob("problem-*.clang.txt")))

    # 3) k-mean-clustring aggregated CWE frequencies (distinct cwe,tool per problem)
    cwe_csv = REPO_ROOT / "k-mean-clustring" / "cwes_by_problem.csv"
    cwe_multiplicity: Counter[int] = Counter()
    if cwe_csv.exists():
        with open(cwe_csv) as f:
            for row in csv.DictReader(f):
                cwe_multiplicity[int(row["problem"])] += 1

    # 4) repair difficulty: max heal depth across round series
    all_ids = set(gen_counts.keys()) | set(cwe_multiplicity.keys())
    max_depth: Counter[int] = Counter()
    for round_dir in (REPO_ROOT / "collected_code_3").glob("round*"):
        max_depth += _max_heal_depth(round_dir, all_ids)

    for pid in sorted(all_ids):
        gen = gen_counts.get(pid, 0)
        cwe = cwe_multiplicity.get(pid, 0)
        depth = max_depth.get(pid, 0)
        score = 1.0 * gen + 2.0 * cwe + 3.0 * depth
        components[pid] = {
            "gen_findings": gen,
            "cwe_tool_pairs": cwe,
            "max_heal_depth": depth,
            "score": round(score, 2),
        }
    return components


def write_subset(components: dict[int, dict], out: Path | None = None) -> Path:
    out = out or (REPO_ROOT / "results" / "vulnerable_subset.csv")
    out.parent.mkdir(parents=True, exist_ok=True)
    rows = sorted(components.items(), key=lambda kv: (-kv[1]["score"], kv[0]))
    with open(out, "w", newline="") as f:
        writer = csv.writer(f)
        writer.writerow(["rank", "problem_id", "score", "gen_findings", "cwe_tool_pairs", "max_heal_depth"])
        for rank, (pid, comp) in enumerate(rows, start=1):
            writer.writerow([rank, pid, comp["score"], comp["gen_findings"], comp["cwe_tool_pairs"], comp["max_heal_depth"]])
    return out


if __name__ == "__main__":
    comps = compute_scores()
    out = write_subset(comps)
    print(f"scored {len(comps)} problems -> {out}")
    import pandas as pd

    df = pd.read_csv(out)
    print(df.head(10).to_string(index=False))
    print(f"\ntop-200 score range: {df['score'].iloc[199]:.2f} .. {df['score'].iloc[0]:.2f}")
