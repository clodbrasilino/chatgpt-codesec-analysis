# Token / time usage per experiment cell

Generated: 2026-09-01. Exact ledger active from 2026-09-01 onward
(results/{model}/{cell}.usage.jsonl — one record per API call:
tokens, reasoning tokens, latency). Rounds that ran before the ledger
existed are ESTIMATED from disk at ~3.6 chars/token; treat those as
order-of-magnitude figures. `mixed` cells show both.

| model | cell | source | calls (exact+est) | prompt tok | completion tok | total (approx) | mean latency s | failed |
|---|---|---|---|---|---|---|---|---|
| claude-fable-5 | feedback-dynamic-r0-t1.0-p1.0 | mixed | 710+600 | 288,264 | 745,507 | 1,033,771 | 23.076 | 521 |
| claude-fable-5 | feedback-static+dynamic-r0-t1.0-p1.0 | mixed | 7873+2922 | 1,527,473 | 3,042,804 | 4,570,277 | 18.98 | 6765 |
| claude-fable-5 | feedback-static-r0-t1.0-p1.0 | mixed | 8706+0 | 1,012,127 | 3,007,242 | 4,019,369 | 11.79 | 5235 |
| deepseek-v4-pro | feedback-dynamic-r0-t1.0-p1.0 | mixed | 306+600 | 308,249 | 593,588 | 901,837 | 5.983 | 0 |
| deepseek-v4-pro | feedback-static+dynamic-r0-t0.2-p1.0 | mixed | 1158+200 | 713,027 | 931,066 | 1,644,093 | 9.047 | 0 |
| deepseek-v4-pro | feedback-static+dynamic-r0-t1.0-p0.5 | mixed | 1100+200 | 636,738 | 864,821 | 1,501,559 | 6.54 | 0 |
| deepseek-v4-pro | feedback-static+dynamic-r0-t1.0-p1.0 | mixed | 3855+2922 | 2,799,044 | 3,167,708 | 5,966,752 | 5.597 | 0 |
| deepseek-v4-pro | feedback-static-r0-t0.2-p1.0 | mixed | 319+0 | 107,005 | 198,685 | 305,690 | 5.79 | 0 |
| deepseek-v4-pro | feedback-static-r0-t1.0-p0.5 | mixed | 331+0 | 126,363 | 216,894 | 343,257 | 6.674 | 0 |
| deepseek-v4-pro | feedback-static-r0-t1.0-p1.0 | mixed | 286+4857 | 1,733,699 | 2,260,934 | 3,994,633 | 3.977 | 0 |
| deepseek-v4-pro-thinking | feedback-static+dynamic-r1-t1.0-p1.0 | mixed | 441+600 | 285,750 | 2,559,304 | 2,845,054 | 223.3 | 148 |
| deepseek-v4-pro-thinking | feedback-static-r1-t1.0-p1.0 | mixed | 900+0 | 240,654 | 5,126,199 | 5,366,853 | 113.949 | 134 |
| gemini-3-pro | feedback-dynamic-r0-t1.0-p1.0 | mixed | 133+600 | 177,630 | 395,266 | 572,896 | 17.712 | 0 |
| gemini-3-pro | feedback-static+dynamic-r0-t0.2-p1.0 | mixed | 1058+0 | 282,614 | 563,809 | 846,423 | 11.403 | 158 |
| gemini-3-pro | feedback-static+dynamic-r0-t1.0-p0.5 | mixed | 938+0 | 265,946 | 547,371 | 813,317 | 11.07 | 55 |
| gemini-3-pro | feedback-static+dynamic-r0-t1.0-p1.0 | mixed | 2923+2922 | 1,206,210 | 1,646,984 | 2,853,194 | 18.528 | 1640 |
| gemini-3-pro | feedback-static-r0-t1.0-p1.0 | mixed | 22192+0 | 677,639 | 1,600,203 | 2,277,842 | 18.127 | 18649 |
| gemini-3-pro-thinking | feedback-static+dynamic-r1-t1.0-p1.0 | mixed | 392+600 | 266,286 | 504,705 | 770,991 | 49.915 | 159 |
| gemini-3-pro-thinking | feedback-static-r1-t1.0-p1.0 | mixed | 1210+0 | 165,118 | 522,575 | 687,693 | 32.371 | 496 |
| glm-5.1 | feedback-dynamic-r0-t1.0-p1.0 | mixed | 422+600 | 245,559 | 443,608 | 689,167 | 8.676 | 180 |
| glm-5.1 | feedback-static+dynamic-r0-t0.2-p1.0 | mixed | 1546+0 | 627,107 | 766,276 | 1,393,383 | 6.158 | 0 |
| glm-5.1 | feedback-static+dynamic-r0-t1.0-p0.5 | mixed | 2361+0 | 582,900 | 727,340 | 1,310,240 | 7.277 | 896 |
| glm-5.1 | feedback-static+dynamic-r0-t1.0-p1.0 | mixed | 5895+2922 | 3,144,883 | 3,123,159 | 6,268,042 | 4.497 | 0 |
| glm-5.1 | feedback-static-r0-t1.0-p1.0 | mixed | 8543+0 | 2,347,875 | 2,630,005 | 4,977,880 | 4.618 | 954 |
| glm-5.1-thinking | feedback-static+dynamic-r1-t1.0-p1.0 | mixed | 336+600 | 318,946 | 3,810,597 | 4,129,543 | 141.332 | 0 |
| glm-5.1-thinking | feedback-static-r1-t1.0-p1.0 | mixed | 2497+0 | 219,239 | 2,942,874 | 3,162,113 | 51.689 | 1673 |
| kimi-k3 | feedback-dynamic-r0-t1.0-p1.0 | mixed | 289+600 | 267,655 | 556,614 | 824,269 | 17.365 | 0 |
| kimi-k3 | feedback-static+dynamic-r0-t1.0-p1.0 | mixed | 2658+2922 | 1,720,606 | 2,315,936 | 4,036,542 | 12.118 | 404 |
| kimi-k3 | feedback-static-r0-t1.0-p1.0 | mixed | 3736+0 | 881,753 | 1,767,794 | 2,649,547 | 19.287 | 0 |
| kimi-k3-thinking | feedback-static+dynamic-r1-t1.0-p1.0 | mixed | 394+600 | 471,736 | 2,404,434 | 2,876,170 | 251.989 | 0 |
| kimi-k3-thinking | feedback-static-r1-t1.0-p1.0 | mixed | 3688+0 | 283,073 | 2,133,528 | 2,416,601 | 79.017 | 2908 |
| openai-gpt56-sol | feedback-dynamic-r0-t1.0-p1.0 | mixed | 38+600 | 93,175 | 427,724 | 520,899 | 8.757 | 15 |
| openai-gpt56-sol | feedback-static+dynamic-r0-t1.0-p1.0 | mixed | 1601+2922 | 1,346,958 | 2,212,544 | 3,559,502 | 7.279 | 0 |
| openai-gpt56-sol | feedback-static-r0-t1.0-p1.0 | mixed | 4180+0 | 1,061,584 | 2,022,135 | 3,083,719 | 7.332 | 7 |
| openai-gpt56-sol-thinking | feedback-static+dynamic-r1-t1.0-p1.0 | mixed | 520+600 | 538,117 | 1,591,099 | 2,129,216 | 49.951 | 0 |
| openai-gpt56-sol-thinking | feedback-static-r1-t1.0-p1.0 | mixed | 1305+0 | 519,043 | 2,150,327 | 2,669,370 | 47.525 | 192 |
| qwen-max | feedback-dynamic-r0-t1.0-p1.0 | mixed | 386+600 | 281,917 | 376,657 | 658,574 | 9.616 | 0 |
| qwen-max | feedback-none-r0-t0.5-p0.5 | estimated | 0+0 | 0 | 0 | 0 | — | 0 |
| qwen-max | feedback-static+dynamic-r0-t0.2-p1.0 | mixed | 1245+200 | 514,464 | 561,820 | 1,076,284 | 12.68 | 0 |
| qwen-max | feedback-static+dynamic-r0-t1.0-p0.5 | mixed | 1199+200 | 490,441 | 543,850 | 1,034,291 | 9.936 | 0 |
| qwen-max | feedback-static+dynamic-r0-t1.0-p1.0 | mixed | 4477+2922 | 2,188,958 | 1,930,298 | 4,119,256 | 8.867 | 609 |
| qwen-max | feedback-static+dynamic-r0-t1.0-p1.0-legacy2s | mixed | 104+896 | 389,233 | 383,076 | 772,309 | 10.59 | 0 |
| qwen-max | feedback-static-r0-t0.2-p1.0 | mixed | 306+0 | 73,798 | 113,258 | 187,056 | 9.543 | 0 |
| qwen-max | feedback-static-r0-t1.0-p0.5 | mixed | 307+0 | 79,885 | 118,751 | 198,636 | 9.712 | 0 |
| qwen-max | feedback-static-r0-t1.0-p1.0 | mixed | 118+4516 | 1,157,519 | 1,189,642 | 2,347,161 | 10.388 | 0 |
