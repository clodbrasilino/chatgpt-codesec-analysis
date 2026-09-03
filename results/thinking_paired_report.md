# Thinking vs non-thinking paired contrast (vulnerable subset, top-200)

Baseline: **deepseek-v4-pro** (reasoning disabled, `feedback-static-r0-t1.0-p1.0`, sample-1 pairing; all-samples sensitivity below). Thinking: **deepseek-v4-pro-thinking** (`feedback-static-r1-t1.0-p1.0`, 1 sample/task). Same t=1.0/p=1.0, static feedback, max_rounds = 10.
Generated: 2026-09-01/02 (pre-registered tests: mcnemar, wilcoxon_signed_rank, effect_size_r, bootstrap_ci; alpha = 0.05).

n = 199 paired problems (sample-1 pairing).

| Metric | non-thinking | thinking |
|---|---|---|
| Final clean | 98.0% | 100.0% |
| Clean at start | 57.8% | 75.9% |
| Outcome counts | {'clean_at_start': 115, 'clean': 80, 'not_cleaned': 4} | {'clean_at_start': 151, 'clean': 48} |

- **McNemar (exact)**: b = 0 (baseline clean, thinking not), c = 4 (reverse), p = 0.125
- **Wilcoxon signed-rank** on penalized rounds-to-clean (n_eff = 96): p = 1.83e-06, effect r = -0.487 (>0 = thinking needs more rounds)
- **Bootstrap 95% CI** clean-rate difference (thinking − baseline): [+0.005, +0.040]
- Sensitivity (baseline = all-3-samples-clean bar): McNemar b = 0, c = 10, p = 0.001953; bootstrap CI [+0.020, +0.085]

## Usage contrast (exact ledger)

| Metric | non-thinking | thinking |
|---|---|---|
| Calls (ok/fail) | 286/0 | 753/105 |
| Prompt tokens | 160,507 | 234,054 |
| Completion tokens | 125,315 | 4,908,910 |
| Reasoning tokens | 0 | 4,482,576 |
| Mean latency/call | 4.0s | 111.3s |

Per-problem cost multiplier (completion tokens): 14.9x; latency multiplier: 28.0x.

## Caveats

1. Baseline sample 1 and thinking sample 1 are independent generations (no shared randomness); pairing is by problem.
2. One sample per thinking cell -> noisy per-problem outcomes; interpret non-significance as inconclusive.
3. Same static gate on both cells; no gate asymmetry.
4. Thinking cell max_tokens = 16384 caps reasoning chain length; very long chains may truncate (empty-content retries are logged as failed calls).
