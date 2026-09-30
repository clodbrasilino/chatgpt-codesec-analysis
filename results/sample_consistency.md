# Sample-level consistency of round-0 detections (main gate, s+d non-thinking)

Scope: 974 tasks x 3 samples per model (n = 2,922); detections =
gate reports at round 0 (generation). "Consistency" = share of
tasks with >=1 detection that are detected on ALL 3 samples.
Computed from the final manifests by `src/analysis/sample_consistency.py`.

## Within-model consistency — round-0 detections per task (0/1/2/3 samples flagged)

| Model | 0 | 1 | 2 | 3 | tasks flagged >=1 | all-3 | consistency |
|---|---:|---:|---:|---:|---:|---:|---:|
| Claude Fable 5 | 455 | 118 | 107 | 294 | 519 | 294 | 56.6% |
| GPT-5.6~Sol | 348 | 119 | 154 | 353 | 626 | 353 | 56.4% |
| Gemini 3.1 Pro | 438 | 185 | 128 | 223 | 536 | 223 | 41.6% |
| Kimi K3 | 248 | 214 | 210 | 302 | 726 | 302 | 41.6% |
| DeepSeek V4 Pro | 199 | 190 | 215 | 370 | 775 | 370 | 47.7% |
| Qwen Max | 257 | 166 | 181 | 370 | 717 | 370 | 51.6% |
| GLM-5.1 | 160 | 180 | 180 | 454 | 814 | 454 | 55.8% |

## Within-model consistency — still flagged at the five-round horizon

| Model | 0 | 1 | 2 | 3 | tasks >=1 | all-3 | consistency |
|---|---:|---:|---:|---:|---:|---:|---:|
| Claude Fable 5 | 775 | 80 | 62 | 57 | 199 | 57 | 28.6% |
| GPT-5.6~Sol | 597 | 165 | 118 | 94 | 377 | 94 | 24.9% |
| Gemini 3.1 Pro | 924 | 31 | 8 | 11 | 50 | 11 | 22.0% |
| Kimi K3 | 579 | 217 | 106 | 72 | 395 | 72 | 18.2% |
| DeepSeek V4 Pro | 616 | 191 | 100 | 67 | 358 | 67 | 18.7% |
| Qwen Max | 726 | 138 | 60 | 50 | 248 | 50 | 20.2% |
| GLM-5.1 | 683 | 163 | 71 | 57 | 291 | 57 | 19.6% |

## Cross-model agreement — tasks majority-flagged (>=2 of 3 samples) by N of 7 models

| Models flagging | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Tasks | 58 | 114 | 159 | 154 | 141 | 125 | 103 | 120 |

Of 974 tasks: 964 (99.0%) are flagged on at least one sample of at least one model; only 10 tasks are detection-free across every model and every sample.
[114, 159, 154, 141, 125, 103, 120]

916 (94.0%) are majority-flagged by at least one model; 489 (50.2%) by at least four; 120 (12.3%) by all seven.

Headline ranges: within-model generation consistency 41.6--56.6%; horizon persistence 18.2--28.6%.

