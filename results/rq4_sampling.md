# RQ4: sampling-parameter ablation (200-problem subset, full gate)

Grid arms vs the main cell (t=1.0, p=1.0): temperature 0.2 and
top_p 0.5, non-thinking, 3 samples per arm, problem-level pairing
(200 problems; ids from manifest outcomes). Primary = common
five-round censor on all arms; as-recorded = sensitivity.
Models: DeepSeek V4 Pro, Gemini 3.1 Pro, GLM-5.1, Qwen Max
(Kimi K3's host rejects sampling parameters; GPT-5.6 and Claude
Fable 5 grid cells do not exist). DeepSeek's t0.2 cell fails the
validity gate (heal_failed 158 > 50) and is excluded from tests.

## Primary (common 5-round censor)

### t=0.2 (vs t=1.0)

| Model | n | det-free @gen main → grid | Δ (95% CI) | pass @horizon main → grid | Δ (95% CI) | McNemar x/y (p) | Wilcoxon (p, r) |
|---|---:|---|---|---|---|---|---|
| DeepSeek V4 Pro | — | invalid (excluded) | | | | | |
| Gemini 3.1 Pro | 200 | 48.2% → 52.0% | +3.8pp [-0.3, +8.0] | 95.3% → 97.0% | +1.7pp [+0.2, +3.5] | 1/3 (0.625) | p=0.0869, r=+0.606 |
| GLM-5.1 | 200 | 39.3% → 42.3% | +3.0pp [-1.0, +7.0] | 77.8% → 78.5% | +0.7pp [-2.7, +4.0] | 12/11 (1) | p=0.674, r=+0.056 |
| Qwen Max | 200 | 42.5% → 43.0% | +0.5pp [-5.0, +5.7] | 78.7% → 81.5% | +2.8pp [-0.2, +5.8] | 10/8 (0.815) | p=0.0809, r=+0.247 |

### top_p=0.5 (vs top_p=1.0)

| Model | n | det-free @gen main → grid | Δ (95% CI) | pass @horizon main → grid | Δ (95% CI) | McNemar x/y (p) | Wilcoxon (p, r) |
|---|---:|---|---|---|---|---|---|
| DeepSeek V4 Pro | 200 | 34.5% → 37.5% | +3.0pp [-1.7, +7.8] | 73.2% → 73.7% | +0.5pp [-3.2, +4.2] | 15/14 (1) | p=0.895, r=+0.019 |
| Gemini 3.1 Pro | 200 | 48.2% → 51.8% | +3.7pp [-0.3, +7.7] | 95.3% → 98.0% | +2.7pp [+0.8, +4.8] | 1/4 (0.375) | p=0.00977, r=+0.780 |
| GLM-5.1 | 200 | 39.3% → 43.2% | +3.8pp [+0.0, +7.8] | 77.8% → 80.3% | +2.5pp [-1.0, +6.0] | 9/12 (0.664) | p=0.143, r=+0.208 |
| Qwen Max | 200 | 42.5% → 46.2% | +3.7pp [-1.7, +9.2] | 78.7% → 80.3% | +1.7pp [-1.2, +4.5] | 8/8 (1) | p=0.264, r=+0.160 |

## Sensitivity (as-recorded outcomes)

### t=0.2 (vs t=1.0)

| Model | n | det-free @gen main → grid | Δ (95% CI) | pass @horizon main → grid | Δ (95% CI) | McNemar x/y (p) | Wilcoxon (p, r) |
|---|---:|---|---|---|---|---|---|
| DeepSeek V4 Pro | — | invalid (excluded) | | | | | |
| Gemini 3.1 Pro | 200 | 48.2% → 52.0% | +3.8pp [-0.5, +8.0] | 97.0% → 98.2% | +1.2pp [-0.2, +2.5] | 1/1 (1) | p=0.146, r=+0.530 |
| GLM-5.1 | 200 | 39.3% → 42.3% | +3.0pp [-0.8, +7.0] | 81.3% → 82.0% | +0.7pp [-2.3, +3.7] | 7/9 (0.804) | p=0.643, r=+0.069 |
| Qwen Max | 200 | 42.5% → 43.0% | +0.5pp [-4.8, +5.8] | 81.7% → 84.2% | +2.5pp [-0.2, +5.2] | 10/7 (0.629) | p=0.0766, r=+0.270 |

### top_p=0.5 (vs top_p=1.0)

| Model | n | det-free @gen main → grid | Δ (95% CI) | pass @horizon main → grid | Δ (95% CI) | McNemar x/y (p) | Wilcoxon (p, r) |
|---|---:|---|---|---|---|---|---|
| DeepSeek V4 Pro | 200 | 34.5% → 37.5% | +3.0pp [-1.8, +7.8] | 77.7% → 77.3% | -0.3pp [-4.2, +3.5] | 16/13 (0.711) | p=0.698, r=-0.057 |
| Gemini 3.1 Pro | 200 | 48.2% → 51.8% | +3.7pp [-0.3, +7.7] | 97.0% → 98.3% | +1.3pp [+0.0, +3.0] | 1/2 (1) | p=0.141, r=+0.639 |
| GLM-5.1 | 200 | 39.3% → 43.2% | +3.8pp [-0.2, +7.8] | 81.3% → 82.5% | +1.2pp [-2.0, +4.5] | 10/11 (1) | p=0.477, r=+0.111 |
| Qwen Max | 200 | 42.5% → 46.2% | +3.7pp [-1.7, +9.2] | 81.7% → 84.2% | +2.5pp [-0.3, +5.2] | 7/6 (1) | p=0.098, r=+0.251 |

