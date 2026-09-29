#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int find_max_segments(int n, int a, int b, int c)
{
    int *dp;
    int lengths[3] = {a, b, c};
    size_t count;
    size_t i;
    size_t j;

    if (n < 0 || a <= 0 || b <= 0 || c <= 0) {
        return -1;
    }

    if ((size_t)n == SIZE_MAX) {
        return -1;
    }

    count = (size_t)n + 1U;

    if (count > SIZE_MAX / sizeof(*dp)) {
        return -1;
    }

    dp = malloc(count * sizeof(*dp));
    if (dp == NULL) {
        return -1;
    }

    dp[0] = 0;

    for (i = 1U; i < count; ++i) {
        dp[i] = -1;

        for (j = 0U; j < 3U; ++j) {
            size_t length = (size_t)lengths[j];

            if (i >= length && dp[i - length] >= 0) {
                int candidate = dp[i - length] + 1;

                if (candidate > dp[i]) {
                    dp[i] = candidate;
                }
            }
        }
    }

    i = (size_t)n;
    n = dp[i] < 0 ? 0 : dp[i];
    free(dp);

    return n;
}

int main(void)
{
    int n;
    int a;
    int b;
    int c;
    int result;

    if (scanf("%d %d %d %d", &n, &a, &b, &c) != 4) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    result = find_max_segments(n, a, b, c);
    if (result < 0) {
        fputs("Unable to calculate the result\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%d\n", result);
    return EXIT_SUCCESS;
}