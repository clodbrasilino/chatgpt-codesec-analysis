# RQ5: cost and execution-time dynamics (main cells, full population)

Exact repair-call ledgers; horizon = 5 rounds (censor). Failed
calls carry no token cost (token fields None on every failed
entry) -- retries cost attempts and latency only.

## 1. Ledger reconciliation

| Model | calls ok | calls failed | fail share | prompt tok (M) | completion tok (M) | reasoning tok (M) | mean latency s | wasted fail latency (h) |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| DeepSeek V4 Pro | 8,468 | 3,665 | 30.2% | 6.77 | 5.38 | 0.00 | 9.1 | 0.2 |
| GPT-5.6 | 8,755 | 3 | 0.0% | 7.69 | 6.65 | 0.00 | 9.3 | 0.2 |
| Gemini 3.1 Pro | 2,509 | 2,872 | 53.4% | 1.82 | 1.42 | 0.00 | 16.0 | 95.2 |
| Kimi K3 | 8,570 | 6,725 | 44.0% | 6.71 | 5.37 | 0.00 | 12.6 | 0.4 |
| GLM-5.1 | 10,016 | 2,990 | 23.0% | 5.42 | 4.09 | 0.00 | 5.2 | 0.2 |
| Qwen Max | 6,721 | 609 | 8.3% | 3.33 | 2.19 | 0.00 | 8.4 | 0.0 |
| Claude Fable 5 | 5,260 | 6,765 | 56.3% | 6.69 | 8.51 | 0.00 | 19.0 | 2.3 |

## 2. Per-outcome token attribution (all rounds, as recorded)

| Model | programs pass | tok/program pass | programs not-passed | tok/program not-passed | ratio (not/pass) |
|---|---:|---:|---:|---:|---:|
| DeepSeek V4 Pro | 1241 | 2,848 | 489 | 17,617 | 6.19x |
| GPT-5.6 | 921 | 4,360 | 565 | 18,282 | 4.19x |
| Gemini 3.1 Pro | 1054 | 1,953 | 56 | 21,104 | 10.81x |
| Kimi K3 | 974 | 2,734 | 566 | 16,652 | 6.09x |
| GLM-5.1 | 1560 | 2,890 | 342 | 14,648 | 5.07x |
| Qwen Max | 1293 | 1,483 | 345 | 10,445 | 7.04x |
| Claude Fable 5 | 911 | 5,542 | 303 | 33,523 | 6.05x |

## 3. Per-round fix rate (hazard), main cells

| Model | round 1 | round 2 | round 3 | round 4 | round 5 |
|---|---:|---:|---:|---:|---:|
| DeepSeek V4 Pro | 808/1730 (47%) | 209/922 (23%) | 54/713 (8%) | 46/659 (7%) | 21/613 (3%) |
| GPT-5.6 | 305/1486 (21%) | 288/1181 (24%) | 88/893 (10%) | 69/805 (9%) | 53/736 (7%) |
| Gemini 3.1 Pro | 796/1110 (72%) | 146/314 (46%) | 48/168 (29%) | 28/120 (23%) | 12/92 (13%) |
| Kimi K3 | 597/1540 (39%) | 143/943 (15%) | 75/800 (9%) | 43/725 (6%) | 37/682 (5%) |
| GLM-5.1 | 623/1902 (33%) | 419/1279 (33%) | 206/860 (24%) | 111/654 (17%) | 67/543 (12%) |
| Qwen Max | 882/1638 (54%) | 188/756 (25%) | 98/568 (17%) | 35/470 (7%) | 27/435 (6%) |
| Claude Fable 5 | 605/1214 (50%) | 92/609 (15%) | 64/517 (12%) | 43/453 (9%) | 35/410 (9%) |

## 4. Kaplan-Meier of rounds-to-pass + log-rank

KM curves in results/rq5_km.pdf/.png (censoring at round 5).

Pairwise log-rank (Holm-adjusted, alpha=0.05): significant pairs:
- GPT-5.6 vs Gemini 3.1 Pro: p = 1.02e-178
- Gemini 3.1 Pro vs Kimi K3: p = 5.55e-112
- Gemini 3.1 Pro vs GLM-5.1: p = 2.67e-100
- GPT-5.6 vs Qwen Max: p = 9.35e-86
- DeepSeek V4 Pro vs Gemini 3.1 Pro: p = 1.13e-76
- GPT-5.6 vs Claude Fable 5: p = 5.54e-63
- Gemini 3.1 Pro vs Claude Fable 5: p = 1.27e-59
- DeepSeek V4 Pro vs GPT-5.6: p = 1.36e-57
- DeepSeek V4 Pro vs GLM-5.1: p = 4.07e-54
- Kimi K3 vs GLM-5.1: p = 5.05e-51
- GLM-5.1 vs Qwen Max: p = 7.42e-49
- GLM-5.1 vs Claude Fable 5: p = 3.37e-45
- GPT-5.6 vs GLM-5.1: p = 6.83e-41
- Gemini 3.1 Pro vs Qwen Max: p = 1.37e-40
- GPT-5.6 vs Kimi K3: p = 2.7e-35
- Kimi K3 vs Qwen Max: p = 2e-27
- DeepSeek V4 Pro vs Qwen Max: p = 8.51e-13
- Kimi K3 vs Claude Fable 5: p = 1.15e-11
- DeepSeek V4 Pro vs Kimi K3: p = 4.71e-11
- DeepSeek V4 Pro vs Claude Fable 5: p = 4.87e-10
- Qwen Max vs Claude Fable 5: p = 1.41e-08

