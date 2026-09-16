#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

static int minimum_cost_path(const int *cost, size_t rows, size_t cols,
                             size_t m, size_t n, int64_t *result)
{
    int64_t *dp;
    size_t count;

    if (cost == NULL || result == NULL || rows == 0 || cols == 0 ||
        m >= rows || n >= cols) {
        return -1;
    }

    if (n == SIZE_MAX || n + 1 > SIZE_MAX / sizeof(*dp)) {
        return -1;
    }

    count = n + 1;
    dp = malloc(count * sizeof(*dp));
    if (dp == NULL) {
        return -1;
    }

    for (size_t i = 0; i <= m; ++i) {
        for (size_t j = 0; j <= n; ++j) {
            int64_t value = cost[i * cols + j];

            if (i == 0 && j == 0) {
                dp[j] = value;
            } else {
                int64_t best;

                if (i == 0) {
                    best = dp[j - 1];
                } else if (j == 0) {
                    best = dp[j];
                } else {
                    best = dp[j] < dp[j - 1] ? dp[j] : dp[j - 1];
                }

                if ((value > 0 && best > INT64_MAX - value) ||
                    (value < 0 && best < INT64_MIN - value)) {
                    free(dp);
                    return -1;
                }

                dp[j] = best + value;
            }
        }
    }

    *result = dp[n];
    free(dp);
    return 0;
}

int main(void)
{
    const int cost[][3] = {
        {1, 2, 3},
        {4, 8, 2},
        {1, 5, 3}
    };
    int64_t result;

    if (minimum_cost_path(&cost[0][0], 3, 3, 2, 2, &result) != 0) {
        fputs("Unable to calculate the minimum cost path.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", result);
    return EXIT_SUCCESS;
}