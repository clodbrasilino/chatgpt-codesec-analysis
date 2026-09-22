# RQ3 final paired analysis (problem-level, full gate)

200-task vulnerable-prone subset (task ids from manifest outcomes), 3 samples per arm, horizon = 5 rounds with a COMMON censor applied to both arms (primary). Sensitivity: as-recorded outcomes (cells differ in recorded budget).

### Primary (common 5-round censor)

| Model | n problems | Q1 detection-free base→think | Δ | 95% CI | McNemar b/c (p) | Wilcoxon (p, r) |
|---|---:|---|---:|---|---|---|---|
| DeepSeek V4 Pro | 200 | 34.5% → 49.2% | +14.7pp | [+9.2, +20.2] | 12/50 (p=1.21e-06) | p=4.55e-07, r=+0.518 |
| GPT-5.6 | 200 | 49.3% → 42.7% | -6.7pp | [-11.2, -2.2] | 23/11 (p=0.0576) | p=0.00521, r=-0.362 |
| Gemini 3.1 Pro | 200 | 48.2% → 52.3% | +4.2pp | [-2.5, +10.8] | 30/40 (p=0.282) | p=0.255, r=+0.117 |
| Kimi K3 | 200 | 34.5% → 39.7% | +5.2pp | [+0.3, +10.0] | 17/33 (p=0.0328) | p=0.0549, r=+0.215 |
| GLM-5.1 | 200 | 39.3% → 47.3% | +8.0pp | [+2.5, +13.5] | 20/37 (p=0.0331) | p=0.00572, r=+0.296 |

| Model | flagged base | flagged think | Q2 repair base→think | Δ | 95% CI | overall pass base→think |
|---|---:|---:|---|---:|---|---|
| DeepSeek V4 Pro | 393 | 305 | 59.0% → 80.7% | +21.6pp | [+15.1, +28.1] | 73.2% → 90.2% |
| GPT-5.6 | 304 | 344 | 46.4% → 81.4% | +35.0pp | [+26.5, +43.2] | 72.8% → 89.3% |
| Gemini 3.1 Pro | 311 | 286 | 91.0% → 92.3% | +1.3pp | [-2.7, +5.2] | 95.3% → 96.3% |
| Kimi K3 | 393 | 362 | 53.2% → 84.0% | +30.8pp | [+25.0, +36.7] | 69.3% → 90.3% |
| GLM-5.1 | 364 | 316 | 63.5% → 88.3% | +24.8pp | [+18.0, +31.8] | 77.8% → 93.8% |

### Sensitivity (as-recorded outcomes)

| Model | n problems | Q1 detection-free base→think | Δ | 95% CI | McNemar b/c (p) | Wilcoxon (p, r) |
|---|---:|---|---:|---|---|---|---|
| DeepSeek V4 Pro | 200 | 34.5% → 49.2% | +14.7pp | [+9.3, +20.2] | 12/50 (p=1.21e-06) | p=4.55e-07, r=+0.518 |
| GPT-5.6 | 200 | 49.3% → 42.7% | -6.7pp | [-11.3, -2.0] | 23/11 (p=0.0576) | p=0.00521, r=-0.362 |
| Gemini 3.1 Pro | 200 | 48.2% → 52.3% | +4.2pp | [-2.5, +10.8] | 30/40 (p=0.282) | p=0.255, r=+0.117 |
| Kimi K3 | 200 | 34.5% → 39.7% | +5.2pp | [+0.3, +10.2] | 17/33 (p=0.0328) | p=0.0549, r=+0.215 |
| GLM-5.1 | 200 | 39.3% → 47.3% | +8.0pp | [+2.5, +13.5] | 20/37 (p=0.0331) | p=0.00572, r=+0.296 |

| Model | flagged base | flagged think | Q2 repair base→think | Δ | 95% CI | overall pass base→think |
|---|---:|---:|---|---:|---|---|
| DeepSeek V4 Pro | 393 | 305 | 65.9% → 80.7% | +14.8pp | [+8.4, +21.0] | 77.7% → 90.2% |
| GPT-5.6 | 304 | 344 | 56.2% → 89.8% | +33.6pp | [+26.1, +40.9] | 77.8% → 94.2% |
| Gemini 3.1 Pro | 311 | 286 | 94.2% → 92.7% | -1.6pp | [-5.7, +2.2] | 97.0% → 96.5% |
| Kimi K3 | 393 | 362 | 56.7% → 84.0% | +27.2pp | [+21.3, +33.1] | 71.7% → 90.3% |
| GLM-5.1 | 364 | 316 | 69.2% → 94.3% | +25.1pp | [+18.4, +31.7] | 81.3% → 97.0% |
