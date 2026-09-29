#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_fourth_powers_even(uint64_t n, uint64_t *result)
{
    if (result == NULL || n > UINT64_C(7131)) {
        return 0;
    }

    uint64_t sum = 0;

    for (uint64_t i = 1; i <= n; ++i) {
        uint64_t even = 2 * i;
        uint64_t square = even * even;
        uint64_t fourth_power = square * square;

        if (UINT64_MAX - sum < fourth_power) {
            return 0;
        }

        sum += fourth_power;
    }

    *result = sum;
    return 1;
}

int main(void)
{
    uint64_t n;
    uint64_t result;

    if (scanf("%" SCNu64, &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!sum_fourth_powers_even(n, &result)) {
        fprintf(stderr, "Result exceeds the supported range\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}