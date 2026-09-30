"""Verify reasoning tokens never exceed completion tokens (paper claim).

Scans every usage ledger under results/ (all models, all cells). For every
ok row that reports reasoning_tokens (base cells record None), checks
reasoning_tokens <= completion_tokens. The paper's cost method bills
completion at the output rate on the grounds that reasoning bills as output
and is a subset of completion; this script is that verification.

Output: results/reasoning_subset_check.md
"""
from __future__ import annotations

import json
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parents[2]
R = REPO / "results"


def main() -> None:
    per_model: dict[str, dict] = {}
    for path in sorted(R.glob("*/*.usage.jsonl")):
        model = path.parent.name
        agg = per_model.setdefault(
            model, {"checked": 0, "with_reasoning": 0, "violations": 0,
                    "max_reasoning": 0})
        with open(path) as f:
            for line in f:
                try:
                    e = json.loads(line)
                except json.JSONDecodeError:
                    continue
                if e.get("ok") is not True:
                    continue
                comp = e.get("completion_tokens")
                if comp is None:
                    continue
                agg["checked"] += 1
                rat = e.get("reasoning_tokens")
                if rat is None:
                    continue
                agg["with_reasoning"] += 1
                if rat > comp:
                    agg["violations"] += 1
                agg["max_reasoning"] = max(agg["max_reasoning"], rat)

    L = ["# Reasoning tokens are a subset of completion tokens", "",
         "Scope: every ok ledger row under results/ (all models, all cells).",
         "Rows with completion_tokens present are checked; rows with",
         "reasoning_tokens present are tested against the subset claim",
         "(reasoning_tokens <= completion_tokens).", "",
         "| Ledger (model / cell dir) | ok rows checked | rows with "
         "reasoning tokens | violations |", "|---|---:|---:|---:|"]
    tot_checked = tot_reason = tot_viol = 0
    for model, a in per_model.items():
        L.append(f"| `{model}` | {a['checked']:,} | "
                 f"{a['with_reasoning']:,} | {a['violations']} |")
        tot_checked += a["checked"]
        tot_reason += a["with_reasoning"]
        tot_viol += a["violations"]
    L += ["| **TOTAL** | "
          f"**{tot_checked:,}** | **{tot_reason:,}** | **{tot_viol}** |", ""]
    if tot_viol == 0:
        L += ["No violations: on every ledger row that reports reasoning",
              "tokens, reasoning_tokens <= completion_tokens. Billing",
              "completion at the output rate is therefore exact for the",
              "reasoning-inclusive cells.", ""]
    else:
        L += [f"**{tot_viol} VIOLATIONS FOUND** -- do not claim the subset",
              "property without fixing this first.", ""]
    out = R / "reasoning_subset_check.md"
    out.write_text("\n".join(L) + "\n")
    print(f"written -> {out}; checked {tot_checked:,} rows, "
          f"{tot_reason:,} with reasoning, violations = {tot_viol}")


if __name__ == "__main__":
    main()
