#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_fifth_powers_of_odds(uint64_t n, uint64_t *result)
{
    uint64_t sum = 0;

    if (result == NULL) {
        return 0;
    }

    for (uint64_t i = 0; i < n; ++i) {
        uint64_t odd;
        uint64_t square;
        uint64_t fourth;
        uint64_t fifth;

        if (i > (UINT64_MAX - UINT64_C(1)) / UINT64_C(2)) {
            return 0;
        }

        odd = UINT64_C(2) * i + UINT64_C(1);

        if (odd > UINT64_MAX / odd) {
            return 0;
        }
        square = odd * odd;

        if (square > UINT64_MAX / square) {
            return 0;
        }
        fourth = square * square;

        if (fourth > UINT64_MAX / odd) {
            return 0;
        }
        fifth = fourth * odd;

        if (sum > UINT64_MAX - fifth) {
            return 0;
        }
        sum += fifth;
    }

    *result = sum;
    return 1;
}

int main(void)
{
    uint64_t n;
    uint64_t sum;

    if (scanf("%" SCNu64, &n) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!sum_fifth_powers_of_odds(n, &sum)) {
        fputs("Result exceeds the supported range\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", sum);
    return EXIT_SUCCESS;
}