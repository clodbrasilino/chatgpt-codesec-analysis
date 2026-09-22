# Hypothesis check: "It is beneficial to not use thinking when using this technique"

User hypothesis: the time and money cost of thinking (especially at
generation) is too high, and its benefits are not enough.

Scope: 200-problem vulnerable-prone subset, full gate, 3 samples per
arm, common five-round censor, 5 toggle-verified models (Qwen Max and
Claude Fable 5 have no thinking variant; Gemini 3.1 Pro's contrast is
reasoning low -> medium with a near-ceiling base arm). Dollar figures
under the worst-case assumptions of results/rq5_usd_costs.md
(cache-miss input; DeepSeek peak; GLM-5.1 <32K tier; 6.7459 CNY/USD).
Sources: results/rq3_paired_final.md, rq5_usd_costs.md (A2),
thinking_tokens_hist.md, model_pricing_official.md.

The hypothesis decomposes into three testable claims:

## Claim 1: the generation-phase cost is too high -- SUPPORTED

Generation tokens per program (base -> thinking):

| Model | gen tok/prog | multiplier |
|---|---:|---:|
| DeepSeek V4 Pro | 548 -> 7,105 | 13.0x |
| GLM-5.1 | 470 -> 3,740 | 8.0x |
| Kimi K3 | 559 -> 3,157 | 5.6x |
| GPT-5.6 | 605 -> 1,924 | 3.2x |
| Gemini 3.1 Pro | 468 -> 818 | 1.7x |

And what does this spend buy at generation? The detection-free rate
moves by at most +14.7pp and is model-specific in BOTH directions
(DeepSeek +14.7pp, p = 4.6e-07; GLM-5.1 +8.0pp, p = 0.006; Kimi +5.2pp,
McNemar p = 0.033; GPT-5.6 -6.7pp, p = 0.005 -- significantly WORSE;
Gemini +4.2pp, n.s.). For GPT-5.6 the generation-phase reasoning spend
is actively counterproductive. There is no reliable generation-time
benefit that could justify a 1.7-13x generation-cost multiplier.

## Claim 2: the repair-phase benefit is real -- SUPPORTED (it exists)

Pass rate at the horizon (base -> thinking): DeepSeek 73.2% -> 90.2%
(+17.0pp), GPT-5.6 72.8% -> 89.3% (+16.5pp), Kimi K3 69.3% -> 90.3%
(+21.0pp), GLM-5.1 77.8% -> 93.8% (+16.0pp) -- all bootstrap CIs
exclude zero. Gemini 95.3% -> 96.3% (+1.0pp, n.s.; ceiling). Pooled:
+229 passed programs of 3,000 (+7.6pp).

## Claim 3: the benefits are not enough (cost-efficiency) -- SUPPORTED for every model

Dollars (worst case) and time, per cell (600 programs):

| Model | $/prog | $/pass | passes per $ | repair s/pass | marginal $ per add. pass |
|---|---|---|---|---|---:|
| DeepSeek | 0.020 -> 0.057 | 0.025 -> 0.033 | 36.6 -> 15.9 (-57%) | 63 -> 210 (3.3x) | 0.07 (vs rate 0.025) |
| GPT-5.6 | 0.133 -> 0.237 | 0.163 -> 0.204 | 5.5 -> 3.8 (-31%) | 52 -> 134 (2.6x) | 0.39 (vs 0.163) |
| Kimi K3 | 0.070 -> 0.185 | 0.090 -> 0.155 | 9.9 -> 4.9 (-51%) | 93 -> 357 (3.8x) | 0.37 (vs 0.090) |
| GLM-5.1 | 0.011 -> 0.058 | 0.012 -> 0.048 | 66.7 -> 16.1 (-76%) | 32 -> 194 (6.0x) | 0.22 (vs 0.012) |
| Gemini | 0.017 -> 0.022 | 0.014 -> 0.013 | 57.2 -> 44.5 (-22%) | 22 -> 46 (2.1x) | n.s. (ceiling) |

- **Cost-efficiency (passes per dollar) falls for EVERY model**:
  -22% (Gemini) to -76% (GLM-5.1). Per-call latency rises 2.5-17x.
- **Tokens**: pooled totals 36.1M vs 19.2M (1.88x) for the +229 passes
  = ~39,300 tokens per additional passed program.
- The marginal dollar is always spent at a worse rate than the
  average: marginal $/additional pass exceeds the model's own base
  $/pass by 2.4x (GPT-5.6), 2.8x (DeepSeek), 4.1x (Kimi K3), and 18x
  (GLM-5.1, whose base is extremely cheap).

## Verdict

- **As a cost-efficiency statement: the hypothesis is supported for
  every model.** Enabling reasoning makes the technique strictly less
  efficient per dollar (passes/$ down 22-76%) and per second (time
  per pass up 2.1-6.0x), and its generation-phase spend (1.7-13x
  tokens) buys no reliable generation-time benefit -- for GPT-5.6 it
  is counterproductive.
- **As an absolute-benefit statement: it depends on the value of
  +16 to +21 percentage points of pass rate.** The repair benefit is
  real and large; whether it justifies 1.3-5.1x the money and 2.1-6.0x
  the time is a deployment judgment, not a measurement. If pass rate
  is the only objective and budget/time are secondary, thinking is
  defensible for DeepSeek V4 Pro, Kimi K3, GPT-5.6, and GLM-5.1; if
  cost-efficiency matters, the data says do not enable it.
- **Per model, the cleanest support for "do not use thinking"**:
  GLM-5.1 (5.1x money, 6.0x time, -76% efficiency) and Gemini 3.1 Pro
  (no benefit at all, by ceiling and by design). DeepSeek V4 Pro is
  the closest to break-even (marginal $0.07 per additional pass) and
  the only model where the generation-phase spend also buys a
  significant detection reduction.
- Design caveat: in this technique thinking applies to BOTH generation
  and repair as one switch; a repair-only reasoning mode was not
  measured and is the natural future-work question, since the
  generation-phase spend is the part with no reliable benefit.

## Threats

- Benefit measured on the vulnerable-prone 200-problem subset (where
  the base arm has headroom); on the full population the base arms
  pass 69-97% already.
- Latency is host- and network-dependent (our lanes ran via proxies
  for GPT/Claude/Gemini); token counts are exact where the ledger
  records the phase.
- Dollar figures are worst-case upper bounds (cache-miss, DeepSeek
  peak); they bound the ratio but do not change the sign of the
  efficiency drop, which is token-denominated.
