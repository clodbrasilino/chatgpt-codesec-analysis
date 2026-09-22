# Tokens per problem: thinking vs non-thinking (histogram analysis)

Unit = problem; total tokens = generation + repair, summed over
the problem's 3 samples. Pooled over the 5 toggle-verified models
on the 200-problem subset (n = 1,000 problems per arm).
Thinking arm: EXACT (ledgers record generation + repair calls).
Non-thinking arm: repair exact; generation estimated from the raw
generation outputs (~3.6 chars/token). Figure:
results/thinking_tokens_hist.pdf.

## Distribution summary

- Non-thinking: mean 19,196; std 25,023; median 6,464; q25 2,758; q75 27,968; max 149,383
- Thinking:     mean 36,076; std 72,192; median 17,027; q25 7,920; q75 40,820; max 1,025,103
- Thinking median is 2.63x the
  non-thinking median; means 1.88x.

## Per-model medians (tokens/problem) and passes

| Model | non-thinking median | thinking median | ratio | pass nt -> th |
|---|---:|---:|---:|---|
| DeepSeek V4 Pro | 9,962 | 31,119 | 3.1x | 439 -> 541 (+102) |
| GPT-5.6 | 6,346 | 17,316 | 2.7x | 437 -> 536 (+99) |
| Kimi K3 | 12,335 | 21,893 | 1.8x | 416 -> 542 (+126) |
| GLM-5.1 | 6,240 | 19,042 | 3.1x | 467 -> 563 (+96) |
| Gemini 3.1 Pro | 4,304 | 4,433 | 1.0x | 572 -> 578 (+6) |

## Reading

- Both distributions are heavy right-tailed: most problems cost
  little; a tail of never-repaired problems absorbs the budget.
- Thinking shifts the WHOLE distribution right: median 2.6x,
  p75 1.5x, p90 1.3x, p99 3.6x -- and STRETCHES the upper tail:
  53 problems exceed 100k tokens
 (vs 15 non-thinking); the worst case
  reaches 1.03M tokens (a GLM-5.1 reasoning loop). Thinking
  buys passes but also multiplies the cost of the problems it
  still fails on.
- Totals: 36,076,199 vs 19,196,120 tokens
 (1.88x) for +429 passed programs of 3,000
 (+7.6pp pooled): ~39,348 tokens per additional passed
  program.
- Per model, the generation phase multiplies tokens by 1.7x
  (Gemini) to 13x (DeepSeek) under thinking, while mean repair
  tokens per problem FALL (fewer unresolved churners).
