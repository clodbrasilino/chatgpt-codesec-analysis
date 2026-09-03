# Temp/top_p grid paired contrast (vulnerable subset, top-200)

Model: **qwen-max**. Feedback/gate = **static+dynamic**. Baseline = feedback-static+dynamic-r0-t1.0-p1.0 (2 samples/task for qwen-max legacy RQ2 cell, 3 otherwise); grid cells = 3 samples/task, max_rounds = 10.
Primary pairing: all-samples aggregation (problem clean iff every sample clean; rounds averaged).
Generated: 2026-09-02 (pre-registered tests: mcnemar, wilcoxon_signed_rank, effect_size_r, bootstrap_ci; alpha = 0.05).

## t0.2-p1.0 vs baseline (t1.0-p1.0)

n = 200 paired problems (all-samples pairing).

| Metric | baseline | t0.2-p1.0 |
|---|---|---|
| Final clean (sample-level) | 91.8% | 93.7% |
| Clean at start (sample-level) | 51.7% | 54.3% |
| Outcome counts (samples) | {'clean': 160, 'not_cleaned': 33, 'clean_at_start': 207} | {'clean': 236, 'clean_at_start': 326, 'not_cleaned': 38} |

- **McNemar (exact)**: b = 7 (baseline clean, grid not), c = 14 (reverse), p = 0.1892
- **Wilcoxon signed-rank** on penalized rounds-to-clean (n_eff = 139): p = 0.07836, effect r = -0.149 (>0 = grid needs more rounds)
- **Bootstrap 95% CI** clean-rate difference (grid − baseline): [-0.010, +0.080]

- Sensitivity (sample-1 pairing): McNemar b = 4, c = 10, p = 0.1796; Wilcoxon p = 0.4616, r = -0.079; bootstrap CI [-0.005, +0.065]

## t1.0-p0.5 vs baseline (t1.0-p1.0)

n = 200 paired problems (all-samples pairing).

| Metric | baseline | t1.0-p0.5 |
|---|---|---|
| Final clean (sample-level) | 91.8% | 93.7% |
| Clean at start (sample-level) | 51.7% | 59.2% |
| Outcome counts (samples) | {'clean': 160, 'not_cleaned': 33, 'clean_at_start': 207} | {'clean': 207, 'clean_at_start': 355, 'not_cleaned': 38} |

- **McNemar (exact)**: b = 6 (baseline clean, grid not), c = 13 (reverse), p = 0.1671
- **Wilcoxon signed-rank** on penalized rounds-to-clean (n_eff = 135): p = 0.02527, effect r = -0.193 (>0 = grid needs more rounds)
- **Bootstrap 95% CI** clean-rate difference (grid − baseline): [-0.005, +0.080]

- Sensitivity (sample-1 pairing): McNemar b = 4, c = 10, p = 0.1796; Wilcoxon p = 0.01316, r = -0.275; bootstrap CI [-0.005, +0.070]

## Caveats

1. Baseline and grid samples are independent generations (no shared randomness); pairing is by problem.
2. Non-significance is inconclusive, not evidence of equivalence.
3. Same gate on all cells within this contrast; cross-gate comparisons (static vs static+dynamic) suffer gate asymmetry — see rq2_paired.
