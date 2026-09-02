# Temp/top_p grid paired contrast (vulnerable subset, top-200)

Model: **deepseek-v4-pro**. Feedback/gate = **static**. Baseline = feedback-static-r0-t1.0-p1.0 (2 samples/task for qwen-max legacy RQ2 cell, 3 otherwise); grid cells = 1 sample/task, max_rounds = 10.
Primary pairing: sample-1 pairing.
Generated: 2026-09-02 (pre-registered tests: mcnemar, wilcoxon_signed_rank, effect_size_r, bootstrap_ci; alpha = 0.05).

## t0.2-p1.0 vs baseline (t1.0-p1.0)

n = 200 paired problems (sample-1 pairing).

| Metric | baseline | t0.2-p1.0 |
|---|---|---|
| Final clean (sample-level) | 98.0% | 98.0% |
| Clean at start (sample-level) | 57.5% | 69.5% |
| Outcome counts (samples) | {'clean': 81, 'not_cleaned': 4, 'clean_at_start': 115} | {'clean': 57, 'clean_at_start': 139, 'not_cleaned': 4} |

- **McNemar (exact)**: b = 4 (baseline clean, grid not), c = 4 (reverse), p = 1
- **Wilcoxon signed-rank** on penalized rounds-to-clean (n_eff = 71): p = 0.0295, effect r = -0.258 (>0 = grid needs more rounds)
- **Bootstrap 95% CI** clean-rate difference (grid − baseline): [-0.025, +0.030]

- Sensitivity (baseline = all-3-samples-clean bar): McNemar b = 3, c = 9, p = 0.146; bootstrap CI [-0.005, +0.065]

## t1.0-p0.5 vs baseline (t1.0-p1.0)

n = 200 paired problems (sample-1 pairing).

| Metric | baseline | t1.0-p0.5 |
|---|---|---|
| Final clean (sample-level) | 98.0% | 98.0% |
| Clean at start (sample-level) | 57.5% | 63.5% |
| Outcome counts (samples) | {'clean': 81, 'not_cleaned': 4, 'clean_at_start': 115} | {'clean': 69, 'clean_at_start': 127, 'not_cleaned': 4} |

- **McNemar (exact)**: b = 4 (baseline clean, grid not), c = 4 (reverse), p = 1
- **Wilcoxon signed-rank** on penalized rounds-to-clean (n_eff = 71): p = 0.2926, effect r = -0.125 (>0 = grid needs more rounds)
- **Bootstrap 95% CI** clean-rate difference (grid − baseline): [-0.030, +0.025]

- Sensitivity (baseline = all-3-samples-clean bar): McNemar b = 2, c = 8, p = 0.1094; bootstrap CI [+0.000, +0.060]

## Caveats

1. Baseline and grid samples are independent generations (no shared randomness); pairing is by problem.
2. Non-significance is inconclusive, not evidence of equivalence.
3. Same gate on all cells within this contrast; cross-gate comparisons (static vs static+dynamic) suffer gate asymmetry — see rq2_paired.
