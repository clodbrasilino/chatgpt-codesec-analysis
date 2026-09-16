#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

static int sum_fourth_powers_of_odds(uint64_t n, uint64_t *result)
{
    uint64_t sum = 0;

    if (result == NULL) {
        return -1;
    }

    for (uint64_t i = 0; i < n; ++i) {
        if (i > (UINT64_MAX - 1U) / 2U) {
            return -1;
        }

        uint64_t odd = 2U * i + 1U;

        if (odd != 0U && odd > UINT64_MAX / odd) {
            return -1;
        }

        uint64_t square = odd * odd;

        if (square != 0U && square > UINT64_MAX / square) {
            return -1;
        }

        uint64_t fourth_power = square * square;

        if (sum > UINT64_MAX - fourth_power) {
            return -1;
        }

        sum += fourth_power;
    }

    *result = sum;
    return 0;
}

int main(void)
{
    uint64_t n;
    uint64_t sum;

    errno = 0;
    if (scanf("%" SCNu64, &n) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (sum_fourth_powers_of_odds(n, &sum) != 0) {
        fputs("Result exceeds the supported integer range\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}