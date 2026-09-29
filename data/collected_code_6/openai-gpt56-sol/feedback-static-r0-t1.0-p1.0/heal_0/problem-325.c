#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int minimum_squares(unsigned int number, unsigned int *result)
{
    unsigned int *dp;
    size_t count;
    unsigned int i;

    if (result == NULL) {
        return -1;
    }

    if ((size_t)number > (SIZE_MAX / sizeof(*dp)) - 1U) {
        return -1;
    }

    count = (size_t)number + 1U;
    dp = malloc(count * sizeof(*dp));
    if (dp == NULL) {
        return -1;
    }

    dp[0] = 0U;

    for (i = 1U; i <= number; ++i) {
        unsigned int square_root;

        dp[i] = UINT_MAX;

        for (square_root = 1U; square_root <= i / square_root; ++square_root) {
            unsigned int square = square_root * square_root;
            unsigned int previous = dp[i - square];

            if (previous != UINT_MAX && previous + 1U < dp[i]) {
                dp[i] = previous + 1U;
            }
        }
    }

    *result = dp[number];
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

    if (minimum_squares(number, &result) != 0) {
        fputs("Unable to compute result\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%u\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}