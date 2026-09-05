"""RQ2 three-channel feedback ablation: static vs dynamic vs static+dynamic.

Per model on the top-200 vulnerable subset, compares the three feedback
arms. CRITICAL SEMANTIC: each arm's manifest outcomes are relative to its
OWN feedback channels — "clean" means "no findings under the channels that
arm feeds back". Cross-arm clean-rate comparisons therefore carry gate
asymmetry (the s+d arm is held to the strictest bar).

What IS exactly comparable:
  - Round-0 detection decomposition: the static arm (RQ1 round-0) and the
    dynamic arm (imports that same round-0 via --gen-source) analyze
    IDENTICAL code, so per-sample initial flags decompose cleanly into
    static-only / dynamic-only / both / neither. For deepseek the s+d
    baseline also shares the same round-0.
  - Healing effectiveness per arm: among initially-flagged samples, how
    many reach own-channel cleanliness within 10 rounds, and how fast.
  - Per-problem paired tests between arms (all-samples aggregation).

Usage:
    python -m src.analysis.rq2_3channel [--model qwen-max]
"""
from __future__ import annotations

import argparse
from collections import Counter
from pathlib import Path

import numpy as np

from .grid_paired import (
    _all_samples_per_problem,
    _load,
    _outcome,
    _KEY_RE,
    _paired_tests,
)

REPO_ROOT = Path(__file__).resolve().parents[2]
RESULTS = REPO_ROOT / "results"
CLEAN_OUTCOMES = {"clean_at_start", "clean"}

ARMS = {
    "static": "feedback-static-r0-t1.0-p1.0",
    "dynamic": "feedback-dynamic-r0-t1.0-p1.0",
    "static+dynamic": "feedback-static+dynamic-r0-t1.0-p1.0",
}


def _sample_outcomes(manifest: dict, pids: set[int]) -> dict[tuple[int, int], tuple[str, int]]:
    """{(pid, sample): (outcome, rounds)} restricted to subset pids."""
    rows: dict[tuple[int, int], tuple[str, int]] = {}
    for key, rec in manifest["outcomes"].items():
        m = _KEY_RE.match(key)
        if not m:
            continue
        pid = int(m.group(1))
        if pid not in pids:
            continue
        smp = int(m.group(3) or 1)
        rows[(pid, smp)] = _outcome(rec)
    return rows


def _flagged_at_start(rows) -> set:
    # flagged at start = any outcome other than clean_at_start
    # ('clean' means it WAS flagged and later healed — not clean at start)
    return {k for k, (o, _) in rows.items() if o != "clean_at_start"}


def analyze(model: str = "qwen-max") -> Path | None:
    manifests = {}
    for arm, slug in ARMS.items():
        data = _load(RESULTS / model / f"{slug}.manifest.json")
        if data is None:
            print(f"[rq2_3channel] {arm} arm manifest missing for {model} — abort")
            return None
        manifests[arm] = data

    pids = set(int(t) for t in manifests["dynamic"]["cell"]["tasks"])
    penalty = 11.0  # max_rounds 10 + 1, uniform across arms

    rows = {arm: _sample_outcomes(m, pids) for arm, m in manifests.items()}
    lines = [
        "# RQ2 three-channel feedback ablation (top-200 vulnerable subset)",
        "",
        f"Model: **{model}**. Arms: static (RQ1 round-0), dynamic (same round-0 via",
        "gen-source), static+dynamic. Outcomes are relative to each arm's own",
        "feedback channels (gate asymmetry applies to cross-arm clean rates).",
        "Generated: 2026-09-03.",
        "",
    ]

    # ---- per-arm descriptives (sample level) ----
    lines += ["## Per-arm descriptives (sample level)", "",
              "| Arm | n | Flagged at start | Healed | Never cleaned | Final own-channel clean | Mean rounds (healed) |",
              "|---|---|---|---|---|---|---|"]
    for arm in ARMS:
        r = rows[arm]
        n = len(r)
        flagged = _flagged_at_start(r)
        healed = [k for k in flagged if r[k][0] == "clean"]
        nc = [k for k in flagged if r[k][0] == "not_cleaned"]
        other = [k for k in flagged if r[k][0] not in ("clean", "not_cleaned")]
        final_clean = sum(1 for k in r if r[k][0] in CLEAN_OUTCOMES)
        mean_rounds = float(np.mean([r[k][1] for k in healed])) if healed else float("nan")
        lines.append(
            f"| {arm} | {n} | {len(flagged)} ({len(flagged)/n:.1%}) | {len(healed)} "
            f"({len(healed)/max(len(flagged),1):.1%} of flagged) | {len(nc)} "
            f"({len(nc)/n:.1%}) | {final_clean} ({final_clean/n:.1%}) | {mean_rounds:.2f} |"
        )
        if other:
            lines.append(f"  (also: {len(other)} other outcomes, e.g. heal_failed: "
                         f"{Counter(r[k][0] for k in other)})")
    lines.append("")

    # ---- round-0 channel decomposition (shared code: static + dynamic arms) ----
    st, dy = _flagged_at_start(rows["static"]), _flagged_at_start(rows["dynamic"])
    shared = set(rows["static"]) & set(rows["dynamic"])
    both = len(st & dy & shared)
    st_only = len((st - dy) & shared)
    dy_only = len((dy - st) & shared)
    neither = len(shared - st - dy)
    lines += [
        "## Round-0 detection decomposition (identical code, per sample)",
        "",
        f"n = {len(shared)} samples with outcomes in both arms (same round-0 code).",
        "",
        "| Channel finding | Samples | % of shared |",
        "|---|---|---|",
        f"| static AND dynamic | {both} | {both/len(shared):.1%} |",
        f"| static only | {st_only} | {st_only/len(shared):.1%} |",
        f"| dynamic only | {dy_only} | {dy_only/len(shared):.1%} |",
        f"| neither | {neither} | {neither/len(shared):.1%} |",
        "",
        f"Static channel flags {len(st & shared)/len(shared):.1%} of initial samples; "
        f"dynamic alone flags {len(dy & shared)/len(shared):.1%}; "
        f"the union is {len((st | dy) & shared)/len(shared):.1%} "
        f"(dynamic-only adds {dy_only/len(shared):.1%} pp on top of static).",
        "",
    ]

    # deepseek: s+d arm also shares round-0 -> consistency check
    sd = _flagged_at_start(rows["static+dynamic"])
    if set(rows["static+dynamic"]) == set(rows["static"]):
        union = (st | dy) & shared
        sd_shared = sd & shared
        agree = len(union ^ sd_shared)
        lines += [
            "The s+d baseline shares the same round-0: its initial flags cover "
            f"{len(sd_shared)/len(shared):.1%} of samples vs the static∪dynamic "
            f"union {len(union)/len(shared):.1%} ({agree} samples differ — "
            "analyzer/timeout nondeterminism between cells).",
            "",
        ]
    else:
        lines += [
            "NOTE: the s+d arm used independent round-0 generations (legacy RQ2 "
            "cell) — its initial flag rate is distributionally, not exactly, "
            "comparable to the static/dynamic decomposition above.",
            "",
        ]

    # ---- per-problem paired tests between arms ----
    agg = {arm: _all_samples_per_problem(m["outcomes"], pids, penalty)
           for arm, m in manifests.items()}
    lines += ["## Per-problem paired contrasts (problem clean iff every sample clean)", ""]
    for a, b in (("static", "dynamic"), ("static", "static+dynamic"),
                 ("dynamic", "static+dynamic")):
        common = sorted(pid for pid in pids if pid in agg[a] and pid in agg[b])
        clean_a = np.array([agg[a][p]["clean"] for p in common], dtype=int)
        clean_b = np.array([agg[b][p]["clean"] for p in common], dtype=int)
        rounds_a = np.array([agg[a][p]["rounds"] for p in common])
        rounds_b = np.array([agg[b][p]["rounds"] for p in common])
        t = _paired_tests(clean_a, clean_b, rounds_a, rounds_b)
        lines += [
            f"### {a} vs {b} (n = {len(common)} problems)",
            "",
            f"- problem-level all-clean rate: {a} {clean_a.mean():.1%} vs "
            f"{b} {clean_b.mean():.1%}",
            f"- McNemar exact: b = {t['b']} ({a} clean, {b} not), c = {t['c']} "
            f"(reverse), p = {t['mcnemar_p']:.4g}",
            f"- Wilcoxon on penalized rounds-to-clean (n_eff = {t['n_eff']}): "
            f"p = {t['wilcoxon_p']:.4g}, r = {t['effect_r']:+.3f} "
            f"(>0 = {b} needs more rounds)",
            f"- Bootstrap 95% CI for clean-rate difference ({b} − {a}): "
            f"[{t['ci'][0]:+.3f}, {t['ci'][1]:+.3f}]",
            "",
        ]

    lines += [
        "## Caveats",
        "",
        "1. Own-channel outcomes: 'clean' under the static arm ignores dynamic",
        "   findings and vice versa; only the s+d arm enforces the full gate.",
        "2. Healing effectiveness (healed-fraction, rounds) is computed among",
        "   each arm's own initially-flagged samples — different denominators.",
        "3. See rq2_paired_report.md for the s+d sticky-finding breakdown.",
        "",
    ]

    out = RESULTS / f"rq2_3channel_report_{model}.md"
    out.write_text("\n".join(lines))
    print(f"[rq2_3channel] report -> {out}")
    return out


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="3-channel feedback ablation")
    parser.add_argument("--model", default="qwen-max")
    args = parser.parse_args()
    analyze(args.model)
