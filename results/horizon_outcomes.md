# Outcomes at the 5-round analysis horizon

Programs are classified as: detection-free at generation; repaired within 5 rounds; or not detection-free at the horizon (clean only after round 5, still flagged, or failed repair).

## Main cells (RQ1) — full gate, all 974 tasks, 3 samples

| Model | n | detection-free at generation | repaired $\le 5$ | not detection-free at horizon | rate at horizon |
|---|---:|---:|---:|---:|---:|
| claude-fable-5 | 2922 | 1708 | 839 | 375 | 87.2\% |
| openai-gpt56-sol | 2922 | 1436 | 803 | 683 | 76.6\% |
| gemini-3-pro | 2922 | 1812 | 1030 | 80 | 97.3\% |
| kimi-k3 | 2922 | 1382 | 895 | 645 | 77.9\% |
| deepseek-v4-pro | 2922 | 1192 | 1138 | 592 | 79.7\% |
| qwen-max | 2922 | 1284 | 1230 | 408 | 86.0\% |
| glm-5.1 | 2922 | 1020 | 1426 | 476 | 83.7\% |

Rounds used by the repaired programs (main cells):

| Model | r1 | r2 | r3 | r4 | r5 |
|---|---:|---:|---:|---:|---:|
| claude-fable-5 | 605 | 92 | 64 | 43 | 35 |
| openai-gpt56-sol | 305 | 288 | 88 | 69 | 53 |
| gemini-3-pro | 796 | 146 | 48 | 28 | 12 |
| kimi-k3 | 597 | 143 | 75 | 43 | 37 |
| deepseek-v4-pro | 808 | 209 | 54 | 46 | 21 |
| qwen-max | 882 | 188 | 98 | 35 | 27 |
| glm-5.1 | 623 | 419 | 206 | 111 | 67 |

## All other cells

| Model | Cell | n | gen | repaired $\le 5$ | beyond 5 | still flagged | failed | rate at horizon |
|---|---|---:|---:|---:|---:|---:|---:|---:|
| claude-fable-5 | `feedback-dynamic-r0-t1.0-p1.0` | 600 | 570 | 12 | 4 | 14 | 0 | 97.0\% |
| claude-fable-5 | `feedback-static-r0-t1.0-p1.0` | 2922 | 1812 | 783 | 67 | 260 | 0 | 88.8\% |
| deepseek-v4-pro | `feedback-dynamic-r0-t1.0-p1.0` | 600 | 555 | 16 | 1 | 28 | 0 | 95.2\% |
| deepseek-v4-pro | `feedback-static+dynamic-r0-t0.2-p1.0` | 600 | 216 | 156 | 13 | 57 | 158 | 62.0\% |
| deepseek-v4-pro | `feedback-static+dynamic-r0-t1.0-p0.5` | 600 | 225 | 217 | 22 | 136 | 0 | 73.7\% |
| deepseek-v4-pro | `feedback-static-r0-t0.2-p1.0` | 200 | 82 | 64 | 10 | 44 | 0 | 73.0\% |
| deepseek-v4-pro | `feedback-static-r0-t1.0-p0.5` | 200 | 75 | 77 | 0 | 2 | 46 | 76.0\% |
| deepseek-v4-pro | `feedback-static-r0-t1.0-p1.0` | 2922 | 1404 | 1031 | 73 | 414 | 0 | 83.3\% |
| deepseek-v4-pro-thinking | `feedback-static+dynamic-r1-t1.0-p1.0` | 600 | 295 | 212 | 1 | 3 | 89 | 84.5\% |
| deepseek-v4-pro-thinking | `feedback-static-r1-t1.0-p1.0` | 600 | 303 | 259 | 21 | 17 | 0 | 93.7\% |
| gemini-3-pro | `feedback-dynamic-r0-t1.0-p1.0` | 600 | 559 | 30 | 4 | 7 | 0 | 98.2\% |
| gemini-3-pro | `feedback-static+dynamic-r0-t0.2-p1.0` | 600 | 312 | 270 | 7 | 11 | 0 | 97.0\% |
| gemini-3-pro | `feedback-static+dynamic-r0-t1.0-p0.5` | 600 | 311 | 277 | 2 | 10 | 0 | 98.0\% |
| gemini-3-pro | `feedback-static-r0-t1.0-p1.0` | 2922 | 1937 | 960 | 17 | 8 | 0 | 99.1\% |
| gemini-3-pro-thinking | `feedback-static+dynamic-r1-t1.0-p1.0` | 600 | 314 | 264 | 1 | 13 | 8 | 96.3\% |
| gemini-3-pro-thinking | `feedback-static-r1-t1.0-p1.0` | 600 | 323 | 268 | 3 | 6 | 0 | 98.5\% |
| glm-5.1 | `feedback-dynamic-r0-t1.0-p1.0` | 600 | 561 | 18 | 0 | 21 | 0 | 96.5\% |
| glm-5.1 | `feedback-static+dynamic-r0-t0.2-p1.0` | 600 | 254 | 217 | 21 | 108 | 0 | 78.5\% |
| glm-5.1 | `feedback-static+dynamic-r0-t1.0-p0.5` | 600 | 259 | 223 | 13 | 105 | 0 | 80.3\% |
| glm-5.1 | `feedback-static-r0-t1.0-p1.0` | 2922 | 1097 | 1409 | 118 | 298 | 0 | 85.8\% |
| glm-5.1-thinking | `feedback-static+dynamic-r1-t1.0-p1.0` | 600 | 284 | 279 | 19 | 18 | 0 | 93.8\% |
| glm-5.1-thinking | `feedback-static-r1-t1.0-p1.0` | 600 | 289 | 281 | 21 | 9 | 0 | 95.0\% |
| kimi-k3 | `feedback-dynamic-r0-t1.0-p1.0` | 600 | 554 | 19 | 2 | 25 | 0 | 95.5\% |
| kimi-k3 | `feedback-static-r0-t1.0-p1.0` | 2922 | 1565 | 781 | 72 | 504 | 0 | 80.3\% |
| kimi-k3-thinking | `feedback-static+dynamic-r1-t1.0-p1.0` | 600 | 238 | 247 | 12 | 19 | 84 | 80.8\% |
| kimi-k3-thinking | `feedback-static-r1-t1.0-p1.0` | 600 | 251 | 306 | 19 | 24 | 0 | 92.8\% |
| openai-gpt56-sol | `feedback-dynamic-r0-t1.0-p1.0` | 600 | 583 | 14 | 0 | 0 | 3 | 99.5\% |
| openai-gpt56-sol | `feedback-static-r0-t1.0-p1.0` | 2922 | 1461 | 807 | 110 | 544 | 0 | 77.6\% |
| openai-gpt56-sol-thinking | `feedback-static+dynamic-r1-t1.0-p1.0` | 600 | 256 | 280 | 29 | 35 | 0 | 89.3\% |
| openai-gpt56-sol-thinking | `feedback-static-r1-t1.0-p1.0` | 600 | 256 | 287 | 23 | 34 | 0 | 90.5\% |
| qwen-max | `feedback-dynamic-r0-t1.0-p1.0` | 600 | 517 | 51 | 6 | 26 | 0 | 94.7\% |
| qwen-max | `feedback-static+dynamic-r0-t0.2-p1.0` | 600 | 258 | 231 | 16 | 95 | 0 | 81.5\% |
| qwen-max | `feedback-static+dynamic-r0-t1.0-p0.5` | 600 | 277 | 205 | 23 | 95 | 0 | 80.3\% |
| qwen-max | `feedback-static-r0-t0.2-p1.0` | 200 | 99 | 81 | 4 | 16 | 0 | 90.0\% |
| qwen-max | `feedback-static-r0-t1.0-p0.5` | 200 | 112 | 63 | 6 | 19 | 0 | 87.5\% |
| qwen-max | `feedback-static-r0-t1.0-p1.0` | 2922 | 1527 | 1126 | 57 | 212 | 0 | 90.8\% |
