# RQ3 focus report: thinking vs non-thinking under the full gate
(static+dynamic), pending final data

Scope. Full-gate cells only (`feedback-static+dynamic`), 200-task
vulnerable-prone subset (top-200 of `results/vulnerable_subset.csv`),
3 samples per task on BOTH arms, t=1.0/p=1.0, horizon = 5 rounds
(config-driven), detection = analysis gate (static analyzers, tests,
sanitizer oracle, AFL++). Non-thinking arm = base main cells
(`...-r0-...`, reasoning off); thinking arm = `...-thinking` cells
(`...-r1-...`, reasoning on). Primary pairing: sample-1 vs sample-1
(pre-registered); sensitivity: all-3-samples bar on both sides.

Exclusions for this report:
- **Gemini 3.1 Pro** — saturated: the base arm passes 97.0% of the
  subset within the horizon (100.0% under the static-only gate), so
  there is no headroom to measure a thinking effect; excluded per
  analyst decision (2026-09-22).
- **DeepSeek V4 Pro, Kimi K3** — full-gate thinking cells currently
  fail the pre-registered validity gate (89 and 84 heal_failed,
  transient provider failures); retry repair launched 2026-09-22
  (resume-cached). To be added when repaired; pooled numbers below
  will be refreshed.

## Per-model repair performance (valid models)

| Model | Pass @horizon base → thinking | Δ | McNemar (b/c) | p | Wilcoxon (penalized rounds) | effect r | 95% CI (diff) |
|---|---|---:|---|---:|---|---:|---|
| GPT-5.6 | 77.8% → 94.2% | +16.4pp | 9/45 | 7.3e-07 | p = 0.0016 | −0.286 | [+0.115, +0.250] |
| GLM-5.1 | 81.3% → 97.0% | +15.7pp | 3/33 | 2.3e-07 | p = 0.0014 | −0.291 | [+0.095, +0.205] |

- b = base passes, thinking does not; c = thinking passes, base does
  not. Discordance is 5-11x in the direction of thinking.
- Negative effect r = the thinking arm reaches a pass in FEWER
  penalized rounds-to-clean on the same problems (Wilcoxon signed-rank
  over all 200 paired problems; penalty = 6 for never-passed).

## Pooled across the two valid models

Discordant pairs pooled (post-hoc, reported alongside per-model tests;
refresh after DeepSeek/Kimi repair):

- Sample-1 pairing: b = 12, c = 78, exact binomial **p = 5.2e-13**.
- All-3-samples sensitivity: b = 16, c = 113, exact binomial
  **p = 3.6e-19**.

## Generation-time contrast (context)

Detection-free at generation moves only modestly and in mixed
directions (GPT 49.3% → 42.7%; GLM 39.3% → 47.3%). The thinking effect
under the full gate is concentrated in **repair**, not in producing
detection-free code on the first attempt.

## Cost context (exact ledgers, subset-restricted)

Thinking costs 2.6-6.1x completion tokens (reasoning-dominated) and
4.3-14.4x latency per call across the two models (GPT 2.6x / 4.3x;
GLM 6.1x / 14.4x for tokens/latency respectively; full-gate cells).
Gemini's reasoning tokens are unmetered by the provider, so its cost
contrast would rest on latency only.

## Verdict

Yes — repair performance differs significantly between the
non-thinking and thinking arms under the full gate for both currently
valid models, in the same direction and with overlapping effect sizes
(moderate, |r| ~ 0.29): thinking adds ~16pp of pass rate within the
five-round horizon and reaches passes in fewer penalized rounds, at a
multi-x token and latency cost. Pooled discordance is decisive
(p = 5e-13). Final paper numbers wait for the DeepSeek/Kimi cell
repair; Gemini stays excluded (saturation), and the static-only
contrast is deferred to the gate-usage ablation.

## Caveats

1. Sample-1 pairing is primary (pre-registered); the all-3-samples
   sensitivity is concordant and stronger.
2. Conditional-on-pass round means are selection-biased (thinking
   passes harder problems) and are deliberately not compared; the
   penalized Wilcoxon over all paired problems is the rounds statistic.
3. The subset is the vulnerable-prone top-200 — base pass rates are
   lower here than on the full 974-task population by construction.
4. Thinking cells record max_rounds = 10 but are truncated to the
   configured 5-round horizon at report time, identically to the base
   cells.
