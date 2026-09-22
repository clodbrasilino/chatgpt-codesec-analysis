# Thinking vs non-thinking paired contrast (5 toggle-verified models, 200-task vulnerable-prone subset)

Subset: top-200 of `results/vulnerable_subset.csv` (ranked by generation findings, CWE-tool pairs, healing depth). Both arms: 3 samples/task, t=1.0/p=1.0. Base = reasoning off (r0; Gemini base = lowest available level), thinking = reasoning on (r1). Horizon: configured 5 rounds. Pre-registered tests: McNemar exact, Wilcoxon signed-rank, effect size r, bootstrap CI (alpha 0.05).

## static-only

### DeepSeek V4 Pro — static-only

Base `feedback-static-r0-t1.0-p1.0`: n=2922, heal_failed=0. Thinking `feedback-static-r1-t1.0-p1.0`: n=600, heal_failed=0.

| arm | programs | detection-free @gen | pass @horizon | clean | not_cleaned | heal_failed |
|---|---:|---:|---:|---:|---:|---:|
| base (subset) | 600 | 37.0% | 80.3% | 260 | 118 | 0 |
| thinking | 600 | 50.5% | 97.2% | 280 | 17 | 0 |

Paired problems: n = 200 (sample-1; horizon = 5 rounds, penalty = 6).

- **McNemar (exact)**: b = 4 (base pass, thinking not), c = 39 (reverse), p = 3.108e-08
- **Wilcoxon** on penalized rounds-to-clean (n_eff = 138): p = 3.17e-07, effect r = -0.435 (>0 = thinking needs more rounds)
- **Bootstrap 95% CI** pass-rate difference (thinking − base): [+0.115, +0.235]
- Sensitivity (all-3-samples bar, both arms): McNemar b = 6, c = 60, p = 2.726e-12; Wilcoxon p = 2.399e-12, r = -0.538; CI [+0.200, +0.340]

### GPT-5.6 — static-only

Base `feedback-static-r0-t1.0-p1.0`: n=2922, heal_failed=0. Thinking `feedback-static-r1-t1.0-p1.0`: n=600, heal_failed=0.

| arm | programs | detection-free @gen | pass @horizon | clean | not_cleaned | heal_failed |
|---|---:|---:|---:|---:|---:|---:|
| base (subset) | 600 | 49.8% | 77.8% | 168 | 133 | 0 |
| thinking | 600 | 42.7% | 94.3% | 310 | 34 | 0 |

Paired problems: n = 200 (sample-1; horizon = 5 rounds, penalty = 6).

- **McNemar (exact)**: b = 5 (base pass, thinking not), c = 46 (reverse), p = 2.328e-09
- **Wilcoxon** on penalized rounds-to-clean (n_eff = 123): p = 0.000397, effect r = -0.319 (>0 = thinking needs more rounds)
- **Bootstrap 95% CI** pass-rate difference (thinking − base): [+0.140, +0.270]
- Sensitivity (all-3-samples bar, both arms): McNemar b = 13, c = 62, p = 8.396e-09; Wilcoxon p = 0.0003036, r = -0.306; CI [+0.165, +0.320]

### Gemini 3.1 Pro — static-only

Base `feedback-static-r0-t1.0-p1.0`: n=2922, heal_failed=0. Thinking `feedback-static-r1-t1.0-p1.0`: n=600, heal_failed=0.

| arm | programs | detection-free @gen | pass @horizon | clean | not_cleaned | heal_failed |
|---|---:|---:|---:|---:|---:|---:|
| base (subset) | 600 | 50.7% | 100.0% | 296 | 0 | 0 |
| thinking | 600 | 53.8% | 99.0% | 271 | 6 | 0 |

Paired problems: n = 200 (sample-1; horizon = 5 rounds, penalty = 6).

- **McNemar (exact)**: b = 2 (base pass, thinking not), c = 0 (reverse), p = 0.5
- **Wilcoxon** on penalized rounds-to-clean (n_eff = 110): p = 0.5266, effect r = +0.060 (>0 = thinking needs more rounds)
- **Bootstrap 95% CI** pass-rate difference (thinking − base): [-0.025, +0.000]
- Sensitivity (all-3-samples bar, both arms): McNemar b = 6, c = 0, p = 0.03125; Wilcoxon p = 0.6563, r = +0.036; CI [-0.055, -0.010]

### Kimi K3 — static-only

Base `feedback-static-r0-t1.0-p1.0`: n=2922, heal_failed=0. Thinking `feedback-static-r1-t1.0-p1.0`: n=600, heal_failed=0.

| arm | programs | detection-free @gen | pass @horizon | clean | not_cleaned | heal_failed |
|---|---:|---:|---:|---:|---:|---:|
| base (subset) | 600 | 36.5% | 72.7% | 217 | 164 | 0 |
| thinking | 600 | 41.8% | 96.0% | 325 | 24 | 0 |

Paired problems: n = 200 (sample-1; horizon = 5 rounds, penalty = 6).

- **McNemar (exact)**: b = 4 (base pass, thinking not), c = 53 (reverse), p = 5.911e-12
- **Wilcoxon** on penalized rounds-to-clean (n_eff = 132): p = 2.422e-07, effect r = -0.449 (>0 = thinking needs more rounds)
- **Bootstrap 95% CI** pass-rate difference (thinking − base): [+0.180, +0.310]
- Sensitivity (all-3-samples bar, both arms): McNemar b = 7, c = 77, p = 5.138e-16; Wilcoxon p = 5.906e-11, r = -0.508; CI [+0.275, +0.425]

### GLM-5.1 — static-only

Base `feedback-static-r0-t1.0-p1.0`: n=2922, heal_failed=0. Thinking `feedback-static-r1-t1.0-p1.0`: n=600, heal_failed=0.

| arm | programs | detection-free @gen | pass @horizon | clean | not_cleaned | heal_failed |
|---|---:|---:|---:|---:|---:|---:|
| base (subset) | 600 | 40.7% | 84.0% | 260 | 96 | 0 |
| thinking | 600 | 48.2% | 98.5% | 302 | 9 | 0 |

Paired problems: n = 200 (sample-1; horizon = 5 rounds, penalty = 6).

- **McNemar (exact)**: b = 1 (base pass, thinking not), c = 28 (reverse), p = 1.118e-07
- **Wilcoxon** on penalized rounds-to-clean (n_eff = 115): p = 6.088e-05, effect r = -0.374 (>0 = thinking needs more rounds)
- **Bootstrap 95% CI** pass-rate difference (thinking − base): [+0.085, +0.185]
- Sensitivity (all-3-samples bar, both arms): McNemar b = 2, c = 45, p = 1.604e-11; Wilcoxon p = 1.632e-06, r = -0.369; CI [+0.155, +0.275]

## full gate

### DeepSeek V4 Pro — full gate

Base `feedback-static+dynamic-r0-t1.0-p1.0`: n=2922, heal_failed=0. Thinking `feedback-static+dynamic-r1-t1.0-p1.0`: heal_failed=89 > 50 (transient transport failures).

| arm | programs | detection-free @gen | pass @horizon | clean | not_cleaned | heal_failed |
|---|---:|---:|---:|---:|---:|---:|
| base (subset) | 600 | 34.5% | 77.7% | 259 | 134 | 0 |
| thinking | 600 | 49.2% | 84.7% | 213 | 3 | 89 |

**Excluded from paired tests** (validity gate).

### GPT-5.6 — full gate

Base `feedback-static+dynamic-r0-t1.0-p1.0`: n=2922, heal_failed=0. Thinking `feedback-static+dynamic-r1-t1.0-p1.0`: n=600, heal_failed=0.

| arm | programs | detection-free @gen | pass @horizon | clean | not_cleaned | heal_failed |
|---|---:|---:|---:|---:|---:|---:|
| base (subset) | 600 | 49.3% | 77.8% | 171 | 133 | 0 |
| thinking | 600 | 42.7% | 94.2% | 309 | 35 | 0 |

Paired problems: n = 200 (sample-1; horizon = 5 rounds, penalty = 6).

- **McNemar (exact)**: b = 9 (base pass, thinking not), c = 45 (reverse), p = 7.288e-07
- **Wilcoxon** on penalized rounds-to-clean (n_eff = 122): p = 0.001577, effect r = -0.286 (>0 = thinking needs more rounds)
- **Bootstrap 95% CI** pass-rate difference (thinking − base): [+0.115, +0.250]
- Sensitivity (all-3-samples bar, both arms): McNemar b = 12, c = 62, p = 2.856e-09; Wilcoxon p = 0.001018, r = -0.274; CI [+0.175, +0.330]

### Gemini 3.1 Pro — full gate

Base `feedback-static+dynamic-r0-t1.0-p1.0`: n=2922, heal_failed=0. Thinking `feedback-static+dynamic-r1-t1.0-p1.0`: n=600, heal_failed=8.

| arm | programs | detection-free @gen | pass @horizon | clean | not_cleaned | heal_failed |
|---|---:|---:|---:|---:|---:|---:|
| base (subset) | 600 | 48.2% | 97.0% | 293 | 18 | 0 |
| thinking | 600 | 52.3% | 96.5% | 265 | 13 | 8 |

Paired problems: n = 200 (sample-1; horizon = 5 rounds, penalty = 6).

- **McNemar (exact)**: b = 5 (base pass, thinking not), c = 2 (reverse), p = 0.4531
- **Wilcoxon** on penalized rounds-to-clean (n_eff = 111): p = 0.9376, effect r = +0.000 (>0 = thinking needs more rounds)
- **Bootstrap 95% CI** pass-rate difference (thinking − base): [-0.040, +0.010]
- Sensitivity (all-3-samples bar, both arms): McNemar b = 7, c = 5, p = 0.7744; Wilcoxon p = 0.06791, r = -0.153; CI [-0.045, +0.025]

### Kimi K3 — full gate

Base `feedback-static+dynamic-r0-t1.0-p1.0`: n=2922, heal_failed=0. Thinking `feedback-static+dynamic-r1-t1.0-p1.0`: heal_failed=84 > 50 (transient transport failures).

| arm | programs | detection-free @gen | pass @horizon | clean | not_cleaned | heal_failed |
|---|---:|---:|---:|---:|---:|---:|
| base (subset) | 600 | 34.5% | 71.7% | 223 | 170 | 0 |
| thinking | 600 | 39.7% | 82.8% | 259 | 19 | 84 |

**Excluded from paired tests** (validity gate).

### GLM-5.1 — full gate

Base `feedback-static+dynamic-r0-t1.0-p1.0`: n=2922, heal_failed=0. Thinking `feedback-static+dynamic-r1-t1.0-p1.0`: n=600, heal_failed=0.

| arm | programs | detection-free @gen | pass @horizon | clean | not_cleaned | heal_failed |
|---|---:|---:|---:|---:|---:|---:|
| base (subset) | 600 | 39.3% | 81.3% | 252 | 112 | 0 |
| thinking | 600 | 47.3% | 97.0% | 298 | 18 | 0 |

Paired problems: n = 200 (sample-1; horizon = 5 rounds, penalty = 6).

- **McNemar (exact)**: b = 3 (base pass, thinking not), c = 33 (reverse), p = 2.272e-07
- **Wilcoxon** on penalized rounds-to-clean (n_eff = 121): p = 0.001382, effect r = -0.291 (>0 = thinking needs more rounds)
- **Bootstrap 95% CI** pass-rate difference (thinking − base): [+0.095, +0.205]
- Sensitivity (all-3-samples bar, both arms): McNemar b = 4, c = 51, p = 2.047e-11; Wilcoxon p = 1.348e-09, r = -0.468; CI [+0.170, +0.300]

## Usage contrast (exact ledgers, subset-restricted)

Base ledgers filtered to the 200 subset task ids; thinking ledgers cover the subset by construction.

| Model | Config | ok/fail calls | prompt tok | completion tok | reasoning tok | mean s/call | completion tok/program |
|---|---|---:|---:|---:|---:|---:|---:|
| DeepSeek V4 Pro | static-only | 1514/2150 vs 1438/2204 | 1,632,987 vs 823,871 | 1,333,615 vs 6,943,572 | 0 vs 6,034,042 | 14.7 vs 87.7 | 11,573 |
| DeepSeek V4 Pro | full gate | 2389/1275 vs 730/3127 | 2,365,210 vs 570,675 | 1,930,074 vs 3,623,782 | 0 vs 3,167,922 | 11.6 vs 132.6 | 6,040 |
| GPT-5.6 | static-only | 2560/144 vs 2020/204 | 2,240,643 vs 1,700,503 | 2,344,087 vs 4,380,503 | 0 vs 2,336,992 | 9.5 vs 46.1 | 7,301 |
| GPT-5.6 | full gate | 2022/1 vs 1480/4 | 2,230,395 vs 1,708,810 | 1,996,519 vs 3,357,466 | 0 vs 1,742,089 | 11.2 vs 48.5 | 5,596 |
| Gemini 3.1 Pro | static-only | 1043/4582 vs 1104/542 | 421,612 vs 552,024 | 689,889 vs 855,716 | 0 vs 0 | 17.7 vs 32.3 | 1,426 |
| Gemini 3.1 Pro | full gate | 793/766 vs 658/698 | 661,837 vs 623,222 | 534,749 vs 530,655 | 0 vs 0 | 16.1 vs 40.3 | 884 |
| Kimi K3 | static-only | 2759/3643 vs 1601/6620 | 2,353,626 vs 1,253,431 | 2,344,779 vs 4,952,240 | 0 vs 3,532,246 | 18.7 vs 75.1 | 8,254 |
| Kimi K3 | full gate | 2463/1890 vs 1055/5463 | 2,446,838 vs 1,167,146 | 2,048,854 vs 4,801,632 | 0 vs 3,792,919 | 15.7 vs 166.5 | 8,003 |
| GLM-5.1 | static-only | 2364/2200 vs 1362/3598 | 1,312,273 vs 628,551 | 1,283,128 vs 5,791,207 | 0 vs 5,016,067 | 7.3 vs 63.1 | 9,652 |
| GLM-5.1 | full gate | 2192/1060 vs 930/2652 | 1,554,105 vs 709,625 | 1,216,159 vs 7,459,974 | 0 vs 6,888,185 | 6.9 vs 117.5 | 12,433 |

