#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static int cube_sum_even(uint64_t n, uint64_t *result)
{
    uint64_t a;
    uint64_t b;

    if (result == NULL || n > 55108U) {
        return 0;
    }

    a = n * (n + 1U);
    b = a / 2U;
    *result = 8U * b * b;

    return 1;
}

int main(void)
{
    uint64_t n;
    uint64_t sum;

    if (scanf("%" SCNu64, &n) != 1) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (!cube_sum_even(n, &sum)) {
        fputs("Input is too large\n", stderr);
        return 1;
    }

    printf("%" PRIu64 "\n", sum);
    return 0;
}