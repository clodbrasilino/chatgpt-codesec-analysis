#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static int sum_fifth_powers(uint64_t n, uint64_t *result)
{
    __uint128_t value;
    __uint128_t square;

    if (result == NULL) {
        return -1;
    }

    value = n;
    value *= n + 1U;
    square = (2U * (__uint128_t)n * n) + (2U * (__uint128_t)n) - 1U;
    value *= square;
    value /= 12U;

    if (value > UINT64_MAX) {
        return -1;
    }

    *result = (uint64_t)value;
    return 0;
}

int main(void)
{
    uint64_t n;
    uint64_t sum;

    if (scanf("%" SCNu64, &n) != 1) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (sum_fifth_powers(n, &sum) != 0) {
        fputs("Result out of range\n", stderr);
        return 1;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return 1;
    }

    return 0;
}