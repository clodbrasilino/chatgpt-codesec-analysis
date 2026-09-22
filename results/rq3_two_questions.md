# RQ3: the two questions — thinking vs non-thinking, full gate

Design. Full-gate cells (`feedback-static+dynamic`), the same 200
problems on both arms (the vulnerable-prone top-200 subset; every
problem of the non-thinking arm is paired to the same problem in the
thinking arm), 3 independent samples per problem per arm (600 programs
each), t=1.0/p=1.0, horizon = 5 rounds (config-driven). Detection =
the analysis gate at round 0 (Q1) and pass-within-horizon (Q2).
Included: GPT-5.6 and GLM-5.1 (both arms valid). Gemini 3.1 Pro is
reported but its answers are INCONCLUSIVE for two reasons: (a) its
base arm already has reasoning enabled at the lowest available level
(Gemini's reasoning cannot be disabled), so the contrast is reasoning
low -> medium, not off -> on; and (b) the base arm is near ceiling
(97.0% pass @horizon; 94.2% repair success among flagged), leaving no
headroom. DeepSeek V4 Pro and Kimi K3 pending the heal-repair of their
thinking cells (transient failures); numbers refresh when repaired.

Paired statistics use the problem as the unit: McNemar exact on the
majority-of-3 problem label, Wilcoxon signed-rank on per-problem
counts (0-3) with rank-biserial r, and cluster bootstrap (10,000
resamples of the 200 problems) for rate differences (thinking - base).

## Q1 — Does thinking generate code with fewer detections?

Detection-free rate at generation = share of the 600 round-0 programs
with no gate finding (`clean_at_start`).

| Model | base | thinking | diff (T-B) | 95% CI | McNemar maj-3 (b/c, p) | Wilcoxon counts (p, r) |
|---|---:|---:|---:|---|---|---|
| GPT-5.6 | 49.3% | 42.7% | **-6.7pp** | [-11.3, -2.0] | 23/11, p = 0.058 | n=74, p = 0.005, r = -0.362 |
| GLM-5.1 | 39.3% | 47.3% | **+8.0pp** | [+2.5, +13.5] | 20/37, p = 0.033 | n=109, p = 0.006, r = +0.296 |
| Gemini 3.1 Pro | 48.2% | 52.3% | +4.2pp | [-2.7, +10.8] | 30/40, p = 0.28 | n=120, p = 0.26, r = +0.117 |

**Answer: no.** Thinking does not reliably reduce generation-time
detections — the effect is model-dependent and runs in OPPOSITE
directions: for GPT-5.6 thinking generates significantly MORE flagged
code (-6.7pp detection-free, Wilcoxon p = 0.005), for GLM-5.1 it
generates less (+8.0pp, p = 0.006). Gemini shows no significant
difference (+4.2pp, CI crossing zero), and its contrast is reasoning
low -> medium rather than off -> on, so it is uninformative for the
off-vs-on question. Across models the generation-time effect is
inconsistent and small relative to the repair effect (Q2).

## Q2 — Does thinking repair detections better?

Repair success rate = among round-0 programs the gate FLAGGED, the
share that reach a pass state within the five-round horizon.

| Model | base | thinking | diff (T-B) | 95% CI (cluster bootstrap) |
|---|---:|---:|---:|---|
| GPT-5.6 | 56.2% (304 flagged) | 89.8% (344 flagged) | **+33.6pp** | [+26.0, +41.1] |
| GLM-5.1 | 69.2% (364 flagged) | 94.3% (316 flagged) | **+25.1pp** | [+18.5, +31.8] |
| Gemini 3.1 Pro | 94.2% (311 flagged) | 92.7% (286 flagged) | -1.6pp | [-5.7, +2.2] |

**Answer: yes, substantially — where measurable.** Conditioned on
being flagged, thinking repairs detections at a 25-34pp higher rate in
GPT-5.6 and GLM-5.1, with cluster bootstrap CIs far from zero. For
Gemini the metric is saturated (base arm already repairs 94.2% of
flagged programs within the horizon), the difference is -1.6pp with a
CI crossing zero, and the arm contrast is reasoning low -> medium, so
its Q2 answer is inconclusive by ceiling and by design. Consistent with the
unconditioned contrast (pass @horizon 77.8% -> 94.2% for GPT,
81.3% -> 97.0% for GLM; McNemar p = 7.3e-07 / 2.3e-07) and with the
penalized rounds statistic (Wilcoxon effect r = -0.29 both models:
thinking reaches passes in fewer rounds on the same problems).

## Reading the two questions together

The thinking effect under the full gate is a REPAIR effect, not a
generation effect: it does not reliably produce detection-free code on
the first attempt (and can produce more flagged code, as for GPT-5.6),
but given flagged code it repairs it far more often within the same
five-round budget. Cost: 2.6-6.1x completion tokens (reasoning-
dominated) and 4.3-14.4x latency per call.

## Caveats

1. The two arms' flagged pools differ (stochastic sampling, t=1.0):
   conditioning on "flagged" selects different program mixes per arm
   (e.g., GPT thinking has 344 flagged vs 304 base). The
   repair-conditioned rates are measured associations, not a
   randomized contrast.
2. Per-problem pairing treats the 3 samples as repeated measurements
   of the same problem; samples are independent generations, so the
   pairing is by problem, not by shared randomness.
3. Gemini excluded (saturation); DeepSeek/Kimi to be inserted after
   cell repair; pooled numbers refresh then.
4. The subset is the vulnerable-prone top-200, so base pass rates are
   lower than on the full 974-task population by construction.
5. Thinking cells record max_rounds = 10 but are reported at the
   configured 5-round horizon, identically to the base cells.
