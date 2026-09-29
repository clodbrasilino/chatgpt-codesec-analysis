#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

static bool all_set_bits_within_range(uint32_t value, unsigned int low, unsigned int high)
{
    const unsigned int width = 32U;

    if (low > high || high >= width) {
        return false;
    }

    const uint32_t lower_mask = (low == 0U) ? 0U : (UINT32_C(1) << low) - UINT32_C(1);
    const uint32_t upper_mask = (high == width - 1U)
        ? 0U
        : ~((UINT32_C(1) << (high + 1U)) - UINT32_C(1));
    const uint32_t outside_mask = lower_mask | upper_mask;

    return (value & outside_mask) == 0U;
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