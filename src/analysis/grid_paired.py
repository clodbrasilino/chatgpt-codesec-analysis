"""Temp/top_p grid paired contrast on the vulnerable subset.

Compares, for the same model on the same top-200 vulnerable subset:
  - baseline: the RQ1 cell (t=1.0, p=1.0), using its SAMPLE-1 outcome per problem
    (exact sample-level pairing — the grid cells draw 1 sample/task by design,
    so the baseline's first sample matches that sampling budget), and
  - grid cells: t=0.2-p1.0 and t1.0-p0.5 (ablation_samples = 1).

Pre-registered tests (config/experiment.yaml -> analysis.tests.rq2_rq3):
  mcnemar, wilcoxon_signed_rank, effect_size_r, bootstrap_ci  (alpha = 0.05)

Sensitivity: baseline aggregated over all 3 samples (problem clean iff all
samples clean) — a stricter baseline bar, reported alongside.

Caveats recorded in the report:
  - Baseline sample 1 vs grid sample 1 are independent draws (no shared seed);
    pairing is by PROBLEM, not by shared randomness.
  - Single sample per grid cell: per-problem outcomes are noisy; treat
    non-significant results as inconclusive, not as evidence of equivalence.
  - Same static gate for all cells (no gate asymmetry, unlike RQ2 contrast).

Usage:
    python -m src.analysis.grid_paired [--model qwen-max]
"""

from __future__ import annotations

import argparse
import re
from collections import Counter
from pathlib import Path

import numpy as np
from scipy import stats as sps

REPO_ROOT = Path(__file__).resolve().parents[2]
RESULTS = REPO_ROOT / "results"
CLEAN_OUTCOMES = {"clean_at_start", "clean"}

BASE_SLUGS = {
    "static": "feedback-static-r0-t1.0-p1.0",
    "static+dynamic": "feedback-static+dynamic-r0-t1.0-p1.0",
}
GRID_SLUGS = {
    "static": {
        "t0.2-p1.0": "feedback-static-r0-t0.2-p1.0",
        "t1.0-p0.5": "feedback-static-r0-t1.0-p0.5",
    },
    "static+dynamic": {
        "t0.2-p1.0": "feedback-static+dynamic-r0-t0.2-p1.0",
        "t1.0-p0.5": "feedback-static+dynamic-r0-t1.0-p0.5",
    },
}

_KEY_RE = re.compile(r"^problem-(\d+)(-s(\d+))?$")


def _load(path: Path) -> dict | None:
    if not path.is_file():
        return None
    import json

    with open(path) as f:
        return json.load(f)


def _outcome(rec) -> tuple[str, int]:
    if isinstance(rec, dict):
        return rec.get("outcome", "unknown"), int(rec.get("rounds_to_clean", 0))
    return rec, 0


def _sample1_per_problem(outcomes: dict, pids: set[int], penalty: float) -> dict[int, dict]:
    """Sample-1 outcome per problem: {'clean': bool, 'rounds': float}."""
    rows: dict[int, dict] = {}
    for key, rec in outcomes.items():
        m = _KEY_RE.match(key)
        if not m or m.group(2):  # skip -s2/-s3
            continue
        pid = int(m.group(1))
        if pid not in pids:
            continue
        outcome, rounds = _outcome(rec)
        rows[pid] = {
            "clean": outcome in CLEAN_OUTCOMES,
            "rounds": float(rounds if outcome in CLEAN_OUTCOMES else penalty),
            "outcome": outcome,
        }
    return rows


def _all_samples_per_problem(outcomes: dict, pids: set[int], penalty: float) -> dict[int, dict]:
    """All-samples aggregation: problem clean iff every sample clean."""
    acc: dict[int, list] = {pid: [] for pid in pids}
    for key, rec in outcomes.items():
        m = _KEY_RE.match(key)
        if not m:
            continue
        pid = int(m.group(1))
        if pid in acc:
            acc[pid].append(_outcome(rec))
    return {
        pid: {
            "clean": bool(v) and all(o in CLEAN_OUTCOMES for o, _ in v),
            "rounds": float(np.mean([r if o in CLEAN_OUTCOMES else penalty for o, r in v])) if v else penalty,
        }
        for pid, v in acc.items()
    }


def _paired_tests(clean_a: np.ndarray, clean_b: np.ndarray, rounds_a: np.ndarray, rounds_b: np.ndarray) -> dict:
    """b/c McNemar + Wilcoxon + effect r + bootstrap CI. B is the grid cell."""
    b = int(np.sum((clean_a == 1) & (clean_b == 0)))  # baseline clean, grid not
    c = int(np.sum((clean_a == 0) & (clean_b == 1)))  # baseline not, grid clean
    mcnemar_p = float(sps.binomtest(b, b + c, 0.5).pvalue) if b + c > 0 else 1.0

    diff = rounds_b - rounds_a  # >0 = grid cell needed more rounds
    nonzero = diff != 0
    wilcoxon_p, effect_r, n_eff = float("nan"), float("nan"), 0
    if nonzero.sum() > 0:
        n_eff = int(nonzero.sum())
        try:
            res = sps.wilcoxon(rounds_b[nonzero], rounds_a[nonzero], zero_method="wilcox")
            wilcoxon_p = float(res.pvalue)
            z = sps.norm.isf(wilcoxon_p / 2) if 0 < wilcoxon_p < 1 else 0.0
            effect_r = float(np.sign(np.mean(diff[nonzero])) * abs(z) / np.sqrt(n_eff))
        except ValueError:
            wilcoxon_p = 1.0

    rng = np.random.default_rng(20260901)
    paired_diff = clean_b - clean_a
    boots = np.array([
        paired_diff[rng.integers(0, len(paired_diff), len(paired_diff))].mean()
        for _ in range(10_000)
    ])
    ci_lo, ci_hi = np.percentile(boots, [2.5, 97.5])
    return {
        "b": b, "c": c, "mcnemar_p": mcnemar_p,
        "wilcoxon_p": wilcoxon_p, "effect_r": effect_r, "n_eff": n_eff,
        "ci": (float(ci_lo), float(ci_hi)),
    }


def analyze(model: str = "qwen-max", feedback: str = "static") -> Path | None:
    if feedback not in BASE_SLUGS:
        print(f"[grid_paired] unknown feedback mode {feedback!r}; abort")
        return None
    baseline_slug = BASE_SLUGS[feedback]
    grid_slugs = GRID_SLUGS[feedback]
    # static grid cells are 1-sample -> sample-1 pairing is primary.
    # s+d grid cells are 3-sample -> all-samples pairing is primary.
    primary_all = feedback != "static"

    baseline = _load(RESULTS / model / f"{baseline_slug}.manifest.json")
    if baseline is None:
        print(f"[grid_paired] baseline manifest missing for {model} ({baseline_slug}); abort")
        return None

    loaded: dict[str, dict] = {}
    for label, slug in grid_slugs.items():
        data = _load(RESULTS / model / f"{slug}.manifest.json")
        if data is None:
            print(f"[grid_paired] {label} manifest not ready for {model} (cell still running?) — skipping")
            continue
        loaded[label] = data

    if not loaded:
        print(f"[grid_paired] no grid manifests yet for {model} ({feedback}); nothing to do")
        return None

    pids_union: set[int] = set()
    for data in loaded.values():
        pids_union.update(int(t) for t in data["cell"]["tasks"])
    penalty = float(max(int(data["cell"]["max_rounds"]) for data in loaded.values()) + 1)

    base_s1 = _sample1_per_problem(baseline["outcomes"], pids_union, penalty)
    base_all = _all_samples_per_problem(baseline["outcomes"], pids_union, penalty)

    fb_label = "static+dynamic" if feedback != "static" else "static"
    suffix = "" if feedback == "static" else "_sd"
    lines = [
        "# Temp/top_p grid paired contrast (vulnerable subset, top-200)",
        "",
        f"Model: **{model}**. Feedback/gate = **{fb_label}**. Baseline = "
        f"{baseline_slug} (2 samples/task for qwen-max legacy RQ2 cell, 3 otherwise); "
        f"grid cells = {'3 samples/task' if primary_all else '1 sample/task'}, "
        f"max_rounds = {penalty - 1:.0f}.",
        f"Primary pairing: {'all-samples aggregation (problem clean iff every sample clean; rounds averaged)' if primary_all else 'sample-1 pairing'}.",
        "Generated: 2026-09-02 (pre-registered tests: mcnemar, wilcoxon_signed_rank, "
        "effect_size_r, bootstrap_ci; alpha = 0.05).",
        "",
    ]

    def _emit(label, data, base_primary, base_sens, primary_name, sens_name):
        grid_primary = _all_samples_per_problem(data["outcomes"], pids_union, penalty) if primary_all \
            else _sample1_per_problem(data["outcomes"], pids_union, penalty)
        out = []
        for pname, base_p, grid_p in ((primary_name, base_primary, grid_primary),):
            common = sorted(pid for pid in pids_union if pid in base_p and pid in grid_p)
            if not common:
                out += [f"## {label} — no overlapping problems", ""]
                continue
            clean_a = np.array([base_p[p]["clean"] for p in common], dtype=int)
            clean_b = np.array([grid_p[p]["clean"] for p in common], dtype=int)
            rounds_a = np.array([base_p[p]["rounds"] for p in common])
            rounds_b = np.array([grid_p[p]["rounds"] for p in common])
            t = _paired_tests(clean_a, clean_b, rounds_a, rounds_b)

            n = len(common)
            # outcome counts from raw manifest outcomes restricted to common pids
            # (baseline restricted to sample-1 keys when the pairing is sample-1)
            raw = Counter()
            for key, rec in data["outcomes"].items():
                m = _KEY_RE.match(key)
                if not m:
                    continue
                pid = int(m.group(1))
                if pid in set(common):
                    raw[_outcome(rec)[0]] += 1
            base_raw = Counter()
            for key, rec in baseline["outcomes"].items():
                m = _KEY_RE.match(key)
                if not m:
                    continue
                if not primary_all and m.group(2):  # sample-1 pairing -> s1 only
                    continue
                pid = int(m.group(1))
                if pid in set(common):
                    base_raw[_outcome(rec)[0]] += 1
            final_clean = (raw.get("clean_at_start", 0) + raw.get("clean", 0)) / max(sum(raw.values()), 1)
            base_final = (base_raw.get("clean_at_start", 0) + base_raw.get("clean", 0)) / max(sum(base_raw.values()), 1)
            init_rate = raw.get("clean_at_start", 0) / max(sum(raw.values()), 1)
            base_init = base_raw.get("clean_at_start", 0) / max(sum(base_raw.values()), 1)

            ci_lo, ci_hi = t["ci"]
            out += [
                f"## {label} vs baseline ({'t1.0-p1.0'})",
                "",
                f"n = {n} paired problems ({pname}).",
                "",
                "| Metric | baseline | " + label + " |",
                "|---|---|---|",
                f"| Final clean (sample-level) | {base_final:.1%} | {final_clean:.1%} |",
                f"| Clean at start (sample-level) | {base_init:.1%} | {init_rate:.1%} |",
                f"| Outcome counts (samples) | {dict(base_raw)} | {dict(raw)} |",
                "",
                f"- **McNemar (exact)**: b = {t['b']} (baseline clean, grid not), "
                f"c = {t['c']} (reverse), p = {t['mcnemar_p']:.4g}",
                f"- **Wilcoxon signed-rank** on penalized rounds-to-clean "
                f"(n_eff = {t['n_eff']}): p = {t['wilcoxon_p']:.4g}, "
                f"effect r = {t['effect_r']:+.3f} (>0 = grid needs more rounds)",
                f"- **Bootstrap 95% CI** clean-rate difference (grid − baseline): "
                f"[{ci_lo:+.3f}, {ci_hi:+.3f}]",
                "",
            ]
        # sensitivity block
        grid_s1 = _sample1_per_problem(data["outcomes"], pids_union, penalty)
        if primary_all:
            common = sorted(pid for pid in pids_union if pid in base_s1 and pid in grid_s1)
            if common:
                clean_a = np.array([base_s1[p]["clean"] for p in common], dtype=int)
                clean_b = np.array([grid_s1[p]["clean"] for p in common], dtype=int)
                rounds_a = np.array([base_s1[p]["rounds"] for p in common])
                rounds_b = np.array([grid_s1[p]["rounds"] for p in common])
                t2 = _paired_tests(clean_a, clean_b, rounds_a, rounds_b)
                out += [
                    f"- Sensitivity (sample-1 pairing): McNemar b = {t2['b']}, "
                    f"c = {t2['c']}, p = {t2['mcnemar_p']:.4g}; Wilcoxon "
                    f"p = {t2['wilcoxon_p']:.4g}, r = {t2['effect_r']:+.3f}; "
                    f"bootstrap CI [{t2['ci'][0]:+.3f}, {t2['ci'][1]:+.3f}]",
                    "",
                ]
        else:
            common = sorted(pid for pid in pids_union if pid in base_sens and pid in grid_s1)
            if common:
                clean_a = np.array([base_sens[p]["clean"] for p in common], dtype=int)
                clean_b = np.array([grid_s1[p]["clean"] for p in common], dtype=int)
                rounds_a = np.array([base_sens[p]["rounds"] for p in common])
                rounds_b = np.array([grid_s1[p]["rounds"] for p in common])
                t2 = _paired_tests(clean_a, clean_b, rounds_a, rounds_b)
                out += [
                    f"- Sensitivity (baseline = all-3-samples-clean bar): McNemar "
                    f"b = {t2['b']}, c = {t2['c']}, p = {t2['mcnemar_p']:.4g}; "
                    f"bootstrap CI [{t2['ci'][0]:+.3f}, {t2['ci'][1]:+.3f}]",
                    "",
                ]
        return out

    for label, data in loaded.items():
        base_primary = base_all if primary_all else base_s1
        base_sens = base_s1 if primary_all else base_all
        lines += _emit(
            label, data, base_primary, base_sens,
            "all-samples pairing" if primary_all else "sample-1 pairing",
            "sample-1",
        )

    lines += [
        "## Caveats",
        "",
        "1. Baseline and grid samples are independent generations "
        "(no shared randomness); pairing is by problem.",
        "2. Non-significance is inconclusive, not evidence of equivalence.",
        "3. Same gate on all cells within this contrast; cross-gate comparisons "
        "(static vs static+dynamic) suffer gate asymmetry — see rq2_paired.",
        "",
    ]

    out = RESULTS / f"grid_paired_report_{model}{suffix}.md"
    out.write_text("\n".join(lines))
    print(f"[grid_paired] report -> {out}")
    return out


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Temp/top_p grid paired contrast")
    parser.add_argument("--model", default="qwen-max")
    parser.add_argument("--feedback", default="static",
                        choices=["static", "static+dynamic"],
                        help="which grid generation to analyze")
    args = parser.parse_args()
    analyze(args.model, args.feedback)
