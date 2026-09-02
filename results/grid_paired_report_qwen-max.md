# Temp/top_p grid paired contrast (vulnerable subset, top-200)

Model: **qwen-max**. Feedback/gate = **static**. Baseline = feedback-static-r0-t1.0-p1.0 (2 samples/task for qwen-max legacy RQ2 cell, 3 otherwise); grid cells = 1 sample/task, max_rounds = 10.
Primary pairing: sample-1 pairing.
Generated: 2026-09-02 (pre-registered tests: mcnemar, wilcoxon_signed_rank, effect_size_r, bootstrap_ci; alpha = 0.05).

## t0.2-p1.0 vs baseline (t1.0-p1.0)

n = 200 paired problems (sample-1 pairing).

| Metric | baseline | t0.2-p1.0 |
|---|---|---|
| Final clean (sample-level) | 98.0% | 99.0% |
| Clean at start (sample-level) | 62.5% | 63.0% |
| Outcome counts (samples) | {'clean': 71, 'clean_at_start': 125, 'not_cleaned': 4} | {'clean': 72, 'clean_at_start': 126, 'not_cleaned': 2} |

- **McNemar (exact)**: b = 1 (baseline clean, grid not), c = 3 (reverse), p = 0.625
- **Wilcoxon signed-rank** on penalized rounds-to-clean (n_eff = 74): p = 0.3145, effect r = -0.117 (>0 = grid needs more rounds)
- **Bootstrap 95% CI** clean-rate difference (grid − baseline): [-0.010, +0.030]

- Sensitivity (baseline = all-3-samples-clean bar): McNemar b = 1, c = 9, p = 0.02148; bootstrap CI [+0.010, +0.070]

## t1.0-p0.5 vs baseline (t1.0-p1.0)

n = 200 paired problems (sample-1 pairing).

| Metric | baseline | t1.0-p0.5 |
|---|---|---|
| Final clean (sample-level) | 98.0% | 98.5% |
| Clean at start (sample-level) | 62.5% | 71.0% |
| Outcome counts (samples) | {'clean': 71, 'clean_at_start': 125, 'not_cleaned': 4} | {'clean': 55, 'clean_at_start': 142, 'not_cleaned': 3} |

- **McNemar (exact)**: b = 2 (baseline clean, grid not), c = 3 (reverse), p = 1
- **Wilcoxon signed-rank** on penalized rounds-to-clean (n_eff = 70): p = 0.1203, effect r = -0.186 (>0 = grid needs more rounds)
- **Bootstrap 95% CI** clean-rate difference (grid − baseline): [-0.015, +0.025]

- Sensitivity (baseline = all-3-samples-clean bar): McNemar b = 2, c = 9, p = 0.06543; bootstrap CI [+0.005, +0.070]

## Caveats

1. Baseline and grid samples are independent generations (no shared randomness); pairing is by problem.
2. Non-significance is inconclusive, not evidence of equivalence.
3. Same gate on all cells within this contrast; cross-gate comparisons (static vs static+dynamic) suffer gate asymmetry — see rq2_paired.
