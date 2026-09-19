# Annotation audit — main s+d+fuzz cells

## deepseek-v4-pro (last fuzz-era round: 11)

| class | count |
|---|---|
| MATCH | 3701 |

By file era (pre-fuzz = mtime < 2026-09-15):

| era | class | count |
|---|---|---|
| fuzz | MATCH | 1600 |
| pre-fuzz | MATCH | 2101 |

Outcome soundness:

| check | count |
|---|---|
| OK-clean | 1067 |
| OK-clean_at_start | 1665 |
| OK-not_cleaned | 190 |


## qwen-max (last fuzz-era round: 11)

| class | count |
|---|---|
| MATCH | 3612 |

By file era (pre-fuzz = mtime < 2026-09-15):

| era | class | count |
|---|---|---|
| fuzz | MATCH | 2132 |
| pre-fuzz | MATCH | 1480 |

Outcome soundness:

| check | count |
|---|---|
| OK-clean | 1225 |
| OK-clean_at_start | 1545 |
| OK-not_cleaned | 152 |


## glm-5.1 (last fuzz-era round: 11)

| class | count |
|---|---|
| MATCH | 5944 |

By file era (pre-fuzz = mtime < 2026-09-15):

| era | class | count |
|---|---|---|
| fuzz | MATCH | 2893 |
| pre-fuzz | MATCH | 3051 |

Outcome soundness:

| check | count |
|---|---|
| OK-clean | 1359 |
| OK-clean_at_start | 1322 |
| OK-not_cleaned | 241 |


## kimi-k3 (last fuzz-era round: 11)

| class | count |
|---|---|
| MATCH | 2127 |

By file era (pre-fuzz = mtime < 2026-09-15):

| era | class | count |
|---|---|---|
| fuzz | MATCH | 789 |
| pre-fuzz | MATCH | 1338 |

Outcome soundness:

| check | count |
|---|---|
| OK-clean | 802 |
| OK-clean_at_start | 2035 |
| OK-not_cleaned | 85 |


## openai-gpt56-sol (last fuzz-era round: 11)

| class | count |
|---|---|
| MATCH | 1630 |

By file era (pre-fuzz = mtime < 2026-09-15):

| era | class | count |
|---|---|---|
| fuzz | MATCH | 1393 |
| pre-fuzz | MATCH | 237 |

Outcome soundness:

| check | count |
|---|---|
| OK-clean | 649 |
| OK-clean_at_start | 2235 |
| OK-not_cleaned | 38 |


## claude-fable-5 (last fuzz-era round: 11)

| class | count |
|---|---|
| MATCH | 1095 |

By file era (pre-fuzz = mtime < 2026-09-15):

| era | class | count |
|---|---|---|
| fuzz | MATCH | 1095 |

Outcome soundness:

| check | count |
|---|---|
| OK-clean | 614 |
| OK-clean_at_start | 2276 |
| OK-not_cleaned | 32 |


## gemini-3-pro (last fuzz-era round: 11)

| class | count |
|---|---|
| MATCH | 1262 |

By file era (pre-fuzz = mtime < 2026-09-15):

| era | class | count |
|---|---|---|
| fuzz | MATCH | 1262 |

Outcome soundness:

| check | count |
|---|---|
| OK-clean | 701 |
| OK-clean_at_start | 2185 |
| OK-not_cleaned | 36 |


## TOTAL across 7 models

| class | count |
|---|---|
| MATCH | 19371 |

Outcome totals:

| check | count |
|---|---|
| OK-clean | 6417 |
| OK-clean_at_start | 13263 |
| OK-not_cleaned | 774 |
