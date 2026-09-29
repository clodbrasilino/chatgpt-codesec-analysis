#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int minimum_squares(unsigned int number, unsigned int *result)
{
    unsigned int *dp;
    size_t count;
    unsigned int i;

    if (result == NULL) {
        return EINVAL;
    }

    if ((size_t)number > (SIZE_MAX / sizeof(*dp)) - 1U) {
        return EOVERFLOW;
    }

    count = (size_t)number + 1U;
    dp = malloc(count * sizeof(*dp));
    if (dp == NULL) {
        return ENOMEM;
    }

    dp[0] = 0U;

    for (i = 1U; i <= number; ++i) {
        unsigned int j;

        dp[i] = UINT_MAX;

        for (j = 1U; j <= i / j; ++j) {
            unsigned int square = j * j;
            unsigned int candidate = dp[i - square] + 1U;

            if (candidate < dp[i]) {
                dp[i] = candidate;
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
    int status;

    if (scanf("%u", &number) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    status = minimum_squares(number, &result);
    if (status != 0) {
        errno = status;
        perror("minimum_squares");
        return EXIT_FAILURE;
    }

    if (printf("%u\n", result) < 0) {
        fputs("Output error\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}