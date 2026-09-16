#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>

static bool all_set_bits_within_range(uint32_t value, unsigned int low, unsigned int high)
{
    uint32_t range_mask;

    if (low > high || high >= 32U) {
        return false;
    }

    range_mask = (UINT32_MAX << low) & (UINT32_MAX >> (31U - high));
    return (value & ~range_mask) == 0U;
}

int main(void)
{
    uint32_t value;
    unsigned int low;
    unsigned int high;

    if (scanf("%" SCNu32 " %u %u", &value, &low, &high) != 3) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    puts(all_set_bits_within_range(value, low, high) ? "true" : "false");
    return 0;
}