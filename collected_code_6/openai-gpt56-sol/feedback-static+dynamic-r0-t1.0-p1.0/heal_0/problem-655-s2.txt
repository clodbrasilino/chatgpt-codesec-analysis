#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static int sum_of_fifth_powers(uint64_t n, uint64_t *result)
{
    const uint64_t maximum_n = 1388;
    __uint128_t sum = 0;

    if (result == NULL || n > maximum_n) {
        return -1;
    }

    for (uint64_t i = 1; i <= n; ++i) {
        __uint128_t value = i;
        sum += value * value * value * value * value;
    }

    *result = (uint64_t)sum;
    return 0;
}

int main(void)
{
    uint64_t n;
    uint64_t result;

    if (scanf("%" SCNu64, &n) != 1) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (sum_of_fifth_powers(n, &result) != 0) {
        fputs("Input is too large\n", stderr);
        return 1;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return 1;
    }

    return 0;
}