# Annotation audit — main s+d+fuzz cells

## deepseek-v4-pro (last fuzz-era round: 11)

| class | count |
|---|---|
| MATCH | 7810 |
| TEST-GAP | 12 |
| STATIC-GAP | 27 |
| MISMATCH-OTHER | 2 |
| ORPHAN | 13 |

By file era (pre-fuzz = mtime < 2026-09-15):

| era | class | count |
|---|---|---|
| fuzz | MATCH | 6205 |
| fuzz | MISMATCH-OTHER | 2 |
| fuzz | ORPHAN | 13 |
| fuzz | STATIC-GAP | 16 |
| fuzz | TEST-GAP | 8 |
| pre-fuzz | MATCH | 1605 |
| pre-fuzz | STATIC-GAP | 11 |
| pre-fuzz | TEST-GAP | 4 |

Outcome soundness:

| check | count |
|---|---|
| NOT_CLEANED-BUT-DETECTION-FREE | 1 |
| OK-clean | 1241 |
| OK-clean_at_start | 1192 |
| OK-not_cleaned | 488 |

Examples `TEST-GAP`: deepseek-v4-pro/heal_7/problem-537-s3, deepseek-v4-pro/heal_9/problem-621, deepseek-v4-pro/heal_9/problem-621-s3, deepseek-v4-pro/heal_11/problem-102, deepseek-v4-pro/heal_11/problem-118-s2, deepseek-v4-pro/heal_11/problem-206-s3
Examples `ORPHAN`: deepseek-v4-pro/heal_11/problem-116-s2, deepseek-v4-pro/heal_11/problem-202-s3, deepseek-v4-pro/heal_11/problem-203, deepseek-v4-pro/heal_11/problem-250-s2, deepseek-v4-pro/heal_11/problem-385-s3, deepseek-v4-pro/heal_11/problem-44
Examples `STATIC-GAP`: deepseek-v4-pro/heal_11/problem-118, deepseek-v4-pro/heal_11/problem-118-s3, deepseek-v4-pro/heal_11/problem-13, deepseek-v4-pro/heal_11/problem-237, deepseek-v4-pro/heal_11/problem-350-s2, deepseek-v4-pro/heal_11/problem-352-s3
Examples `MISMATCH-OTHER`: deepseek-v4-pro/heal_11/problem-537, deepseek-v4-pro/heal_11/problem-631-s2
Examples `NOT_CLEANED-BUT-DETECTION-FREE`: deepseek-v4-pro/problem-44(not_cleaned@r10)

## qwen-max (last fuzz-era round: 11)

| class | count |
|---|---|
| MATCH | 6063 |
| FUZZ-GAP | 6 |
| TEST-GAP | 13 |
| STATIC-GAP | 15 |
| EXTRA | 1 |
| ORPHAN | 2 |

By file era (pre-fuzz = mtime < 2026-09-15):

| era | class | count |
|---|---|---|
| fuzz | EXTRA | 1 |
| fuzz | FUZZ-GAP | 6 |
| fuzz | MATCH | 4799 |
| fuzz | ORPHAN | 2 |
| fuzz | STATIC-GAP | 15 |
| fuzz | TEST-GAP | 13 |
| pre-fuzz | MATCH | 1264 |

Outcome soundness:

| check | count |
|---|---|
| OK-clean | 1293 |
| OK-clean_at_start | 1284 |
| OK-not_cleaned | 345 |

Examples `TEST-GAP`: qwen-max/heal_11/problem-118-s3, qwen-max/heal_11/problem-244, qwen-max/heal_11/problem-500-s2, qwen-max/heal_11/problem-537-s2, qwen-max/heal_11/problem-537-s3, qwen-max/heal_11/problem-595
Examples `FUZZ-GAP`: qwen-max/heal_11/problem-279, qwen-max/heal_11/problem-279-s3, qwen-max/heal_11/problem-752-s3, qwen-max/heal_11/problem-86, qwen-max/heal_11/problem-86-s2, qwen-max/heal_11/problem-86-s3
Examples `STATIC-GAP`: qwen-max/heal_11/problem-307-s2, qwen-max/heal_11/problem-310, qwen-max/heal_11/problem-310-s3, qwen-max/heal_11/problem-381-s2, qwen-max/heal_11/problem-450, qwen-max/heal_11/problem-450-s2
Examples `ORPHAN`: qwen-max/heal_11/problem-483-s2, qwen-max/heal_11/problem-741-s2
Examples `EXTRA`: qwen-max/heal_11/problem-760-s2

## glm-5.1 (last fuzz-era round: 11)

| class | count |
|---|---|
| MATCH | 7533 |
| TEST-GAP | 11 |
| STATIC-GAP | 38 |
| MISMATCH-OTHER | 8 |
| ORPHAN | 111 |

By file era (pre-fuzz = mtime < 2026-09-15):

| era | class | count |
|---|---|---|
| fuzz | MATCH | 5510 |
| fuzz | MISMATCH-OTHER | 6 |
| fuzz | ORPHAN | 97 |
| fuzz | STATIC-GAP | 26 |
| fuzz | TEST-GAP | 5 |
| pre-fuzz | MATCH | 2023 |
| pre-fuzz | MISMATCH-OTHER | 2 |
| pre-fuzz | ORPHAN | 14 |
| pre-fuzz | STATIC-GAP | 12 |
| pre-fuzz | TEST-GAP | 6 |

Outcome soundness:

| check | count |
|---|---|
| NOT_CLEANED-BUT-DETECTION-FREE | 4 |
| OK-clean | 1560 |
| OK-clean_at_start | 1020 |
| OK-not_cleaned | 338 |

Examples `TEST-GAP`: glm-5.1/heal_3/problem-450, glm-5.1/heal_5/problem-640-s3, glm-5.1/heal_11/problem-310-s2, glm-5.1/heal_11/problem-403, glm-5.1/heal_11/problem-537, glm-5.1/heal_11/problem-640
Examples `STATIC-GAP`: glm-5.1/heal_11/problem-102-s2, glm-5.1/heal_11/problem-118-s3, glm-5.1/heal_11/problem-159, glm-5.1/heal_11/problem-162-s3, glm-5.1/heal_11/problem-283-s3, glm-5.1/heal_11/problem-295
Examples `ORPHAN`: glm-5.1/heal_11/problem-107, glm-5.1/heal_11/problem-129-s2, glm-5.1/heal_11/problem-131, glm-5.1/heal_11/problem-138, glm-5.1/heal_11/problem-151, glm-5.1/heal_11/problem-151-s2
Examples `MISMATCH-OTHER`: glm-5.1/heal_11/problem-386, glm-5.1/heal_11/problem-450-s3, glm-5.1/heal_11/problem-507-s2, glm-5.1/heal_11/problem-537-s3, glm-5.1/heal_11/problem-724-s3, glm-5.1/heal_11/problem-756-s3
Examples `NOT_CLEANED-BUT-DETECTION-FREE`: glm-5.1/problem-18(not_cleaned@r10), glm-5.1/problem-335-s2(not_cleaned@r10), glm-5.1/problem-681-s3(not_cleaned@r10), glm-5.1/problem-849(not_cleaned@r10)

## kimi-k3 (last fuzz-era round: 11)

| class | count |
|---|---|
| MATCH | 8252 |
| FUZZ-GAP | 1 |
| TEST-GAP | 6 |
| STATIC-GAP | 16 |
| MISMATCH-OTHER | 5 |
| ORPHAN | 6 |

By file era (pre-fuzz = mtime < 2026-09-15):

| era | class | count |
|---|---|---|
| fuzz | FUZZ-GAP | 1 |
| fuzz | MATCH | 7371 |
| fuzz | MISMATCH-OTHER | 4 |
| fuzz | ORPHAN | 4 |
| fuzz | STATIC-GAP | 6 |
| fuzz | TEST-GAP | 5 |
| pre-fuzz | MATCH | 881 |
| pre-fuzz | MISMATCH-OTHER | 1 |
| pre-fuzz | ORPHAN | 2 |
| pre-fuzz | STATIC-GAP | 10 |
| pre-fuzz | TEST-GAP | 1 |

Outcome soundness:

| check | count |
|---|---|
| NOT_CLEANED-BUT-DETECTION-FREE | 1 |
| OK-clean | 974 |
| OK-clean_at_start | 1382 |
| OK-not_cleaned | 565 |

Examples `FUZZ-GAP`: kimi-k3/heal_11/problem-107-s3
Examples `STATIC-GAP`: kimi-k3/heal_11/problem-118, kimi-k3/heal_11/problem-118-s2, kimi-k3/heal_11/problem-118-s3, kimi-k3/heal_11/problem-160-s2, kimi-k3/heal_11/problem-310, kimi-k3/heal_11/problem-310-s3
Examples `MISMATCH-OTHER`: kimi-k3/heal_11/problem-157-s3, kimi-k3/heal_11/problem-765-s2, kimi-k3/heal_11/problem-838, kimi-k3/heal_11/problem-838-s2, kimi-k3/heal_11/problem-870-s2
Examples `ORPHAN`: kimi-k3/heal_11/problem-175-s2, kimi-k3/heal_11/problem-595, kimi-k3/heal_11/problem-595-s2, kimi-k3/heal_11/problem-699, kimi-k3/heal_11/problem-699-s2, kimi-k3/heal_11/problem-813-s2
Examples `TEST-GAP`: kimi-k3/heal_11/problem-640, kimi-k3/heal_11/problem-640-s3, kimi-k3/heal_11/problem-699-s3, kimi-k3/heal_11/problem-706, kimi-k3/heal_11/problem-903-s3, kimi-k3/heal_11/problem-952-s2
Examples `NOT_CLEANED-BUT-DETECTION-FREE`: kimi-k3/problem-813-s2(not_cleaned@r10)

## openai-gpt56-sol (last fuzz-era round: 11)

| class | count |
|---|---|
| MATCH | 8813 |
| TEST-GAP | 2 |
| STATIC-GAP | 5 |
| MISMATCH-OTHER | 2 |
| ORPHAN | 4 |

By file era (pre-fuzz = mtime < 2026-09-15):

| era | class | count |
|---|---|---|
| fuzz | MATCH | 8734 |
| fuzz | MISMATCH-OTHER | 2 |
| fuzz | ORPHAN | 3 |
| fuzz | STATIC-GAP | 3 |
| fuzz | TEST-GAP | 2 |
| pre-fuzz | MATCH | 79 |
| pre-fuzz | ORPHAN | 1 |
| pre-fuzz | STATIC-GAP | 2 |

Outcome soundness:

| check | count |
|---|---|
| OK-clean | 921 |
| OK-clean_at_start | 1436 |
| OK-not_cleaned | 565 |

Examples `STATIC-GAP`: openai-gpt56-sol/heal_11/problem-118-s2, openai-gpt56-sol/heal_11/problem-142-s2, openai-gpt56-sol/heal_11/problem-482-s2, openai-gpt56-sol/heal_11/problem-676-s2, openai-gpt56-sol/heal_11/problem-71-s2
Examples `ORPHAN`: openai-gpt56-sol/heal_11/problem-138-s3, openai-gpt56-sol/heal_11/problem-255, openai-gpt56-sol/heal_11/problem-27, openai-gpt56-sol/heal_11/problem-57
Examples `TEST-GAP`: openai-gpt56-sol/heal_11/problem-218, openai-gpt56-sol/heal_11/problem-677-s3
Examples `MISMATCH-OTHER`: openai-gpt56-sol/heal_11/problem-311, openai-gpt56-sol/heal_11/problem-430

## claude-fable-5 (last fuzz-era round: 11)

| class | count |
|---|---|
| MATCH | 5183 |
| TEST-GAP | 2 |
| STATIC-GAP | 7 |
| MISMATCH-OTHER | 2 |

By file era (pre-fuzz = mtime < 2026-09-15):

| era | class | count |
|---|---|---|
| fuzz | MATCH | 5183 |
| fuzz | MISMATCH-OTHER | 2 |
| fuzz | STATIC-GAP | 7 |
| fuzz | TEST-GAP | 2 |

Outcome soundness:

| check | count |
|---|---|
| OK-clean | 911 |
| OK-clean_at_start | 1708 |
| OK-not_cleaned | 303 |

Examples `STATIC-GAP`: claude-fable-5/heal_11/problem-118-s2, claude-fable-5/heal_11/problem-213-s2, claude-fable-5/heal_11/problem-249-s3, claude-fable-5/heal_11/problem-310, claude-fable-5/heal_11/problem-310-s2, claude-fable-5/heal_11/problem-424
Examples `MISMATCH-OTHER`: claude-fable-5/heal_11/problem-321-s3, claude-fable-5/heal_11/problem-424-s2
Examples `TEST-GAP`: claude-fable-5/heal_11/problem-640-s2, claude-fable-5/heal_11/problem-640-s3

## gemini-3-pro (last fuzz-era round: 11)

| class | count |
|---|---|
| MATCH | 2177 |
| FUZZ-GAP | 7 |
| TEST-GAP | 3 |
| STATIC-GAP | 11 |
| MISMATCH-OTHER | 4 |
| ORPHAN | 1 |

By file era (pre-fuzz = mtime < 2026-09-15):

| era | class | count |
|---|---|---|
| fuzz | FUZZ-GAP | 7 |
| fuzz | MATCH | 2177 |
| fuzz | MISMATCH-OTHER | 4 |
| fuzz | ORPHAN | 1 |
| fuzz | STATIC-GAP | 11 |
| fuzz | TEST-GAP | 3 |

Outcome soundness:

| check | count |
|---|---|
| OK-clean | 1054 |
| OK-clean_at_start | 1812 |
| OK-not_cleaned | 56 |

Examples `FUZZ-GAP`: gemini-3-pro/heal_4/problem-621, gemini-3-pro/heal_9/problem-621-s3, gemini-3-pro/heal_10/problem-621-s3, gemini-3-pro/heal_11/problem-503, gemini-3-pro/heal_11/problem-503-s2, gemini-3-pro/heal_11/problem-503-s3
Examples `STATIC-GAP`: gemini-3-pro/heal_11/problem-118-s2, gemini-3-pro/heal_11/problem-310-s2, gemini-3-pro/heal_11/problem-310-s3, gemini-3-pro/heal_11/problem-41-s2, gemini-3-pro/heal_11/problem-41-s3, gemini-3-pro/heal_11/problem-426-s2
Examples `MISMATCH-OTHER`: gemini-3-pro/heal_11/problem-426, gemini-3-pro/heal_11/problem-670, gemini-3-pro/heal_11/problem-670-s3, gemini-3-pro/heal_11/problem-677-s2
Examples `TEST-GAP`: gemini-3-pro/heal_11/problem-444-s2, gemini-3-pro/heal_11/problem-640-s3, gemini-3-pro/heal_11/problem-670-s2
Examples `ORPHAN`: gemini-3-pro/heal_11/problem-621-s2

## TOTAL across 7 models

| class | count |
|---|---|
| EXTRA | 1 |
| FUZZ-GAP | 14 |
| MATCH | 45831 |
| MISMATCH-OTHER | 23 |
| ORPHAN | 137 |
| STATIC-GAP | 119 |
| TEST-GAP | 49 |

Outcome totals:

| check | count |
|---|---|
| NOT_CLEANED-BUT-DETECTION-FREE | 6 |
| OK-clean | 7954 |
| OK-clean_at_start | 9834 |
| OK-not_cleaned | 2660 |
