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

        if (i > (UINT64_MAX - 1) / 2) {
            return 0;
        }
        /* Possible weaknesses found:
         *  Assignment 'odd=2*i+1', assigned value is greater than 0
         */
        odd = 2 * i + 1;

        /* Possible weaknesses found:
         *  Condition 'odd!=0' is always true [knownConditionTrueFalse]
         *  Condition 'odd!=0' is always true
         */
        if (odd != 0 && odd > UINT64_MAX / odd) {
            return 0;
        }
        square = odd * odd;

        if (square != 0 && square > UINT64_MAX / square) {
            return 0;
        }
        fourth = square * square;

        if (odd != 0 && fourth > UINT64_MAX / odd) {
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
    int scan_result;

    scan_result = scanf("%" SCNu64, &n);
    if (scan_result != 1) {
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