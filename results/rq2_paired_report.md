# RQ2 paired contrast: static+dynamic vs static feedback

Model: **qwen-max** — vulnerable subset, top-200 ranked problems (n = 200 paired problems).
Generated: 2026-09-01 (pre-registered tests: mcnemar, wilcoxon_signed_rank, effect_size_r, bootstrap_ci; alpha = 0.05).

## Cells

| Cell | Feedback | Measure | Samples/task | n (samples) |
|---|---|---|---|---|
| RQ1 | static | static | 3 | 600 |
| RQ2 key | static+dynamic | static+dynamic | 2 | 400 |

## Descriptives (per-sample, restricted to the 200 tasks)

| Metric | RQ1 static | RQ2 static+dynamic |
|---|---|---|
| Clean at start | 58.7% | 51.7% |
| Final clean | 98.0% | 91.8% |
| Outcome counts | {'clean': 236, 'clean_at_start': 352, 'not_cleaned': 12} | {'clean': 160, 'not_cleaned': 33, 'clean_at_start': 207} |

Not-cleaned penalty for rounds-to-clean: 11 (max_rounds + 1).

## Pre-registered tests (per-problem pairing, n = 200)

- **McNemar (exact)** on problem-level clean: b = 22 (static clean, s+d not), c = 6 (static not, s+d clean), p = 0.003719
- **Wilcoxon signed-rank** on penalized rounds-to-clean (n_eff = 155 non-zero pairs): p = 2.112e-06
- **Effect size r** = +0.381 (>0 = s+d cell needs MORE rounds; includes the gate-asymmetry effect)
- **Bootstrap 95% CI** for paired clean-rate difference (s+d − static): [-0.130, -0.030]
- Sensitivity — Wilcoxon on problems clean under both gates (n = 168): p = 0.002249

## Sticky findings: what still flags the 33 not_cleaned samples (final round reports)

- Channel class: {'dynamic_only': 25, 'both': 3, 'static_only': 5}
- Non-empty finding reports by tool: {'.asan.txt': 5, '.test.txt': 23, '.cppcheck.txt': 6, '.gcc.txt': 2, '.clang.txt': 2}

## Caveats

1. **Gate asymmetry** — RQ1 'clean' means static-gate clean only; RQ2 'clean' means clean under the stricter static+dynamic gate. The contrast tests whether dynamic feedback helps the model reach the stricter bar; it does not claim the RQ1 outputs are equally defect-free.
2. Samples per task differ (3 vs 2); pairing is per-problem.
3. Single model; repeat per model as key cells complete.
