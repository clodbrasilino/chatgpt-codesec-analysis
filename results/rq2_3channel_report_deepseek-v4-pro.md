# RQ2 three-channel feedback ablation (top-200 vulnerable subset)

Model: **deepseek-v4-pro**. Arms: static (RQ1 round-0), dynamic (same round-0 via
gen-source), static+dynamic. Outcomes are relative to each arm's own
feedback channels (gate asymmetry applies to cross-arm clean rates).
Generated: 2026-09-03.

## Per-arm descriptives (sample level)

| Arm | n | Flagged at start | Healed | Never cleaned | Final own-channel clean | Mean rounds (healed) |
|---|---|---|---|---|---|---|
| static | 600 | 237 (39.5%) | 225 (94.9% of flagged) | 12 (2.0%) | 588 (98.0%) | 1.39 |
| dynamic | 600 | 41 (6.8%) | 13 (31.7% of flagged) | 28 (4.7%) | 572 (95.3%) | 1.69 |
| static+dynamic | 600 | 263 (43.8%) | 230 (87.5% of flagged) | 33 (5.5%) | 567 (94.5%) | 1.38 |

## Round-0 detection decomposition (identical code, per sample)

n = 600 samples with outcomes in both arms (same round-0 code).

| Channel finding | Samples | % of shared |
|---|---|---|
| static AND dynamic | 21 | 3.5% |
| static only | 216 | 36.0% |
| dynamic only | 20 | 3.3% |
| neither | 343 | 57.2% |

Static channel flags 39.5% of initial samples; dynamic alone flags 6.8%; the union is 42.8% (dynamic-only adds 3.3% pp on top of static).

The s+d baseline shares the same round-0: its initial flags cover 43.8% of samples vs the static∪dynamic union 42.8% (6 samples differ — analyzer/timeout nondeterminism between cells).

## Per-problem paired contrasts (problem clean iff every sample clean)

### static vs dynamic (n = 200 problems)

- problem-level all-clean rate: static 95.0% vs dynamic 93.0%
- McNemar exact: b = 13 (static clean, dynamic not), c = 9 (reverse), p = 0.5235
- Wilcoxon on penalized rounds-to-clean (n_eff = 130): p = 1.603e-08, r = -0.496 (>0 = dynamic needs more rounds)
- Bootstrap 95% CI for clean-rate difference (dynamic − static): [-0.065, +0.025]

### static vs static+dynamic (n = 200 problems)

- problem-level all-clean rate: static 95.0% vs static+dynamic 88.5%
- McNemar exact: b = 15 (static clean, static+dynamic not), c = 2 (reverse), p = 0.00235
- Wilcoxon on penalized rounds-to-clean (n_eff = 45): p = 0.0007741, r = +0.501 (>0 = static+dynamic needs more rounds)
- Bootstrap 95% CI for clean-rate difference (static+dynamic − static): [-0.105, -0.025]

### dynamic vs static+dynamic (n = 200 problems)

- problem-level all-clean rate: dynamic 93.0% vs static+dynamic 88.5%
- McNemar exact: b = 10 (dynamic clean, static+dynamic not), c = 1 (reverse), p = 0.01172
- Wilcoxon on penalized rounds-to-clean (n_eff = 132): p = 3.406e-17, r = +0.734 (>0 = static+dynamic needs more rounds)
- Bootstrap 95% CI for clean-rate difference (static+dynamic − dynamic): [-0.080, -0.015]

## Caveats

1. Own-channel outcomes: 'clean' under the static arm ignores dynamic
   findings and vice versa; only the s+d arm enforces the full gate.
2. Healing effectiveness (healed-fraction, rounds) is computed among
   each arm's own initially-flagged samples — different denominators.
3. See rq2_paired_report.md for the s+d sticky-finding breakdown.
