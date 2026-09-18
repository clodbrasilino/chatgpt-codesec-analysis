# Annotation audit — main s+d+fuzz cells

## deepseek-v4-pro (last fuzz-era round: 11)

| class | count |
|---|---|
| MATCH | 3637 |
| FUZZ-GAP | 62 |
| TEST-GAP | 25 |
| ORACLE-GAP | 3 |
| ORPHAN | 1 |

By file era (pre-fuzz = mtime < 2026-09-15):

| era | class | count |
|---|---|---|
| fuzz | FUZZ-GAP | 10 |
| fuzz | MATCH | 1393 |
| pre-fuzz | FUZZ-GAP | 52 |
| pre-fuzz | MATCH | 2244 |
| pre-fuzz | ORACLE-GAP | 3 |
| pre-fuzz | ORPHAN | 1 |
| pre-fuzz | TEST-GAP | 25 |

Outcome soundness:

| check | count |
|---|---|
| OK-clean | 1064 |
| OK-clean_at_start | 1665 |
| OK-not_cleaned | 193 |

Examples `TEST-GAP`: deepseek-v4-pro/heal_1/problem-101-s2, deepseek-v4-pro/heal_1/problem-101-s3, deepseek-v4-pro/heal_1/problem-102, deepseek-v4-pro/heal_1/problem-102-s2, deepseek-v4-pro/heal_1/problem-102-s3, deepseek-v4-pro/heal_1/problem-103-s3
Examples `FUZZ-GAP`: deepseek-v4-pro/heal_1/problem-103, deepseek-v4-pro/heal_1/problem-129, deepseek-v4-pro/heal_1/problem-274-s3, deepseek-v4-pro/heal_1/problem-300, deepseek-v4-pro/heal_1/problem-314-s3, deepseek-v4-pro/heal_1/problem-453
Examples `ORACLE-GAP`: deepseek-v4-pro/heal_1/problem-348-s2, deepseek-v4-pro/heal_1/problem-539, deepseek-v4-pro/heal_1/problem-748-s2
Examples `ORPHAN`: deepseek-v4-pro/heal_1/problem-507-s2

## qwen-max (last fuzz-era round: 11)

| class | count |
|---|---|
| MATCH | 3460 |
| FUZZ-GAP | 198 |

By file era (pre-fuzz = mtime < 2026-09-15):

| era | class | count |
|---|---|---|
| fuzz | FUZZ-GAP | 105 |
| fuzz | MATCH | 1973 |
| pre-fuzz | FUZZ-GAP | 93 |
| pre-fuzz | MATCH | 1487 |

Outcome soundness:

| check | count |
|---|---|
| OK-clean | 1217 |
| OK-clean_at_start | 1546 |
| OK-not_cleaned | 159 |

Examples `FUZZ-GAP`: qwen-max/heal_1/problem-129-s3, qwen-max/heal_1/problem-150-s3, qwen-max/heal_1/problem-169-s2, qwen-max/heal_1/problem-170-s3, qwen-max/heal_1/problem-179-s2, qwen-max/heal_1/problem-179-s3

## glm-5.1 (last fuzz-era round: 11)

| class | count |
|---|---|
| MATCH | 5910 |
| FUZZ-GAP | 11 |
| TEST-GAP | 18 |

By file era (pre-fuzz = mtime < 2026-09-15):

| era | class | count |
|---|---|---|
| fuzz | FUZZ-GAP | 3 |
| fuzz | MATCH | 2825 |
| pre-fuzz | FUZZ-GAP | 8 |
| pre-fuzz | MATCH | 3085 |
| pre-fuzz | TEST-GAP | 18 |

Outcome soundness:

| check | count |
|---|---|
| OK-clean | 1362 |
| OK-clean_at_start | 1322 |
| OK-not_cleaned | 238 |

Examples `FUZZ-GAP`: glm-5.1/heal_1/problem-20, glm-5.1/heal_1/problem-510-s2, glm-5.1/heal_1/problem-520, glm-5.1/heal_1/problem-767-s2, glm-5.1/heal_1/problem-782-s2, glm-5.1/heal_2/problem-803-s3
Examples `TEST-GAP`: glm-5.1/heal_1/problem-218, glm-5.1/heal_1/problem-218-s3, glm-5.1/heal_1/problem-306-s3, glm-5.1/heal_1/problem-34, glm-5.1/heal_1/problem-355, glm-5.1/heal_1/problem-355-s3

## kimi-k3 (last fuzz-era round: 11)

| class | count |
|---|---|
| MATCH | 2067 |
| FUZZ-GAP | 79 |
| TEST-GAP | 12 |

By file era (pre-fuzz = mtime < 2026-09-15):

| era | class | count |
|---|---|---|
| fuzz | FUZZ-GAP | 31 |
| fuzz | MATCH | 680 |
| pre-fuzz | FUZZ-GAP | 48 |
| pre-fuzz | MATCH | 1387 |
| pre-fuzz | TEST-GAP | 12 |

Outcome soundness:

| check | count |
|---|---|
| OK-clean | 802 |
| OK-clean_at_start | 2036 |
| OK-not_cleaned | 84 |

Examples `TEST-GAP`: kimi-k3/heal_1/problem-102, kimi-k3/heal_1/problem-102-s2, kimi-k3/heal_1/problem-102-s3, kimi-k3/heal_1/problem-107-s3, kimi-k3/heal_1/problem-118-s2, kimi-k3/heal_1/problem-175-s2
Examples `FUZZ-GAP`: kimi-k3/heal_1/problem-122-s2, kimi-k3/heal_1/problem-126-s2, kimi-k3/heal_1/problem-129-s3, kimi-k3/heal_1/problem-134, kimi-k3/heal_1/problem-179, kimi-k3/heal_1/problem-179-s3

## openai-gpt56-sol (last fuzz-era round: 11)

| class | count |
|---|---|
| MATCH | 1626 |
| FUZZ-GAP | 5 |
| TEST-GAP | 1 |

By file era (pre-fuzz = mtime < 2026-09-15):

| era | class | count |
|---|---|---|
| fuzz | FUZZ-GAP | 4 |
| fuzz | MATCH | 1388 |
| pre-fuzz | FUZZ-GAP | 1 |
| pre-fuzz | MATCH | 238 |
| pre-fuzz | TEST-GAP | 1 |

Outcome soundness:

| check | count |
|---|---|
| OK-clean | 649 |
| OK-clean_at_start | 2235 |
| OK-not_cleaned | 38 |

Examples `TEST-GAP`: openai-gpt56-sol/heal_1/problem-20-s3
Examples `FUZZ-GAP`: openai-gpt56-sol/heal_1/problem-324-s2, openai-gpt56-sol/heal_1/problem-683-s2, openai-gpt56-sol/heal_1/problem-911, openai-gpt56-sol/heal_1/problem-911-s3, openai-gpt56-sol/heal_2/problem-469-s2

## claude-fable-5 (last fuzz-era round: 11)

| class | count |
|---|---|
| MATCH | 1073 |
| FUZZ-GAP | 26 |

By file era (pre-fuzz = mtime < 2026-09-15):

| era | class | count |
|---|---|---|
| fuzz | FUZZ-GAP | 26 |
| fuzz | MATCH | 1073 |

Outcome soundness:

| check | count |
|---|---|
| OK-clean | 615 |
| OK-clean_at_start | 2276 |
| OK-not_cleaned | 31 |

Examples `FUZZ-GAP`: claude-fable-5/heal_1/problem-190, claude-fable-5/heal_1/problem-190-s2, claude-fable-5/heal_1/problem-291-s3, claude-fable-5/heal_1/problem-402, claude-fable-5/heal_1/problem-402-s2, claude-fable-5/heal_1/problem-402-s3

## gemini-3-pro (last fuzz-era round: 11)

| class | count |
|---|---|
| MATCH | 1260 |
| FUZZ-GAP | 11 |

By file era (pre-fuzz = mtime < 2026-09-15):

| era | class | count |
|---|---|---|
| fuzz | FUZZ-GAP | 11 |
| fuzz | MATCH | 1260 |

Outcome soundness:

| check | count |
|---|---|
| OK-clean | 700 |
| OK-clean_at_start | 2185 |
| OK-not_cleaned | 37 |

Examples `FUZZ-GAP`: gemini-3-pro/heal_1/problem-194-s3, gemini-3-pro/heal_1/problem-218-s3, gemini-3-pro/heal_1/problem-501-s3, gemini-3-pro/heal_1/problem-598-s3, gemini-3-pro/heal_1/problem-603, gemini-3-pro/heal_1/problem-633-s2

## TOTAL across 7 models

| class | count |
|---|---|
| FUZZ-GAP | 392 |
| MATCH | 19033 |
| ORACLE-GAP | 3 |
| ORPHAN | 1 |
| TEST-GAP | 56 |

Outcome totals:

| check | count |
|---|---|
| OK-clean | 6409 |
| OK-clean_at_start | 13265 |
| OK-not_cleaned | 780 |
