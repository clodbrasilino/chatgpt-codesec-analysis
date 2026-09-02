# Thinking vs non-thinking paired contrast (vulnerable subset, top-200)

Baseline: **deepseek-v4-pro** (reasoning disabled, `feedback-static-r0-t1.0-p1.0`, sample-1 pairing; all-samples sensitivity below). Thinking: **deepseek-v4-pro-thinking** (`feedback-static-r1-t1.0-p1.0`, 1 sample/task). Same t=1.0/p=1.0, static feedback, max_rounds = 10.
Generated: 2026-09-01/02 (pre-registered tests: mcnemar, wilcoxon_signed_rank, effect_size_r, bootstrap_ci; alpha = 0.05).

n = 1 paired problems (sample-1 pairing).

| Metric | non-thinking | thinking |
|---|---|---|
| Final clean | 100.0% | 100.0% |
| Clean at start | 100.0% | 100.0% |
| Outcome counts | {'clean_at_start': 1} | {'clean_at_start': 1} |

- **McNemar (exact)**: b = 0 (baseline clean, thinking not), c = 0 (reverse), p = 1
- **Wilcoxon signed-rank** on penalized rounds-to-clean (n_eff = 0): p = nan, effect r = +nan (>0 = thinking needs more rounds)
- **Bootstrap 95% CI** clean-rate difference (thinking − baseline): [+0.000, +0.000]
- Sensitivity (baseline = all-3-samples-clean bar): McNemar b = 0, c = 0, p = 1; bootstrap CI [+0.000, +0.000]

## Usage contrast (exact ledger)

| Metric | non-thinking | thinking |
|---|---|---|
| Calls (ok/fail) | 286/0 | 1/0 |
| Prompt tokens | 160,507 | 183 |
| Completion tokens | 125,315 | 8,668 |
| Reasoning tokens | 0 | 8,043 |
| Mean latency/call | 4.0s | 111.4s |

Per-problem cost multiplier (completion tokens): 19.8x; latency multiplier: 28.0x.

## Caveats

1. Baseline sample 1 and thinking sample 1 are independent generations (no shared randomness); pairing is by problem.
2. One sample per thinking cell -> noisy per-problem outcomes; interpret non-significance as inconclusive.
3. Same static gate on both cells; no gate asymmetry.
4. Thinking cell max_tokens = 16384 caps reasoning chain length; very long chains may truncate (empty-content retries are logged as failed calls).
