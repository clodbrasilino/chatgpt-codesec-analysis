#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static int sum_fourth_powers_even(uint32_t n, uint64_t *result)
{
    const uint64_t limit = 249U;

    if (result == NULL || n > limit) {
        return -1;
    }

    uint64_t sum = 0U;

    for (uint64_t i = 1U; i <= n; ++i) {
        uint64_t even = 2U * i;
        uint64_t square = even * even;
        sum += square * square;
    }

    *result = sum;
    return 0;
}

int main(void)
{
    uint32_t n;
    uint64_t sum;

    if (scanf("%" SCNu32, &n) != 1) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (sum_fourth_powers_even(n, &sum) != 0) {
        fputs("Input is out of range\n", stderr);
        return 1;
    }

    printf("%" PRIu64 "\n", sum);
    return 0;
}