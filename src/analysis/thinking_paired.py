"""Thinking vs non-thinking paired contrast on the vulnerable subset.

Compares, on the same top-200 vulnerable subset, same decoding params
(t=1.0, p=1.0), same static feedback, same max_rounds:
  - baseline: deepseek-v4-pro (reasoning disabled) RQ1 cell, sample-1 pairing,
  - thinking: deepseek-v4-pro-thinking (reasoning enabled, r1 slug) cell,
    1 sample/task.

Pre-registered tests (config/experiment.yaml -> analysis.tests.rq2_rq3):
  mcnemar, wilcoxon_signed_rank, effect_size_r, bootstrap_ci  (alpha = 0.05)

Sensitivity: baseline aggregated over all 3 samples (problem clean iff all
samples clean) — a stricter baseline bar, reported alongside.

Extra vs grid_paired: per-call usage contrast pulled from the usage ledgers
(thinking burns reasoning tokens; cost/latency overhead is a paper talking
point, and the user's token accounting is of utmost importance).

Usage:
    python -m src.analysis.thinking_paired
"""

from __future__ import annotations

import json
from collections import Counter
from pathlib import Path

import numpy as np

from src.analysis.grid_paired import (
    _all_samples_per_problem,
    _load,
    _paired_tests,
    _sample1_per_problem,
)

REPO_ROOT = Path(__file__).resolve().parents[2]
RESULTS = REPO_ROOT / "results"

BASE_MODEL = "deepseek-v4-pro"
THINK_MODEL = "deepseek-v4-pro-thinking"
BASE_SLUG = "feedback-static-r0-t1.0-p1.0"
THINK_SLUG = "feedback-static-r1-t1.0-p1.0"


def _usage_summary(model: str, slug: str) -> dict | None:
    f = RESULTS / model / f"{slug}.usage.jsonl"
    if not f.is_file():
        return None
    calls = [json.loads(l) for l in open(f)]
    ok = [c for c in calls if c.get("ok")]
    g = lambda k: sum((c.get(k) or 0) for c in ok)  # noqa: E731
    lat = [c.get("latency_s") or 0 for c in ok]
    return {
        "calls": len(calls),
        "ok": len(ok),
        "fail": len(calls) - len(ok),
        "in_tok": g("prompt_tokens"),
        "out_tok": g("completion_tokens"),
        "reason_tok": g("reasoning_tokens"),
        "mean_lat": sum(lat) / max(len(lat), 1),
    }


def analyze() -> Path | None:
    baseline = _load(RESULTS / BASE_MODEL / f"{BASE_SLUG}.manifest.json")
    thinking = _load(RESULTS / THINK_MODEL / f"{THINK_SLUG}.manifest.json")
    if baseline is None:
        print("[thinking_paired] baseline manifest missing; abort")
        return None
    if thinking is None:
        print("[thinking_paired] thinking manifest not ready (cell still running?) — abort")
        return None

    pids = set(int(t) for t in thinking["cell"]["tasks"])
    penalty = float(thinking["cell"]["max_rounds"]) + 1

    base_s1 = _sample1_per_problem(baseline["outcomes"], pids, penalty)
    base_all = _all_samples_per_problem(baseline["outcomes"], pids, penalty)
    think = _sample1_per_problem(thinking["outcomes"], pids, penalty)

    common = sorted(pid for pid in pids if pid in base_s1 and pid in think)
    n = len(common)
    lines = [
        "# Thinking vs non-thinking paired contrast (vulnerable subset, top-200)",
        "",
        f"Baseline: **{BASE_MODEL}** (reasoning disabled, `{BASE_SLUG}`, sample-1 pairing; "
        f"all-samples sensitivity below). Thinking: **{THINK_MODEL}** "
        f"(`{THINK_SLUG}`, 1 sample/task). Same t=1.0/p=1.0, static feedback, "
        f"max_rounds = {penalty - 1:.0f}.",
        "Generated: 2026-09-01/02 (pre-registered tests: mcnemar, wilcoxon_signed_rank, "
        "effect_size_r, bootstrap_ci; alpha = 0.05).",
        "",
    ]

    if n == 0:
        lines += ["No overlapping problems yet — run the full subset cell first.", ""]
    else:
        clean_a = np.array([base_s1[p]["clean"] for p in common], dtype=int)
        clean_b = np.array([think[p]["clean"] for p in common], dtype=int)
        rounds_a = np.array([base_s1[p]["rounds"] for p in common])
        rounds_b = np.array([think[p]["rounds"] for p in common])
        t = _paired_tests(clean_a, clean_b, rounds_a, rounds_b)

        clean_a2 = np.array([base_all[p]["clean"] for p in common], dtype=int)
        rounds_a2 = np.array([base_all[p]["rounds"] for p in common])
        t2 = _paired_tests(clean_a2, clean_b, rounds_a2, rounds_b)

        counts = Counter(think[p]["outcome"] for p in common)
        base_counts = Counter(base_s1[p]["outcome"] for p in common)
        base_final = (base_counts.get("clean_at_start", 0) + base_counts.get("clean", 0)) / n
        think_final = (counts.get("clean_at_start", 0) + counts.get("clean", 0)) / n
        ci_lo, ci_hi = t["ci"]
        ci2_lo, ci2_hi = t2["ci"]

        lines += [
            f"n = {n} paired problems (sample-1 pairing).",
            "",
            "| Metric | non-thinking | thinking |",
            "|---|---|---|",
            f"| Final clean | {base_final:.1%} | {think_final:.1%} |",
            f"| Clean at start | {base_counts.get('clean_at_start', 0) / n:.1%} | "
            f"{counts.get('clean_at_start', 0) / n:.1%} |",
            f"| Outcome counts | {dict(base_counts)} | {dict(counts)} |",
            "",
            f"- **McNemar (exact)**: b = {t['b']} (baseline clean, thinking not), "
            f"c = {t['c']} (reverse), p = {t['mcnemar_p']:.4g}",
            f"- **Wilcoxon signed-rank** on penalized rounds-to-clean "
            f"(n_eff = {t['n_eff']}): p = {t['wilcoxon_p']:.4g}, "
            f"effect r = {t['effect_r']:+.3f} (>0 = thinking needs more rounds)",
            f"- **Bootstrap 95% CI** clean-rate difference (thinking − baseline): "
            f"[{ci_lo:+.3f}, {ci_hi:+.3f}]",
            f"- Sensitivity (baseline = all-3-samples-clean bar): McNemar "
            f"b = {t2['b']}, c = {t2['c']}, p = {t2['mcnemar_p']:.4g}; "
            f"bootstrap CI [{ci2_lo:+.3f}, {ci2_hi:+.3f}]",
            "",
        ]

    # usage contrast
    u_base = _usage_summary(BASE_MODEL, BASE_SLUG)
    u_think = _usage_summary(THINK_MODEL, THINK_SLUG)
    lines += ["## Usage contrast (exact ledger)", ""]
    if u_base and u_think:
        lines += [
            "| Metric | non-thinking | thinking |",
            "|---|---|---|",
            f"| Calls (ok/fail) | {u_base['ok']}/{u_base['fail']} | {u_think['ok']}/{u_think['fail']} |",
            f"| Prompt tokens | {u_base['in_tok']:,} | {u_think['in_tok']:,} |",
            f"| Completion tokens | {u_base['out_tok']:,} | {u_think['out_tok']:,} |",
            f"| Reasoning tokens | {u_base['reason_tok']:,} | {u_think['reason_tok']:,} |",
            f"| Mean latency/call | {u_base['mean_lat']:.1f}s | {u_think['mean_lat']:.1f}s |",
            "",
        ]
        if u_base["ok"] and u_think["ok"]:
            lines += [
                f"Per-problem cost multiplier (completion tokens): "
                f"{(u_think['out_tok'] / max(u_think['ok'],1)) / (u_base['out_tok'] / max(u_base['ok'],1)):.1f}x; "
                f"latency multiplier: {u_think['mean_lat'] / u_base['mean_lat']:.1f}x.",
                "",
            ]
    else:
        lines += ["Ledger missing for one or both cells (pre-ledger rounds are "
                  "estimated elsewhere; see usage_report).", ""]

    lines += [
        "## Caveats",
        "",
        "1. Baseline sample 1 and thinking sample 1 are independent generations "
        "(no shared randomness); pairing is by problem.",
        "2. One sample per thinking cell -> noisy per-problem outcomes; interpret "
        "non-significance as inconclusive.",
        "3. Same static gate on both cells; no gate asymmetry.",
        "4. Thinking cell max_tokens = 16384 caps reasoning chain length; very long "
        "chains may truncate (empty-content retries are logged as failed calls).",
        "",
    ]

    out = RESULTS / "thinking_paired_report.md"
    out.write_text("\n".join(lines))
    print(f"[thinking_paired] report -> {out}")
    return out


if __name__ == "__main__":
    analyze()
