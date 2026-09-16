#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

static int min_squares(unsigned int n, unsigned int *result)
{
    unsigned int *dp;
    size_t count;
    unsigned int i;

    if (result == NULL) {
        return -1;
    }

    if ((size_t)n > (SIZE_MAX / sizeof(*dp)) - 1U) {
        return -1;
    }

    count = (size_t)n + 1U;
    dp = malloc(count * sizeof(*dp));
    if (dp == NULL) {
        return -1;
    }

    dp[0] = 0U;

    for (i = 1U; i <= n; ++i) {
        unsigned int j;

        dp[i] = i;

        for (j = 1U; j <= i / j; ++j) {
            unsigned int square = j * j;
            unsigned int candidate = dp[i - square] + 1U;

            if (candidate < dp[i]) {
                dp[i] = candidate;
            }
        }
    }

    *result = dp[n];
    free(dp);
    return 0;
}

int main(void)
{
    unsigned int number;
    unsigned int result;

    if (scanf("%u", &number) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (min_squares(number, &result) != 0) {
        fputs("Unable to compute result\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%u\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}