#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

static int sum_fourth_powers_of_odds(uint64_t n, uint64_t *result)
{
    uint64_t sum = 0;

    if (result == NULL) {
        return -1;
    }

    for (uint64_t i = 0; i < n; ++i) {
        uint64_t odd;
        uint64_t square;
        uint64_t fourth_power;

        if (i > (UINT64_MAX - UINT64_C(1)) / UINT64_C(2)) {
            return -1;
        }

        odd = UINT64_C(2) * i + UINT64_C(1);

        if (odd > UINT64_MAX / odd) {
            return -1;
        }

        square = odd * odd;

        if (square > UINT64_MAX / square) {
            return -1;
        }

        fourth_power = square * square;

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
    int trailing;

    if (scanf("%" SCNu64, &n) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    do {
        trailing = getchar();
    } while (trailing == ' ' || trailing == '\t' ||
             trailing == '\n' || trailing == '\r' ||
             trailing == '\f' || trailing == '\v');

    if (trailing != EOF) {
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