# Temp/top_p grid paired contrast (vulnerable subset, top-200)

Model: **deepseek-v4-pro**. Feedback/gate = **static+dynamic**. Baseline = feedback-static+dynamic-r0-t1.0-p1.0 (2 samples/task for qwen-max legacy RQ2 cell, 3 otherwise); grid cells = 3 samples/task, max_rounds = 10.
Primary pairing: all-samples aggregation (problem clean iff every sample clean; rounds averaged).
Generated: 2026-09-02 (pre-registered tests: mcnemar, wilcoxon_signed_rank, effect_size_r, bootstrap_ci; alpha = 0.05).

## t0.2-p1.0 vs baseline (t1.0-p1.0)

n = 200 paired problems (all-samples pairing).

| Metric | baseline | t0.2-p1.0 |
|---|---|---|
| Final clean (sample-level) | 94.5% | 93.8% |
| Clean at start (sample-level) | 56.2% | 61.2% |
| Outcome counts (samples) | {'clean': 230, 'not_cleaned': 33, 'clean_at_start': 337} | {'clean': 196, 'not_cleaned': 37, 'clean_at_start': 367} |

- **McNemar (exact)**: b = 7 (baseline clean, grid not), c = 12 (reverse), p = 0.3593
- **Wilcoxon signed-rank** on penalized rounds-to-clean (n_eff = 123): p = 0.4379, effect r = +0.070 (>0 = grid needs more rounds)
- **Bootstrap 95% CI** clean-rate difference (grid − baseline): [-0.020, +0.070]

- Sensitivity (sample-1 pairing): McNemar b = 7, c = 7, p = 1; Wilcoxon p = 0.536, r = +0.069; bootstrap CI [-0.035, +0.035]

## t1.0-p0.5 vs baseline (t1.0-p1.0)

n = 200 paired problems (all-samples pairing).

| Metric | baseline | t1.0-p0.5 |
|---|---|---|
| Final clean (sample-level) | 94.5% | 94.7% |
| Clean at start (sample-level) | 56.2% | 60.3% |
| Outcome counts (samples) | {'clean': 230, 'not_cleaned': 33, 'clean_at_start': 337} | {'clean': 206, 'clean_at_start': 362, 'not_cleaned': 32} |

- **McNemar (exact)**: b = 4 (baseline clean, grid not), c = 10 (reverse), p = 0.1796
- **Wilcoxon signed-rank** on penalized rounds-to-clean (n_eff = 129): p = 0.9925, effect r = +0.001 (>0 = grid needs more rounds)
- **Bootstrap 95% CI** clean-rate difference (grid − baseline): [-0.005, +0.065]

- Sensitivity (sample-1 pairing): McNemar b = 4, c = 7, p = 0.5488; Wilcoxon p = 0.4729, r = -0.080; bootstrap CI [-0.015, +0.050]

## Caveats

1. Baseline and grid samples are independent generations (no shared randomness); pairing is by problem.
2. Non-significance is inconclusive, not evidence of equivalence.
3. Same gate on all cells within this contrast; cross-gate comparisons (static vs static+dynamic) suffer gate asymmetry — see rq2_paired.
