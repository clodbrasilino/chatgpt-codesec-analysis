# RQ5: cost-benefit analysis (generation vs repair; models and ablations)

Failed calls are excluded from the scientific cost figures (zero
token cost; engineering concern -- see rq5_cost_dynamics.md for
the reconciliation). Generation tokens are estimates (~3.6
chars/token); repair tokens are exact ledger (ok calls).
Cost to fix = repair tokens per passed program.

## A. Models (main cells, full population)

| Model | gen tok/prog (est) | repair tok/prog | pass @horizon | repair tok per pass | mean repair latency (s) | repair s per pass |
|---|---:|---:|---:|---:|---:|---:|
| DeepSeek V4 Pro | 548 | 4,158 | 79.7% | 5,214 | 9.1 | 33.0 |
| GPT-5.6 | 605 | 4,909 | 76.6% | 6,407 | 9.3 | 36.3 |
| Gemini 3.1 Pro | 468 | 1,109 | 97.3% | 1,140 | 16.0 | 14.2 |
| Kimi K3 | 559 | 4,137 | 77.9% | 5,308 | 12.6 | 47.5 |
| GLM-5.1 | 470 | 3,257 | 83.7% | 3,891 | 5.2 | 21.2 |
| Qwen Max | 363 | 1,889 | 86.0% | 2,196 | 8.4 | 22.3 |
| Claude Fable 5 | 584 | 5,204 | 87.2% | 5,970 | 19.0 | 39.2 |

## B. Gate usage (200-problem subset; cost-benefit against the
## common full-gate criterion from the cross-evaluation)

| Model / arm | repair tok/prog | pass (common crit) | repair tok per common-crit pass | mean latency (s) |
|---|---:|---:|---:|---:|
| DeepSeek V4 Pro / static-only | 4,944 | 343 (57.2%) | 8,649 | 14.7 |
| DeepSeek V4 Pro / dynamic-only | 713 | 218 (36.3%) | 1,962 | 6.0 |
| DeepSeek V4 Pro / full gate | 7,159 | 439 (73.2%) | 9,784 | 11.6 |
| GPT-5.6 / static-only | 7,641 | 336 (56.0%) | 13,645 | 9.5 |
| GPT-5.6 / dynamic-only | 51 | 298 (49.7%) | 103 | 8.8 |
| GPT-5.6 / full gate | 7,045 | 437 (72.8%) | 9,673 | 11.2 |
| Gemini 3.1 Pro / static-only | 1,853 | 448 (74.7%) | 2,481 | 17.7 |
| Gemini 3.1 Pro / dynamic-only | 302 | 295 (49.2%) | 613 | 17.7 |
| Gemini 3.1 Pro / full gate | 1,994 | 572 (95.3%) | 2,092 | 16.1 |
| Kimi K3 / static-only | 7,831 | 287 (47.8%) | 16,371 | 18.7 |
| Kimi K3 / dynamic-only | 581 | 211 (35.2%) | 1,652 | 17.4 |
| Kimi K3 / full gate | 7,493 | 416 (69.3%) | 10,807 | 15.7 |
| GLM-5.1 / static-only | 4,326 | 350 (58.3%) | 7,415 | 7.3 |
| GLM-5.1 / dynamic-only | 516 | 241 (40.2%) | 1,285 | 8.7 |
| GLM-5.1 / full gate | 4,617 | 467 (77.8%) | 5,932 | 6.9 |
| Qwen Max / static-only | 1,572 | 375 (62.5%) | 2,515 | 9.0 |
| Qwen Max / dynamic-only | 607 | 267 (44.5%) | 1,364 | 9.6 |
| Qwen Max / full gate | 3,173 | 472 (78.7%) | 4,034 | 10.8 |
| Claude Fable 5 / static-only | 9,045 | 355 (59.2%) | 15,287 | 19.9 |
| Claude Fable 5 / dynamic-only | 972 | 276 (46.0%) | 2,113 | 23.1 |
| Claude Fable 5 / full gate | 9,524 | 473 (78.8%) | 12,081 | 20.6 |

## C. Thinking ablation (full-gate cells, 200-problem subset)

| Model | arm | repair tok/prog | pass @horizon | repair tok per pass |
|---|---|---:|---:|---:|
| DeepSeek V4 Pro base | 7,159 | 439 (73.2%) | 9,784 |
| DeepSeek V4 Pro thinking | 8,210 | 541 (90.2%) | 9,106 |
| GPT-5.6 base | 7,045 | 437 (72.8%) | 9,673 |
| GPT-5.6 thinking | 8,444 | 536 (89.3%) | 9,452 |
| Gemini 3.1 Pro base | 1,994 | 572 (95.3%) | 2,092 |
| Gemini 3.1 Pro thinking | 1,923 | 578 (96.3%) | 1,996 |
| Kimi K3 base | 7,493 | 416 (69.3%) | 10,807 |
| Kimi K3 thinking | 11,190 | 542 (90.3%) | 12,388 |
| GLM-5.1 base | 4,617 | 467 (77.8%) | 5,932 |
| GLM-5.1 thinking | 13,616 | 563 (93.8%) | 14,511 |

## D. Sampling ablation (full-gate cells, 200-problem subset)

| Model | arm | repair tok/prog | pass @horizon | repair tok per pass |
|---|---|---:|---:|---:|
| DeepSeek V4 Pro t=1.0 p=1.0 | 7,159 | 439 (73.2%) | 9,784 |
| DeepSeek V4 Pro t=0.2 p=1.0 | 3,987 | 372 (62.0%) | 6,431 |
| DeepSeek V4 Pro t=1.0 p=0.5 | 7,043 | 442 (73.7%) | 9,560 |
| Gemini 3.1 Pro t=1.0 p=1.0 | 1,994 | 572 (95.3%) | 2,092 |
| Gemini 3.1 Pro t=0.2 p=1.0 | 2,317 | 582 (97.0%) | 2,389 |
| Gemini 3.1 Pro t=1.0 p=0.5 | 2,083 | 588 (98.0%) | 2,125 |
| GLM-5.1 t=1.0 p=1.0 | 4,617 | 467 (77.8%) | 5,932 |
| GLM-5.1 t=0.2 p=1.0 | 4,908 | 471 (78.5%) | 6,253 |
| GLM-5.1 t=1.0 p=0.5 | 4,672 | 482 (80.3%) | 5,815 |
| Qwen Max t=1.0 p=1.0 | 3,173 | 472 (78.7%) | 4,034 |
| Qwen Max t=0.2 p=1.0 | 3,066 | 489 (81.5%) | 3,762 |
| Qwen Max t=1.0 p=0.5 | 3,006 | 482 (80.3%) | 3,742 |

## Caveats

- Gemini 3.1 Pro's ledger covers only part of its main run
  (1,110 of 2,922 programs): its per-program costs are
  underestimates.
- Tokens-per-pass in the gate-usage comparison counts
  detection-free passes, which cost zero repair tokens; the
  dynamic-only arm's low tokens-per-pass largely reflects that
  selection (49% common-criterion pass, mostly detection-free).
- DeepSeek's t=0.2 cell fails the validity gate (heal_failed
  158 > 50); its row is indicative only.
- Generation tokens are estimates (no generation ledger).
