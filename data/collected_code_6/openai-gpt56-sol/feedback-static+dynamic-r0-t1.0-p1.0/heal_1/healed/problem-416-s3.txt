#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t maximum_sum(uint64_t n)
{
    if (n < 12) {
        return n;
    }

    uint64_t half = maximum_sum(n / 2);
    uint64_t third = maximum_sum(n / 3);
    uint64_t quarter = maximum_sum(n / 4);

    if (UINT64_MAX - half < third) {
        return UINT64_MAX;
    }

    uint64_t sum = half + third;

    if (UINT64_MAX - sum < quarter) {
        return UINT64_MAX;
    }

    sum += quarter;
    return sum > n ? sum : n;
}

int main(void)
{
    uintmax_t value;
    char extra;

    if (scanf("%" SCNuMAX " %c", &value, &extra) != 1) {
        return EXIT_FAILURE;
    }

    if (value > UINT64_MAX) {
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", maximum_sum((uint64_t)value));
    return EXIT_SUCCESS;
}