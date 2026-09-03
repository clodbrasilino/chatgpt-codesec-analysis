# Token / time usage per experiment cell

Generated: 2026-09-01. Exact ledger active from 2026-09-01 onward
(results/{model}/{cell}.usage.jsonl — one record per API call:
tokens, reasoning tokens, latency). Rounds that ran before the ledger
existed are ESTIMATED from disk at ~3.6 chars/token; treat those as
order-of-magnitude figures. `mixed` cells show both.

| model | cell | source | calls (exact+est) | prompt tok | completion tok | total (approx) | mean latency s | failed |
|---|---|---|---|---|---|---|---|---|
| deepseek-v4-pro | feedback-dynamic-r0-t1.0-p1.0 | estimated | 0+600 | 76,551 | 397,517 | 474,068 | — | 0 |
| deepseek-v4-pro | feedback-static+dynamic-r0-t0.2-p1.0 | mixed | 1112+200 | 679,145 | 902,112 | 1,581,257 | 8.994 | 0 |
| deepseek-v4-pro | feedback-static+dynamic-r0-t1.0-p0.5 | mixed | 1056+200 | 597,157 | 829,639 | 1,426,796 | 6.265 | 0 |
| deepseek-v4-pro | feedback-static+dynamic-r0-t1.0-p1.0 | mixed | 648+600 | 605,281 | 843,827 | 1,449,108 | 6.232 | 0 |
| deepseek-v4-pro | feedback-static-r0-t0.2-p1.0 | mixed | 319+0 | 107,005 | 198,685 | 305,690 | 5.79 | 0 |
| deepseek-v4-pro | feedback-static-r0-t1.0-p0.5 | mixed | 331+0 | 126,363 | 216,894 | 343,257 | 6.674 | 0 |
| deepseek-v4-pro | feedback-static-r0-t1.0-p1.0 | mixed | 286+4857 | 1,733,699 | 2,260,934 | 3,994,633 | 3.977 | 0 |
| deepseek-v4-pro-thinking | feedback-static-r1-t1.0-p1.0 | mixed | 1+2 | 457 | 9,612 | 10,069 | 111.423 | 0 |
| qwen-max | feedback-dynamic-r0-t1.0-p1.0 | mixed | 293+600 | 228,594 | 338,821 | 567,415 | 9.677 | 0 |
| qwen-max | feedback-none-r0-t0.5-p0.5 | estimated | 0+0 | 0 | 0 | 0 | — | 0 |
| qwen-max | feedback-static+dynamic-r0-t0.2-p1.0 | mixed | 1184+200 | 486,145 | 540,887 | 1,027,032 | 12.903 | 0 |
| qwen-max | feedback-static+dynamic-r0-t1.0-p0.5 | mixed | 1129+200 | 453,999 | 516,624 | 970,623 | 10.003 | 0 |
| qwen-max | feedback-static+dynamic-r0-t1.0-p1.0 | mixed | 104+896 | 389,233 | 383,076 | 772,309 | 10.59 | 0 |
| qwen-max | feedback-static-r0-t0.2-p1.0 | mixed | 306+0 | 73,798 | 113,258 | 187,056 | 9.543 | 0 |
| qwen-max | feedback-static-r0-t1.0-p0.5 | mixed | 307+0 | 79,885 | 118,751 | 198,636 | 9.712 | 0 |
| qwen-max | feedback-static-r0-t1.0-p1.0 | mixed | 118+4516 | 1,157,519 | 1,189,642 | 2,347,161 | 10.388 | 0 |
