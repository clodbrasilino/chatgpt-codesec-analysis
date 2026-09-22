# RQ5: USD costs (official pricing + exact ledgers)

FX: 1 USD = 6.7459 CNY (PBOC/CFETS central parity, 2026-09-22;
market band 6.696-6.701 the same day). CNY-native models (Kimi,
GLM, Qwen) converted at parity. Costing: prompt x in-rate +
completion x out-rate (reasoning tokens are a subset of
completion and bill as output -- verified on every ledger row).
All input billed at the cache-MISS rate (ledgers do not record
cache hits; conservative upper bound). DeepSeek: peak = 2x
off-peak; runs executed Beijing daytime, peak used for DeepSeek
rows (off-peak bound noted). Generation tokens are estimates
(~3.6 chars/token). Per-program stats: mean / std / median.

## USD prices used (per 1M tokens)

| Model | in $/M | out $/M | native |
|---|---:|---:|---|
| DeepSeek V4 Pro | 1.32 (peak) / 0.66 (off) | 3.96 / 1.98 | USD |
| GPT-5.6 | 5.000 | 30.00 | USD |
| Gemini 3.1 Pro | 2.000 | 12.00 | USD |
| Kimi K3 | 2.965 | 14.82 | CNY |
| GLM-5.1 | 0.889 | 3.56 | CNY |
| Qwen Max | 0.356 | 1.42 | CNY |
| Claude Fable 5 | 10.000 | 50.00 | USD |

## A. Models (main cells, full population, repair = exact ledger,
generation = estimate)

| Model | repair $/prog mean/std/median | gen est $/prog | total $/prog | pass @horizon | cost to fix ($/pass) | repair s/pass | total $ (cell) |
|---|---|---:|---:|---:|---:|---:|---:|
| DeepSeek V4 Pro | 0.010 / 0.020 / 0.002 | 0.0018 | 0.0122 | 2330 (79.7%) | 0.013 | 33.0 | 36 |
| GPT-5.6 | 0.081 / 0.144 / 0.009 | 0.0150 | 0.0964 | 2239 (76.6%) | 0.106 | 36.3 | 282 |
| Gemini 3.1 Pro | 0.007 / 0.024 / 0.000 | 0.0043 | 0.0114 | 2842 (97.3%) | 0.007 | 14.2 | 33 |
| Kimi K3 | 0.034 / 0.067 / 0.005 | 0.0068 | 0.0408 | 2277 (77.9%) | 0.044 | 47.5 | 119 |
| GLM-5.1 | 0.007 / 0.011 / 0.002 | 0.0013 | 0.0080 | 2446 (83.7%) | 0.008 | 21.2 | 23 |
| Qwen Max | 0.001 / 0.003 / 0.000 | 0.0004 | 0.0019 | 2514 (86.0%) | 0.002 | 22.3 | 5 |
| Claude Fable 5 | 0.169 / 0.378 / 0.000 | 0.0241 | 0.1927 | 2547 (87.2%) | 0.193 | 39.2 | 563 |
| **across models (repair $/prog)** | mean 0.044, std 0.062, median 0.010, min 0.001, max 0.169 | | | | | | |
| **across models (cost to fix $/pass)** | mean 0.053, std 0.072, median 0.013, min 0.002, max 0.193 | | | | | | |
| **ALL MODELS total (repair + gen est)** | | | | | | | **$1,062** |

DeepSeek off-peak bound: cell total $18 (vs $36 at peak).

## B. Gate usage (200-problem subset): USD per common-criterion pass

| Model / arm | repair $/prog | common-crit pass | $ per common-crit pass |
|---|---:|---:|---:|
| DeepSeek V4 Pro / static-only | 0.0124 | 343 (57.2%) | 0.022 |
| DeepSeek V4 Pro / dynamic-only | 0.0018 | 218 (36.3%) | 0.005 |
| DeepSeek V4 Pro / full gate | 0.0179 | 439 (73.2%) | 0.025 |
| GPT-5.6 / static-only | 0.1359 | 336 (56.0%) | 0.243 |
| GPT-5.6 / dynamic-only | 0.0008 | 298 (49.7%) | 0.002 |
| GPT-5.6 / full gate | 0.1184 | 437 (72.8%) | 0.163 |
| Gemini 3.1 Pro / static-only | 0.0152 | 448 (74.7%) | 0.020 |
| Gemini 3.1 Pro / dynamic-only | 0.0019 | 295 (49.2%) | 0.004 |
| Gemini 3.1 Pro / full gate | 0.0129 | 572 (95.3%) | 0.014 |
| Kimi K3 / static-only | 0.0696 | 287 (47.8%) | 0.145 |
| Kimi K3 / dynamic-only | 0.0048 | 211 (35.2%) | 0.014 |
| Kimi K3 / full gate | 0.0627 | 416 (69.3%) | 0.090 |
| GLM-5.1 / static-only | 0.0096 | 350 (58.3%) | 0.016 |
| GLM-5.1 / dynamic-only | 0.0011 | 241 (40.2%) | 0.003 |
| GLM-5.1 / full gate | 0.0095 | 467 (77.8%) | 0.012 |
| Qwen Max / static-only | 0.0012 | 375 (62.5%) | 0.002 |
| Qwen Max / dynamic-only | 0.0005 | 267 (44.5%) | 0.001 |
| Qwen Max / full gate | 0.0025 | 472 (78.7%) | 0.003 |
| Claude Fable 5 / static-only | 0.3022 | 355 (59.2%) | 0.511 |
| Claude Fable 5 / dynamic-only | 0.0345 | 276 (46.0%) | 0.075 |
| Claude Fable 5 / full gate | 0.3055 | 473 (78.8%) | 0.388 |

## C. Thinking ablation (subset): USD per pass and marginal USD per
## additional pass

| Model | arm | $/prog | pass | $/pass | marginal $/add. pass |
|---|---|---:|---:|---:|---:|
| DeepSeek V4 Pro | base | 0.0179 | 439 | 0.025 | |
| DeepSeek V4 Pro | thinking | 0.0294 | 541 | 0.033 | 0.07 |
| GPT-5.6 | base | 0.1184 | 437 | 0.163 | |
| GPT-5.6 | thinking | 0.1821 | 536 | 0.204 | 0.39 |
| Gemini 3.1 Pro | base | 0.0129 | 572 | 0.014 | |
| Gemini 3.1 Pro | thinking | 0.0127 | 578 | 0.013 | -0.02 |
| Kimi K3 | base | 0.0627 | 416 | 0.090 | |
| Kimi K3 | thinking | 0.1397 | 542 | 0.155 | 0.37 |
| GLM-5.1 | base | 0.0095 | 467 | 0.012 | |
| GLM-5.1 | thinking | 0.0453 | 563 | 0.048 | 0.22 |

## D. Sampling ablation (subset): USD per pass

| Model | arm | $/prog | pass | $/pass |
|---|---|---:|---:|---:|
| DeepSeek V4 Pro | t=1.0 p=1.0 | 0.0179 | 439 | 0.025 |
| DeepSeek V4 Pro | t=0.2 p=1.0 | 0.0106 | 372 | 0.017 |
| DeepSeek V4 Pro | t=1.0 p=0.5 | 0.0182 | 442 | 0.025 |
| Gemini 3.1 Pro | t=1.0 p=1.0 | 0.0129 | 572 | 0.014 |
| Gemini 3.1 Pro | t=0.2 p=1.0 | 0.0181 | 582 | 0.019 |
| Gemini 3.1 Pro | t=1.0 p=0.5 | 0.0165 | 588 | 0.017 |
| GLM-5.1 | t=1.0 p=1.0 | 0.0095 | 467 | 0.012 |
| GLM-5.1 | t=0.2 p=1.0 | 0.0108 | 471 | 0.014 |
| GLM-5.1 | t=1.0 p=0.5 | 0.0103 | 482 | 0.013 |
| Qwen Max | t=1.0 p=1.0 | 0.0025 | 472 | 0.003 |
| Qwen Max | t=0.2 p=1.0 | 0.0026 | 489 | 0.003 |
| Qwen Max | t=1.0 p=0.5 | 0.0025 | 482 | 0.003 |

## A2. Every cell separately: non-thinking vs thinking arms

Non-thinking rows are the main cells restricted to the same
200-problem subset as the thinking cells (600 programs), so the
arms are comparable; Qwen Max and Claude Fable 5 have no
thinking variant; Gemini 3.1 Pro's contrast is reasoning
low -> medium (its reasoning cannot be disabled). Generation is
EXACT for the thinking arms (their ledgers record generate
calls) and estimated for the non-thinking cells

| Cell | n | repair $/prog mean/std/median | gen est $/prog | pass @horizon | $/pass | s/pass | cell $ |
|---|---:|---|---:|---:|---:|---:|---:|
| Qwen Max (non-thinking) | 600 | 0.003 / 0.004 / 0.001 | 0.0004 | 472 (78.7%) | 0.003 | 42.8 | 2 |
| Claude Fable 5 (non-thinking) | 600 | 0.306 / 0.504 / 0.046 | 0.0241 | 473 (78.8%) | 0.388 | 75.8 | 198 |
| DeepSeek V4 Pro (non-thinking) | 600 | 0.018 / 0.028 / 0.004 | 0.0018 | 439 (73.2%) | 0.025 | 63.0 | 12 |
| DeepSeek V4 Pro (thinking) | 600 | 0.029 / 0.100 / 0.003 | 0.0277 | 541 (90.2%) | 0.033 | 210.0 | 34 |
| GPT-5.6 (non-thinking) | 600 | 0.118 / 0.185 / 0.007 | 0.0150 | 437 (72.8%) | 0.163 | 51.8 | 80 |
| GPT-5.6 (thinking) | 600 | 0.182 / 0.290 / 0.043 | 0.0553 | 536 (89.3%) | 0.204 | 134.0 | 142 |
| Gemini 3.1 Pro (non-thinking) | 600 | 0.013 / 0.033 / 0.005 | 0.0043 | 572 (95.3%) | 0.014 | 22.3 | 10 |
| Gemini 3.1 Pro (thinking) | 600 | 0.013 / 0.027 / 0.000 | 0.0088 | 578 (96.3%) | 0.013 | 45.9 | 13 |
| Kimi K3 (non-thinking) | 600 | 0.063 / 0.091 / 0.014 | 0.0068 | 416 (69.3%) | 0.090 | 92.8 | 42 |
| Kimi K3 (thinking) | 600 | 0.140 / 0.402 / 0.027 | 0.0447 | 542 (90.3%) | 0.155 | 357.2 | 111 |
| GLM-5.1 (non-thinking) | 600 | 0.010 / 0.016 / 0.002 | 0.0013 | 467 (77.8%) | 0.012 | 32.4 | 7 |
| GLM-5.1 (thinking) | 600 | 0.045 / 0.158 / 0.006 | 0.0130 | 563 (93.8%) | 0.048 | 194.2 | 35 |

## Caveats

- Gemini 3.1 Pro's ledger covers only 1,110 of 2,922 programs:
  its cell total and per-program costs are underestimates.
- All input at cache-miss rates (no cache fields in ledgers):
  upper bound; providers with high hit rates (Kimi, Qwen, GLM,
  Claude) bill less in practice.
- DeepSeek rows use PEAK rates (daytime runs); off-peak halves
  them. Routed via DashScope -- the actual bill may differ from
  vendor list prices (see model_pricing_official.md).
- Generation costs are estimates (~3.6 chars/token), spread
  uniformly per program; per-program std reflects repair only.
