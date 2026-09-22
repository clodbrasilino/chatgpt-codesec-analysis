# Gate-usage ablation (P4): static-only vs dynamic-only vs full gate

Non-thinking arms, 200-problem vulnerable-prone subset, 3 samples
per problem, five-round horizon with a COMMON censor on both arms
(primary; as-recorded sensitivity at the end). Dynamic-only cells
import the round-0 code of the static-only cells (gen_source), so
comparison A holds the code fixed and varies only the feedback
channel; comparison B pairs problems across independently
generated arms.

## Primary (common 5-round censor)

### A. static-only vs dynamic-only (same round-0 code)

| Model | pass static-only → dynamic-only | Δ | 95% CI | McNemar x/y | p |
|---|---|---:|---|---|---|
| DeepSeek V4 Pro | 77.0% → 95.2% | +18.2pp | [+13.2, +23.2] | 3/40 | 3.02e-09 |
| GPT-5.6 | 73.5% → 99.5% | +26.0pp | [+20.8, +31.2] | 0/51 | 8.88e-16 |
| Gemini 3.1 Pro | 99.2% → 98.2% | -1.0pp | [-3.0, +0.7] | 4/0 | 0.125 |
| Kimi K3 | 70.0% → 95.5% | +25.5pp | [+19.8, +31.2] | 4/51 | 2.05e-11 |
| GLM-5.1 | 81.2% → 96.5% | +15.3pp | [+10.7, +20.2] | 5/33 | 4.26e-06 |
| Qwen Max | 83.8% → 94.7% | +10.8pp | [+6.5, +15.3] | 5/27 | 0.000113 |
| Claude Fable 5 | 82.0% → 97.0% | +15.0pp | [+10.2, +20.0] | 6/36 | 2.83e-06 |

### B. static-only vs full gate (independent generations)

| Model | pass static-only → full gate | Δ | 95% CI | McNemar x/y | p |
|---|---|---:|---|---|---|
| DeepSeek V4 Pro | 85.4% → 82.9% | -2.6pp | [-4.5, -0.7] | 55/30 | 0.00884 |
| GPT-5.6 | 78.9% → 78.2% | -0.6pp | [-2.5, +1.2] | 45/39 | 0.586 |
| Gemini 3.1 Pro | 99.7% → 98.0% | -1.6pp | [-2.6, -0.8] | 18/2 | 0.000402 |
| Kimi K3 | 83.0% → 81.7% | -1.2pp | [-3.1, +0.6] | 47/35 | 0.224 |
| GLM-5.1 | 88.8% → 86.9% | -2.0pp | [-3.8, -0.2] | 50/31 | 0.0448 |
| Qwen Max | 92.8% → 88.7% | -4.1pp | [-5.7, -2.6] | 53/13 | 7.24e-07 |
| Claude Fable 5 | 89.4% → 87.8% | -1.6pp | [-3.2, -0.1] | 38/22 | 0.0519 |

### C. dynamic-only vs full gate (independent generations)

| Model | pass dynamic-only → full gate | Δ | 95% CI | McNemar x/y | p |
|---|---|---:|---|---|---|
| DeepSeek V4 Pro | 95.5% → 74.5% | -21.0pp | [-26.5, -15.5] | 42/0 | 4.55e-13 |
| GPT-5.6 | 100.0% → 75.0% | -25.0pp | [-31.0, -19.0] | 50/0 | 1.78e-15 |
| Gemini 3.1 Pro | 98.0% → 97.0% | -1.0pp | [-2.5, +0.0] | 2/0 | 0.5 |
| Kimi K3 | 96.0% → 74.0% | -22.0pp | [-28.0, -16.5] | 45/1 | 1.34e-12 |
| GLM-5.1 | 96.0% → 80.5% | -15.5pp | [-20.5, -10.5] | 31/0 | 9.31e-10 |
| Qwen Max | 96.5% → 81.5% | -15.0pp | [-20.0, -10.0] | 31/1 | 1.54e-08 |
| Claude Fable 5 | 97.0% → 79.0% | -18.0pp | [-23.5, -13.0] | 36/0 | 2.91e-11 |

x = first arm passes / second does not; y = reverse.

## Sensitivity (as-recorded outcomes)

### A. static-only vs dynamic-only (same round-0 code)

| Model | pass static-only → dynamic-only | Δ | 95% CI | McNemar x/y | p |
|---|---|---:|---|---|---|
| DeepSeek V4 Pro | 80.3% → 95.3% | +15.0pp | [+10.5, +19.7] | 4/31 | 3.47e-06 |
| GPT-5.6 | 77.8% → 99.5% | +21.7pp | [+17.2, +26.5] | 0/39 | 3.64e-12 |
| Gemini 3.1 Pro | 100.0% → 98.8% | -1.2pp | [-2.5, -0.2] | 2/0 | 0.5 |
| Kimi K3 | 72.7% → 95.8% | +23.2pp | [+17.8, +28.5] | 4/45 | 8.23e-10 |
| GLM-5.1 | 84.0% → 96.5% | +12.5pp | [+7.8, +17.2] | 7/28 | 0.000508 |
| Qwen Max | 87.8% → 95.7% | +7.8pp | [+4.0, +11.8] | 5/18 | 0.0106 |
| Claude Fable 5 | 86.7% → 97.7% | +11.0pp | [+6.7, +15.5] | 5/26 | 0.000192 |

### B. static-only vs full gate (independent generations)

| Model | pass static-only → full gate | Δ | 95% CI | McNemar x/y | p |
|---|---|---:|---|---|---|
| DeepSeek V4 Pro | 88.4% → 86.1% | -2.3pp | [-4.1, -0.4] | 54/32 | 0.023 |
| GPT-5.6 | 82.9% → 82.8% | -0.1pp | [-2.1, +1.8] | 48/47 | 1 |
| Gemini 3.1 Pro | 99.9% → 98.6% | -1.3pp | [-2.1, -0.7] | 13/0 | 0.000244 |
| Kimi K3 | 85.6% → 84.7% | -0.9pp | [-2.7, +0.7] | 40/31 | 0.342 |
| GLM-5.1 | 92.4% → 90.9% | -1.5pp | [-3.0, -0.1] | 32/17 | 0.0444 |
| Qwen Max | 94.4% → 90.5% | -3.9pp | [-5.4, -2.4] | 49/11 | 7.56e-07 |
| Claude Fable 5 | 92.4% → 91.0% | -1.4pp | [-2.9, -0.1] | 30/16 | 0.0541 |

### C. dynamic-only vs full gate (independent generations)

| Model | pass dynamic-only → full gate | Δ | 95% CI | McNemar x/y | p |
|---|---|---:|---|---|---|
| DeepSeek V4 Pro | 95.5% → 79.5% | -16.0pp | [-21.5, -11.0] | 32/0 | 4.66e-10 |
| GPT-5.6 | 100.0% → 81.0% | -19.0pp | [-24.5, -14.0] | 38/0 | 7.28e-12 |
| Gemini 3.1 Pro | 99.0% → 98.0% | -1.0pp | [-2.5, +0.0] | 2/0 | 0.5 |
| Kimi K3 | 96.0% → 76.0% | -20.0pp | [-26.0, -14.5] | 41/1 | 1.96e-11 |
| GLM-5.1 | 96.0% → 83.0% | -13.0pp | [-18.0, -8.5] | 26/0 | 2.98e-08 |
| Qwen Max | 96.5% → 85.5% | -11.0pp | [-15.5, -6.5] | 23/1 | 2.98e-06 |
| Claude Fable 5 | 97.5% → 83.5% | -14.0pp | [-19.0, -9.5] | 28/0 | 7.45e-09 |

x = first arm passes / second does not; y = reverse.


## Interpretation (criterion caveat is essential)

Each arm's "pass" is its own gate's termination criterion, so the bars
differ across arms: dynamic-only pass requires no dynamic finding,
static-only pass requires no static finding, and full-gate pass
requires both. Cross-arm differences therefore mix (i) feedback
effectiveness and (ii) criterion strictness, and comparisons B and C
additionally involve independently generated round-0 code.

- **A (same round-0 code, feedback channel varied)** is the controlled
  contrast: with identical starting code, dynamic feedback drives
  repair to its own criterion far more often than static feedback
  (+10.8 to +26.0pp in 6 of 7 models, all p <= 1e-4; Gemini saturated
  at ~99%). Under static-only feedback, 15-30% of problems remain
  unrepaired at the horizon even though the same code is repairable
  under dynamic feedback.
- **B and C are criterion-confounded**: the full gate is strictly
  harder to satisfy (must clear static AND dynamic findings), so its
  lower pass rate vs dynamic-only (C) does not mean worse repair.
  A common-criterion comparison would require evaluating the missing
  channel on each arm's final code (cheap for static on the
  dynamic-only arm; heavier for dynamic on the static-only arm).
- The B result that the full gate does not beat static-only (and is
  significantly lower for Qwen, DeepSeek, Gemini, GLM) is consistent
  with the RQ2 false-positive-tension finding: static findings
  (largely quality/lexical) keep the loop from terminating, and the
  full gate's stricter criterion costs pass rate.
- Scope: 200-problem vulnerable-prone subset, non-thinking, 3
  samples/problem; Gemini near ceiling throughout.
