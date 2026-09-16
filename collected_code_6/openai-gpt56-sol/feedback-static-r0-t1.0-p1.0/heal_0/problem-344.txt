#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static uint64_t integer_sqrt(uint64_t value)
{
    uint64_t result = 0;
    uint64_t bit = UINT64_C(1) << 62;

    while (bit > value) {
        bit >>= 2;
    }

    while (bit != 0) {
        if (value >= result + bit) {
            value -= result + bit;
            result = (result >> 1) + bit;
        } else {
            result >>= 1;
        }
        bit >>= 2;
    }

    return result;
}

static uint64_t count_odd_factors_in_range(uint64_t lower, uint64_t upper)
{
    if (lower > upper) {
        return 0;
    }

    return (upper - lower + 1) -
           (integer_sqrt(upper) - (lower == 0 ? 0 : integer_sqrt(lower - 1)));
}

int main(void)
{
    uint64_t lower;
    uint64_t upper;

    if (scanf("%" SCNu64 " %" SCNu64, &lower, &upper) != 2 || lower > upper) {
        return 1;
    }

    printf("%" PRIu64 "\n", count_odd_factors_in_range(lower, upper));
    return 0;
}