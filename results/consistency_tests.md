# Cross-model consistency: pre-registered significance tests

Unit = problem (n = 974); label = majority-of-3 samples flagged
at generation (round 0, main cells).

## Cochran's Q (7 models)

Q = 326.60, df = 6, p = 1.62e-67.

## Per-model majority-flagged share with Wilson 95% CIs

| Model | flagged (majority) | share | Wilson 95% CI |
|---|---:|---:|---|
| DeepSeek V4 Pro | 585 | 60.1% | [57.0%, 63.1%] |
| GPT-5.6 | 507 | 52.1% | [48.9%, 55.2%] |
| Gemini 3.1 Pro | 351 | 36.0% | [33.1%, 39.1%] |
| Kimi K3 | 512 | 52.6% | [49.4%, 55.7%] |
| GLM-5.1 | 634 | 65.1% | [62.0%, 68.0%] |
| Qwen Max | 551 | 56.6% | [53.4%, 59.7%] |
| Claude Fable 5 | 401 | 41.2% | [38.1%, 44.3%] |

## Pairwise exact McNemar (21 pairs, Holm-adjusted)

| Pair | a-only | b-only | raw p | Holm p | Cohen's g | sig. |
|---|---:|---:|---:|---:|---:|---|
| DeepSeek V4 Pro vs GPT-5.6 | 244 | 166 | 0.000137 | 0.00096 | -0.095 | yes |
| DeepSeek V4 Pro vs Gemini 3.1 Pro | 291 | 57 | 6.16e-39 | 1.23e-37 | -0.336 | yes |
| DeepSeek V4 Pro vs Kimi K3 | 187 | 114 | 3.06e-05 | 0.000245 | -0.121 | yes |
| DeepSeek V4 Pro vs GLM-5.1 | 122 | 171 | 0.00496 | 0.0298 | +0.084 | yes |
| DeepSeek V4 Pro vs Qwen Max | 176 | 142 | 0.0641 | 0.179 | -0.053 | no |
| DeepSeek V4 Pro vs Claude Fable 5 | 274 | 90 | 9.94e-23 | 1.69e-21 | -0.253 | yes |
| GPT-5.6 vs Gemini 3.1 Pro | 283 | 127 | 9.23e-15 | 1.38e-13 | -0.190 | yes |
| GPT-5.6 vs Kimi K3 | 168 | 173 | 0.829 | 0.829 | +0.007 | no |
| GPT-5.6 vs GLM-5.1 | 114 | 241 | 1.39e-11 | 1.8e-10 | +0.179 | yes |
| GPT-5.6 vs Qwen Max | 208 | 252 | 0.0449 | 0.179 | +0.048 | no |
| GPT-5.6 vs Claude Fable 5 | 233 | 127 | 2.5e-08 | 2.5e-07 | -0.147 | yes |
| Gemini 3.1 Pro vs Kimi K3 | 99 | 260 | 8.45e-18 | 1.35e-16 | +0.224 | yes |
| Gemini 3.1 Pro vs GLM-5.1 | 65 | 348 | 7.49e-48 | 1.57e-46 | +0.343 | yes |
| Gemini 3.1 Pro vs Qwen Max | 91 | 291 | 1.7e-25 | 3.06e-24 | +0.262 | yes |
| Gemini 3.1 Pro vs Claude Fable 5 | 131 | 181 | 0.00545 | 0.0298 | +0.080 | yes |
| Kimi K3 vs GLM-5.1 | 114 | 236 | 6.43e-11 | 7.71e-10 | +0.174 | yes |
| Kimi K3 vs Qwen Max | 175 | 214 | 0.0539 | 0.179 | +0.050 | no |
| Kimi K3 vs Claude Fable 5 | 206 | 95 | 1.43e-10 | 1.57e-09 | -0.184 | yes |
| GLM-5.1 vs Qwen Max | 221 | 138 | 1.39e-05 | 0.000125 | -0.116 | yes |
| GLM-5.1 vs Claude Fable 5 | 327 | 94 | 2.98e-31 | 5.65e-30 | -0.277 | yes |
| Qwen Max vs Claude Fable 5 | 293 | 143 | 5.72e-13 | 8.01e-12 | -0.172 | yes |

Holm-adjusted significant pairs: 17 of 21.

- Gemini 3.1 Pro vs GLM-5.1: p = 1.57e-46, Cohen's g = +0.343
- DeepSeek V4 Pro vs Gemini 3.1 Pro: p = 1.23e-37, Cohen's g = -0.336
- GLM-5.1 vs Claude Fable 5: p = 5.65e-30, Cohen's g = -0.277
- Gemini 3.1 Pro vs Qwen Max: p = 3.06e-24, Cohen's g = +0.262
- DeepSeek V4 Pro vs Claude Fable 5: p = 1.69e-21, Cohen's g = -0.253
- Gemini 3.1 Pro vs Kimi K3: p = 1.35e-16, Cohen's g = +0.224
- GPT-5.6 vs Gemini 3.1 Pro: p = 1.38e-13, Cohen's g = -0.190
- Kimi K3 vs Claude Fable 5: p = 1.57e-09, Cohen's g = -0.184
- GPT-5.6 vs GLM-5.1: p = 1.8e-10, Cohen's g = +0.179
- Kimi K3 vs GLM-5.1: p = 7.71e-10, Cohen's g = +0.174
- Qwen Max vs Claude Fable 5: p = 8.01e-12, Cohen's g = -0.172
- GPT-5.6 vs Claude Fable 5: p = 2.5e-07, Cohen's g = -0.147
- DeepSeek V4 Pro vs Kimi K3: p = 0.000245, Cohen's g = -0.121
- GLM-5.1 vs Qwen Max: p = 0.000125, Cohen's g = -0.116
- DeepSeek V4 Pro vs GPT-5.6: p = 0.00096, Cohen's g = -0.095
- DeepSeek V4 Pro vs GLM-5.1: p = 0.0298, Cohen's g = +0.084
- Gemini 3.1 Pro vs Claude Fable 5: p = 0.0298, Cohen's g = +0.080
