# Statistical report

## Per-model summary (rates with bootstrap 95% CIs)

| model                    | cell                                 |    n |   defect_rate |   defect_rate_static |   compile_rate |   oracle_pass_rate | defect_ci    | compile_ci   |
|:-------------------------|:-------------------------------------|-----:|--------------:|---------------------:|---------------:|-------------------:|:-------------|:-------------|
| deepseek-v4-pro          | feedback-static-r0-t0.2-p1.0         |  200 |        0.305  |               0.305  |         0.98   |             nan    | [0.24, 0.37] | [0.96, 0.99] |
| deepseek-v4-pro          | feedback-static-r0-t1.0-p0.5         |  200 |        0.365  |               0.365  |         0.975  |             nan    | [0.30, 0.43] | [0.95, 0.99] |
| deepseek-v4-pro          | feedback-static-r0-t1.0-p1.0         | 2922 |        0.3443 |               0.3443 |         0.9795 |             nan    | [0.33, 0.36] | [0.97, 0.98] |
| deepseek-v4-pro-thinking | feedback-static-r1-t1.0-p1.0         |    2 |        0      |               0      |         1      |               1    | [0.00, 0.00] | [1.00, 1.00] |
| qwen-max                 | feedback-static+dynamic-r0-t1.0-p1.0 |  400 |        0.4825 |               0.41   |         0.8825 |               0.94 | [0.43, 0.53] | [0.85, 0.91] |
| qwen-max                 | feedback-static-r0-t0.2-p1.0         |  200 |        0.37   |               0.37   |         0.915  |             nan    | [0.30, 0.44] | [0.88, 0.95] |
| qwen-max                 | feedback-static-r0-t1.0-p0.5         |  200 |        0.29   |               0.29   |         0.935  |             nan    | [0.23, 0.35] | [0.90, 0.96] |
| qwen-max                 | feedback-static-r0-t1.0-p1.0         | 2922 |        0.3826 |               0.3826 |         0.9387 |             nan    | [0.37, 0.40] | [0.93, 0.95] |

*CIs are percentile bootstrap (10,000 draws). `oracle_pass_rate` and `defect_rate` include dynamic channels only for cells measured with static+dynamic; `defect_rate_static` is static-only and always comparable across cells.*

## Pairwise model contrasts

*Note: cells differ in configuration (feedback-static+dynamic-r0-t1.0-p1.0, feedback-static-r0-t0.2-p1.0, feedback-static-r0-t1.0-p0.5, feedback-static-r0-t1.0-p1.0, feedback-static-r1-t1.0-p1.0); interpret contrasts across mixed cells with caution.*

## Initial defect rate (flagged at heal_0)

| name1           | name2    |   rate1 |   rate2 |   delta |   cohens_h | test   |     p_value |   odds_ratio |   p_adjusted | significant   |
|:----------------|:---------|--------:|--------:|--------:|-----------:|:-------|------------:|-------------:|-------------:|:--------------|
| deepseek-v4-pro | qwen-max |  0.3432 |  0.3877 | -0.0445 |     -0.093 | chi2   | 0.000108273 |        0.825 |     0.000108 | True          |

## Final clean rate

| name1           | name2    |   rate1 |   rate2 |   delta |   cohens_h | test   |    p_value |   odds_ratio |   p_adjusted | significant   |
|:----------------|:---------|--------:|--------:|--------:|-----------:|:-------|-----------:|-------------:|-------------:|:--------------|
| deepseek-v4-pro | qwen-max |  0.9705 |  0.9801 | -0.0096 |     -0.062 | chi2   | 0.00902888 |        0.667 |     0.009029 | True          |

## Compile rate

| name1           | name2    |   rate1 |   rate2 |   delta |   cohens_h | test   |     p_value |   odds_ratio |   p_adjusted | significant   |
|:----------------|:---------|--------:|--------:|--------:|-----------:|:-------|------------:|-------------:|-------------:|:--------------|
| deepseek-v4-pro | qwen-max |  0.9792 |  0.9312 |   0.048 |      0.241 | chi2   | 8.97363e-22 |        3.482 |            0 | True          |

## Rounds-to-clean (Mann-Whitney U + Cliff's delta)

| name1           | name2    |   n1 |   n2 |   mean1 |   mean2 | test        |   p_value |   cliffs_delta | effect     |   p_adjusted | significant   |
|:----------------|:---------|-----:|-----:|--------:|--------:|:------------|----------:|---------------:|:-----------|-------------:|:--------------|
| deepseek-v4-pro | qwen-max |   57 |  160 |   1.386 |   1.688 | mannwhitney |  0.227794 |         -0.085 | negligible |     0.227794 | False         |
