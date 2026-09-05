# RQ2 three-channel feedback ablation (top-200 vulnerable subset)

Model: **qwen-max**. Arms: static (RQ1 round-0), dynamic (same round-0 via
gen-source), static+dynamic. Outcomes are relative to each arm's own
feedback channels (gate asymmetry applies to cross-arm clean rates).
Generated: 2026-09-03.

## Per-arm descriptives (sample level)

| Arm | n | Flagged at start | Healed | Never cleaned | Final own-channel clean | Mean rounds (healed) |
|---|---|---|---|---|---|---|
| static | 600 | 248 (41.3%) | 236 (95.2% of flagged) | 12 (2.0%) | 588 (98.0%) | 1.39 |
| dynamic | 600 | 68 (11.3%) | 50 (73.5% of flagged) | 18 (3.0%) | 582 (97.0%) | 2.26 |
| static+dynamic | 400 | 193 (48.2%) | 160 (82.9% of flagged) | 33 (8.2%) | 367 (91.8%) | 1.69 |

## Round-0 detection decomposition (identical code, per sample)

n = 600 samples with outcomes in both arms (same round-0 code).

| Channel finding | Samples | % of shared |
|---|---|---|
| static AND dynamic | 31 | 5.2% |
| static only | 217 | 36.2% |
| dynamic only | 37 | 6.2% |
| neither | 315 | 52.5% |

Static channel flags 41.3% of initial samples; dynamic alone flags 11.3%; the union is 47.5% (dynamic-only adds 6.2% pp on top of static).

NOTE: the s+d arm used independent round-0 generations (legacy RQ2 cell) — its initial flag rate is distributionally, not exactly, comparable to the static/dynamic decomposition above.

## Per-problem paired contrasts (problem clean iff every sample clean)

### static vs dynamic (n = 200 problems)

- problem-level all-clean rate: static 95.0% vs dynamic 93.5%
- McNemar exact: b = 13 (static clean, dynamic not), c = 10 (reverse), p = 0.6776
- Wilcoxon on penalized rounds-to-clean (n_eff = 143): p = 1.792e-06, r = -0.399 (>0 = dynamic needs more rounds)
- Bootstrap 95% CI for clean-rate difference (dynamic − static): [-0.060, +0.030]

### static vs static+dynamic (n = 200 problems)

- problem-level all-clean rate: static 95.0% vs static+dynamic 87.0%
- McNemar exact: b = 22 (static clean, static+dynamic not), c = 6 (reverse), p = 0.003719
- Wilcoxon on penalized rounds-to-clean (n_eff = 155): p = 2.112e-06, r = +0.381 (>0 = static+dynamic needs more rounds)
- Bootstrap 95% CI for clean-rate difference (static+dynamic − static): [-0.130, -0.030]

### dynamic vs static+dynamic (n = 200 problems)

- problem-level all-clean rate: dynamic 93.5% vs static+dynamic 87.0%
- McNemar exact: b = 21 (dynamic clean, static+dynamic not), c = 8 (reverse), p = 0.02412
- Wilcoxon on penalized rounds-to-clean (n_eff = 134): p = 3.231e-13, r = +0.629 (>0 = static+dynamic needs more rounds)
- Bootstrap 95% CI for clean-rate difference (static+dynamic − dynamic): [-0.115, -0.015]

## Caveats

1. Own-channel outcomes: 'clean' under the static arm ignores dynamic
   findings and vice versa; only the s+d arm enforces the full gate.
2. Healing effectiveness (healed-fraction, rounds) is computed among
   each arm's own initially-flagged samples — different denominators.
3. See rq2_paired_report.md for the s+d sticky-finding breakdown.
