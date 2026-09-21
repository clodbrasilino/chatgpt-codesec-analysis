# Round-5 Data-Completeness Audit

Scope: every non-legacy cell in `collected_code_6`; a program is
**complete** if it has full analysis artifacts through round 5
(or reached its terminal state earlier).

| Model | Cell | n | complete | heal_failed | missing_healed | missing_reports | missing_fuzz | needs_beyond_cap |
|---|---|---:|---:|---:|---:|---:|---:|---:|
| claude-fable-5 | feedback-dynamic-r0-t1.0-p1.0 | 600 | 600 | 0 | 0 | 0 | 0 | 4 |
| claude-fable-5 | feedback-static+dynamic-r0-t1.0-p1.0 | 2922 | 2922 | 0 | 0 | 0 | 0 | 72 |
| claude-fable-5 | feedback-static-r0-t1.0-p1.0 | 2922 | 2922 | 0 | 0 | 0 | 0 | 67 |
| deepseek-v4-pro | feedback-dynamic-r0-t1.0-p1.0 | 600 | 600 | 0 | 0 | 0 | 0 | 1 |
| deepseek-v4-pro | feedback-static+dynamic-r0-t0.2-p1.0 | 600 | 442 | 158 | 0 | 0 | 0 | 13 |
| deepseek-v4-pro | feedback-static+dynamic-r0-t1.0-p0.5 | 600 | 600 | 0 | 0 | 0 | 0 | 22 |
| deepseek-v4-pro | feedback-static+dynamic-r0-t1.0-p1.0 | 2922 | 2922 | 0 | 0 | 0 | 0 | 103 |
| deepseek-v4-pro | feedback-static-r0-t0.2-p1.0 | 200 | 200 | 0 | 0 | 0 | 0 | 10 |
| deepseek-v4-pro | feedback-static-r0-t1.0-p0.5 | 200 | 154 | 46 | 0 | 0 | 0 | 0 |
| deepseek-v4-pro | feedback-static-r0-t1.0-p1.0 | 2922 | 2922 | 0 | 0 | 0 | 0 | 73 |
| deepseek-v4-pro-thinking | feedback-static+dynamic-r1-t1.0-p1.0 | 600 | 511 | 89 | 0 | 0 | 0 | 1 |
| deepseek-v4-pro-thinking | feedback-static-r1-t1.0-p1.0 | 600 | 600 | 0 | 0 | 0 | 0 | 21 |
| gemini-3-pro | feedback-dynamic-r0-t1.0-p1.0 | 600 | 600 | 0 | 0 | 0 | 0 | 4 |
| gemini-3-pro | feedback-static+dynamic-r0-t0.2-p1.0 | 600 | 600 | 0 | 0 | 0 | 0 | 7 |
| gemini-3-pro | feedback-static+dynamic-r0-t1.0-p0.5 | 600 | 600 | 0 | 0 | 0 | 0 | 2 |
| gemini-3-pro | feedback-static+dynamic-r0-t1.0-p1.0 | 2922 | 2920 | 0 | 0 | 0 | 2 | 24 |
| gemini-3-pro | feedback-static-r0-t1.0-p1.0 | 2922 | 2922 | 0 | 0 | 0 | 0 | 17 |
| gemini-3-pro-thinking | feedback-static+dynamic-r1-t1.0-p1.0 | 600 | 592 | 8 | 0 | 0 | 0 | 1 |
| gemini-3-pro-thinking | feedback-static-r1-t1.0-p1.0 | 600 | 600 | 0 | 0 | 0 | 0 | 3 |
| glm-5.1 | feedback-dynamic-r0-t1.0-p1.0 | 600 | 600 | 0 | 0 | 0 | 0 | 0 |
| glm-5.1 | feedback-static+dynamic-r0-t0.2-p1.0 | 600 | 600 | 0 | 0 | 0 | 0 | 21 |
| glm-5.1 | feedback-static+dynamic-r0-t1.0-p0.5 | 600 | 600 | 0 | 0 | 0 | 0 | 13 |
| glm-5.1 | feedback-static+dynamic-r0-t1.0-p1.0 | 2922 | 2922 | 0 | 0 | 0 | 0 | 134 |
| glm-5.1 | feedback-static-r0-t1.0-p1.0 | 2922 | 2922 | 0 | 0 | 0 | 0 | 118 |
| glm-5.1-thinking | feedback-static+dynamic-r1-t1.0-p1.0 | 600 | 600 | 0 | 0 | 0 | 0 | 19 |
| glm-5.1-thinking | feedback-static-r1-t1.0-p1.0 | 600 | 600 | 0 | 0 | 0 | 0 | 21 |
| kimi-k3 | feedback-dynamic-r0-t1.0-p1.0 | 600 | 599 | 0 | 0 | 1 | 0 | 2 |
| kimi-k3 | feedback-static+dynamic-r0-t1.0-p1.0 | 2922 | 2922 | 0 | 0 | 0 | 0 | 79 |
| kimi-k3 | feedback-static-r0-t1.0-p1.0 | 2922 | 2922 | 0 | 0 | 0 | 0 | 72 |
| kimi-k3-thinking | feedback-static+dynamic-r1-t1.0-p1.0 | 600 | 515 | 84 | 0 | 0 | 1 | 12 |
| kimi-k3-thinking | feedback-static-r1-t1.0-p1.0 | 600 | 600 | 0 | 0 | 0 | 0 | 19 |
| openai-gpt56-sol | feedback-dynamic-r0-t1.0-p1.0 | 600 | 597 | 3 | 0 | 0 | 0 | 0 |
| openai-gpt56-sol | feedback-static+dynamic-r0-t1.0-p1.0 | 2922 | 2922 | 0 | 0 | 0 | 0 | 118 |
| openai-gpt56-sol | feedback-static-r0-t1.0-p1.0 | 2922 | 2922 | 0 | 0 | 0 | 0 | 110 |
| openai-gpt56-sol-thinking | feedback-static+dynamic-r1-t1.0-p1.0 | 600 | 598 | 0 | 0 | 0 | 2 | 29 |
| openai-gpt56-sol-thinking | feedback-static-r1-t1.0-p1.0 | 600 | 600 | 0 | 0 | 0 | 0 | 23 |
| qwen-max | feedback-dynamic-r0-t1.0-p1.0 | 600 | 600 | 0 | 0 | 0 | 0 | 6 |
| qwen-max | feedback-none-r0-t0.5-p0.5 | 0 | 0 | 0 | 0 | 0 | 0 | 0 |
| qwen-max | feedback-static+dynamic-r0-t0.2-p1.0 | 600 | 600 | 0 | 0 | 0 | 0 | 16 |
| qwen-max | feedback-static+dynamic-r0-t1.0-p0.5 | 600 | 600 | 0 | 0 | 0 | 0 | 23 |
| qwen-max | feedback-static+dynamic-r0-t1.0-p1.0 | 2922 | 2917 | 0 | 0 | 4 | 1 | 63 |
| qwen-max | feedback-static-r0-t0.2-p1.0 | 200 | 200 | 0 | 0 | 0 | 0 | 4 |
| qwen-max | feedback-static-r0-t1.0-p0.5 | 200 | 200 | 0 | 0 | 0 | 0 | 6 |
| qwen-max | feedback-static-r0-t1.0-p1.0 | 2922 | 2922 | 0 | 0 | 0 | 0 | 57 |
| **TOTAL** | --- | **56708** | **56309** | 388 | 0 | 5 | 6 | 1410 |

## Problem cells (any non-complete programs)

### deepseek-v4-pro / feedback-static+dynamic-r0-t0.2-p1.0 — 158 incomplete of 600
- **heal_failed**: 158 — e.g. problem-102@r1, problem-102-s2@r1, problem-102-s3@r1, problem-114@r1, problem-114-s2@r1

### deepseek-v4-pro / feedback-static-r0-t1.0-p0.5 — 46 incomplete of 200
- **heal_failed**: 46 — e.g. problem-771@r4, problem-779@r4, problem-788@r4, problem-829@r4, problem-932@r4

### deepseek-v4-pro-thinking / feedback-static+dynamic-r1-t1.0-p1.0 — 89 incomplete of 600
- **heal_failed**: 89 — e.g. problem-206-s2@r3, problem-207-s2@r3, problem-217-s2@r3, problem-263-s2@r3, problem-263-s3@r3

### gemini-3-pro / feedback-static+dynamic-r0-t1.0-p1.0 — 2 incomplete of 2922
- **missing_fuzz**: 2 — e.g. problem-621@r2, problem-621-s2@r4

### gemini-3-pro-thinking / feedback-static+dynamic-r1-t1.0-p1.0 — 8 incomplete of 600
- **heal_failed**: 8 — e.g. problem-843@r2, problem-843-s2@r2, problem-469-s2@r3, problem-699-s3@r3, problem-802-s3@r5

### kimi-k3 / feedback-dynamic-r0-t1.0-p1.0 — 1 incomplete of 600
- **missing_reports**: 1 — e.g. problem-198-s3@r0.fuzz.txt

### kimi-k3-thinking / feedback-static+dynamic-r1-t1.0-p1.0 — 85 incomplete of 600
- **heal_failed**: 84 — e.g. problem-387@r1, problem-387-s2@r1, problem-391@r1, problem-391-s3@r1, problem-400@r1
- **missing_fuzz**: 1 — e.g. problem-131-s2@r2

### openai-gpt56-sol / feedback-dynamic-r0-t1.0-p1.0 — 3 incomplete of 600
- **heal_failed**: 3 — e.g. problem-127-s2@r1, problem-262-s3@r1, problem-65-s2@r1

### openai-gpt56-sol-thinking / feedback-static+dynamic-r1-t1.0-p1.0 — 2 incomplete of 600
- **missing_fuzz**: 2 — e.g. problem-131@r1, problem-131-s3@r1

### qwen-max / feedback-static+dynamic-r0-t1.0-p1.0 — 5 incomplete of 2922
- **missing_reports**: 4 — e.g. problem-450@r5:.test.txt,.fuzz.txt, problem-450-s2@r5:.test.txt,.fuzz.txt, problem-500@r3:.test.txt,.fuzz.txt, problem-500-s2@r3:.test.txt,.fuzz.txt
- **missing_fuzz**: 1 — e.g. problem-699@r3

