# Channel and sub-channel contribution (five-round horizon)

Programs (model x problem) with at least one finding of the
sub-channel on any version from round 0 to round 5. Main cells,
full gate, non-thinking. Aggregate = unique (model, program) pairs,
20454 programs in total.

## Per model

| Model | programs | STATIC any | gcc | clang | cppcheck | flawfinder | DYN any | tests | oracle | ASan | UBSan | fuzzer | any channel |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| claude-fable-5 | 2922 | 1127 | 24 | 28 | 622 | 736 | 198 | 139 | 0 | 1 | 59 | 67 | 1325 |
| openai-gpt56-sol | 2922 | 1464 | 316 | 381 | 808 | 1046 | 104 | 83 | 1 | 1 | 18 | 20 | 1568 |
| gemini-3-pro | 2922 | 1014 | 17 | 39 | 638 | 489 | 201 | 121 | 1 | 2 | 76 | 95 | 1215 |
| kimi-k3 | 2922 | 1379 | 75 | 96 | 742 | 910 | 354 | 229 | 1 | 4 | 101 | 143 | 1733 |
| deepseek-v4-pro | 2922 | 1564 | 100 | 135 | 1177 | 704 | 402 | 249 | 9 | 16 | 141 | 171 | 1966 |
| qwen-max | 2922 | 1476 | 246 | 246 | 1131 | 446 | 431 | 240 | 19 | 19 | 171 | 229 | 1907 |
| glm-5.1 | 2922 | 1840 | 241 | 285 | 1497 | 854 | 347 | 306 | 3 | 3 | 38 | 43 | 2187 |
| **Aggregate** | 20454 | 9864 | 1019 | 1210 | 6615 | 5185 | 2037 | 1367 | 34 | 46 | 604 | 768 | 10620 |

Fuzzer split (aggregate): attributed findings 597, signal-only crashes 347 (a program may appear in both).

Notes: a program counts for a sub-channel if that sub-channel produced at least one injectable finding on any version within rounds 0-5; the oracle split (ASan/UBSan) is by report prefix; fuzzer findings include replay-attributed sanitizer reports and signal-only crashes.
