# Reasoning tokens are a subset of completion tokens

Scope: every ok ledger row under results/ (all models, all cells).
Rows with completion_tokens present are checked; rows with
reasoning_tokens present are tested against the subset claim
(reasoning_tokens <= completion_tokens).

| Ledger (model / cell dir) | ok rows checked | rows with reasoning tokens | violations |
|---|---:|---:|---:|
| `claude-fable-5` | 12,821 | 26 | 0 |
| `deepseek-v4-pro` | 19,198 | 0 | 0 |
| `deepseek-v4-pro-thinking` | 2,315 | 2,315 | 0 |
| `gemini-3-pro` | 9,502 | 8 | 0 |
| `gemini-3-pro-thinking` | 1,762 | 1 | 0 |
| `glm-5.1` | 27,318 | 0 | 0 |
| `glm-5.1-thinking` | 2,292 | 2,292 | 0 |
| `kimi-k3` | 18,773 | 0 | 0 |
| `kimi-k3-thinking` | 2,797 | 2,797 | 0 |
| `openai-gpt56-sol` | 20,070 | 19 | 0 |
| `openai-gpt56-sol-thinking` | 3,500 | 3,494 | 0 |
| `qwen-max` | 15,282 | 0 | 0 |
| **TOTAL** | **135,630** | **10,952** | **0** |

No violations: on every ledger row that reports reasoning
tokens, reasoning_tokens <= completion_tokens. Billing
completion at the output rate is therefore exact for the
reasoning-inclusive cells.

