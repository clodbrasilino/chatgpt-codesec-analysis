#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

static int sum_fifth_powers_even(uint64_t n, uint64_t *result)
{
    const uint64_t max_n = 9103U;
    __uint128_t sum = 0U;

    if (result == NULL || n > max_n) {
        return -1;
    }

    for (uint64_t i = 1U; i <= n; ++i) {
        __uint128_t value = (__uint128_t)2U * i;
        sum += value * value * value * value * value;
    }

    *result = (uint64_t)sum;
    return 0;
}

int main(void)
{
    uint64_t n;
    uint64_t sum;

    errno = 0;
    if (scanf("%" SCNu64, &n) != 1 || errno != 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (sum_fifth_powers_even(n, &sum) != 0) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}