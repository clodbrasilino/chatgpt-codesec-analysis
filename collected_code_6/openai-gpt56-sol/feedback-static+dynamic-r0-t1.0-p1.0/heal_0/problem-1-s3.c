#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

static int min3(int a, int b, int c)
{
    int minimum = a;

    if (b < minimum) {
        minimum = b;
    }
    if (c < minimum) {
        minimum = c;
    }

    return minimum;
}

static int minimum_cost_path(const int *cost, size_t rows, size_t cols,
                             size_t m, size_t n, int *result)
{
    int *dp;

    if (cost == NULL || result == NULL || rows == 0 || cols == 0 ||
        m >= rows || n >= cols || n == SIZE_MAX ||
        n + 1 > SIZE_MAX / sizeof(*dp)) {
        return -1;
    }

    dp = malloc((n + 1) * sizeof(*dp));
    if (dp == NULL) {
        return -1;
    }

    dp[0] = cost[0];

    for (size_t j = 1; j <= n; ++j) {
        if (__builtin_add_overflow(dp[j - 1], cost[j], &dp[j])) {
            free(dp);
            return -1;
        }
    }

    for (size_t i = 1; i <= m; ++i) {
        if (__builtin_add_overflow(dp[0], cost[i * cols], &dp[0])) {
            free(dp);
            return -1;
        }

        int diagonal = dp[0] - cost[i * cols];

        for (size_t j = 1; j <= n; ++j) {
            int above = dp[j];
            int best = min3(dp[j - 1], above, diagonal);

            diagonal = above;
            if (__builtin_add_overflow(best, cost[i * cols + j], &dp[j])) {
                free(dp);
                return -1;
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
    int result;

    if (minimum_cost_path(&cost[0][0], 3, 3, 2, 2, &result) != 0) {
        fputs("Unable to calculate the minimum cost path.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%d\n", result);
    return EXIT_SUCCESS;
}