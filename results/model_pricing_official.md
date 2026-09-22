# Official API pricing for the models used (collected 2026-09-22)

All prices per 1M tokens, from the providers' official pricing pages.
USD where the provider prices in dollars; CNY for the Chinese models
(DeepSeek publishes both; Kimi/Qwen/GLM are CNY-native). Sources and
verification dates noted per row.

## Summary table

| Model (registry id) | Provider / endpoint used | Input (cache miss) | Input (cache hit) | Output (incl. thinking) | Currency | Official source |
|---|---|---:|---:|---:|---|---|
| deepseek-v4-pro | DeepSeek official API (also routed via DashScope) | $0.66 off-peak / $1.32 peak | $0.022 / $0.044 | $1.98 / $3.96 | USD (CNY page: ¥4.5/¥9 miss, ¥13.5/¥27 out off/peak) | api-docs.deepseek.com/quick_start/pricing (verified 2026-09-18) |
| openai-gpt56-sol | OpenAI official API | $5.00 | $0.50 | $30.00 | USD | openai.com/api/pricing; developers.openai.com/api/docs/pricing (2026-09-22) |
| gemini-3-pro (registry: gemini-3.1-pro-preview) | Google Gemini API (preview) | $2.00 (prompts ≤200k) | $0.20 (+$4.50/M-tok/h storage) | $12.00 (thinking included) | USD | ai.google.dev/gemini-api/docs/pricing; blog.google (2026-09-22) |
| kimi-k3 | Moonshot AI (routed via DashScope) | ¥20 | ¥2 | ¥100 | CNY (press USD equiv: $3.00 / $15.00) | Moonshot K3 pricing page (2026-09-22, via official announcements) |
| glm-5.1 | Zhipu BigModel (routed via DashScope) | ¥6 (input <32K) / ¥8 (≥32K) | ¥1.3 / ¥2 | ¥24 (<32K) / ¥28 (≥32K) | CNY | docs.bigmodel.cn/cn/guide/start/pricing; open.bigmodel.cn/pricing (2026-09-22) |
| qwen-max | Alibaba Cloud Bailian / DashScope (China mainland) | ¥2.4 | ¥0.48 | ¥9.6 | CNY | help.aliyun.com/zh/model-studio/qwen-max (2026-09-22) |
| claude-fable-5 | Anthropic official API | $10.00 | $1.00 (cache read; 5m cache write $12.50) | $50.00 | USD | docs.anthropic.com/en/docs/about-claude/pricing; anthropic.com/api (2026-09-22) |

## Per-provider notes needed for the cost calculation

1. **Output price includes thinking/reasoning tokens** for all seven
   (DeepSeek states output "including thinking tokens"; Gemini output
   "包括思考 token"; Anthropic/OpenAI bill reasoning as output). Our
   ledgers record `reasoning_tokens` separately, but they bill as
   output -- add them to completion for costing.
2. **Cache tiers**: DeepSeek, OpenAI, Gemini, Anthropic, Kimi, Qwen,
   GLM all have cheaper cache-hit input. Our usage ledgers do NOT
   record cached vs uncached prompt tokens, so a conservative
   calculation bills all input at the cache-miss rate. If a provider
   reports high cache hit rates (e.g., Moonshot claims >90% in coding
   workloads), the true bill is lower -- state the assumption.
3. **DeepSeek peak/off-peak**: peak = 01:00-04:00 and 06:00-10:00 UTC
   Mon-Fri (= 09:00-12:00 and 14:00-18:00 Beijing), peak = 2x off-peak.
   Our runs executed during Beijing daytime -> peak rates likely apply
   for parts of the run; compute both bounds.
4. **GLM-5.1 tiering**: input <32K tokens bills at ¥6/¥24 (in/out);
   >=32K at ¥8/¥28. Our repair prompts are short (hundreds of tokens)
   -> the <32K tier applies.
5. **Gemini 3.1 Pro is a preview** priced for prompts <=200k tokens
   (our prompts are far below); output price includes thinking.
6. **Routing caveat (actual bill vs official price)**: the experiment
   routed DeepSeek, Kimi, GLM, and Qwen through Alibaba DashScope.
   DashScope's billed rates for these models can differ from the
   vendors' first-party prices above. For the dollar conversion,
   decide per model: (a) vendor official price (comparable across
   models) or (b) DashScope billed price (what we actually paid).
7. **Currency conversion**: CNY rows (Kimi, GLM, Qwen; DeepSeek CNY
   page) to be converted at the user-chosen rate.

## Raw notes

- DeepSeek V4 Pro (api-docs.deepseek.com, English page, USD):
  cache-hit input $0.022 off-peak / $0.044 peak; cache-miss input
  $0.66 / $1.32; output $1.98 / $3.96. Chinese page (CNY): off-peak
  miss ¥4.5, output ¥13.5, cache hit ¥0.15; peak 2x. Note: DeepSeek
  announced V4 Pro API continues after 2026-09-14 with billing
  unchanged.
- OpenAI GPT-5.6 Sol: input $5.00, cached $0.50, output $30.00
  (standard, <270K context). Batch -50%; data-residency +10%.
- Gemini 3.1 Pro preview: input $2.00 (<=200k), output $12.00
  (thinking included), context cache $0.20 + $4.50/M-tok/h; batch
  $1.00/$6.00. Vertex lists identical rates ($2/$12 standard).
- Claude Fable 5: standard $10 in / $50 out; cache write $12.50 (5m),
  cache read $1; batch $5/$25. (Anthropic rate card effective
  2026-06-29.)
- Kimi K3 (Moonshot): ¥2 cache hit / ¥20 miss / ¥100 output (CNY);
  USD equivalents quoted in press coverage: $0.30 / $3.00 / $15.00.
- GLM-5.1 (Zhipu BigModel): tiered, <32K: ¥6 in / ¥24 out; >=32K: ¥8
  in / ¥28 out; cache hit ¥1.3 (<32K). Z.ai international USD list:
  $1.40 in / $4.40 out / $0.26 cache.
- Qwen Max (Alibaba, China mainland): ¥2.4 in / ¥9.6 out / ¥0.48
  cache hit (non-thinking mode; thinking mode output price equals
  non-thinking per Alibaba docs). International deployment list:
  ¥11.743 in / ¥46.971 out.
