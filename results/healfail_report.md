# heal_failed detail — five-round analysis window

Every `heal_failed` program in every non-legacy cell, broken down
by the round at which the failure occurred. Failures in rounds 1-5
fall inside the reporting horizon and therefore compromise the
five-round analysis of that cell; failures beyond round 5 do not.

| Model | Cell | Class | n | failed (all) | failed in r1-5 | r1 | r2 | r3 | r4 | r5 | failed r>5 |
|---|---|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| deepseek-v4-pro | `feedback-static+dynamic-r0-t0.2-p1.0` | ablation: sampling grid, grid (t=0.2) | 600 | 158 | **158** | 158 | 0 | 0 | 0 | 0 | 0 |
| deepseek-v4-pro-thinking | `feedback-static+dynamic-r1-t1.0-p1.0` | ablation: extended-reasoning (thinking) — gate static+dynamic | 600 | 89 | **88** | 0 | 0 | 19 | 69 | 0 | 1 |
| kimi-k3-thinking | `feedback-static+dynamic-r1-t1.0-p1.0` | ablation: extended-reasoning (thinking) — gate static+dynamic | 600 | 84 | **84** | 84 | 0 | 0 | 0 | 0 | 0 |
| deepseek-v4-pro | `feedback-static-r0-t1.0-p0.5` | ablation: static only feedback | 200 | 46 | **46** | 0 | 0 | 0 | 9 | 37 | 0 |
| gemini-3-pro-thinking | `feedback-static+dynamic-r1-t1.0-p1.0` | ablation: extended-reasoning (thinking) — gate static+dynamic | 600 | 8 | **5** | 0 | 2 | 2 | 0 | 1 | 3 |
| openai-gpt56-sol | `feedback-dynamic-r0-t1.0-p1.0` | ablation: dynamic only feedback | 600 | 3 | **3** | 3 | 0 | 0 | 0 | 0 | 0 |
| **TOTAL** | --- | --- | --- | **388** | **384** | 245 | 2 | 21 | 78 | 38 | 4 |

## Cells with no failures inside the window

Every cell not listed above has zero `heal_failed` programs in rounds 1-5; in particular all seven main (static+dynamic, full-task) cells are clean inside the window except where listed.
