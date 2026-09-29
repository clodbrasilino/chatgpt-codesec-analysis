#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>

static bool are_bits_unset(uint32_t value, unsigned int start, unsigned int end)
{
    const unsigned int bit_count = 32U;

    if (start > end || end >= bit_count) {
        return false;
    }

    uint32_t mask = UINT32_MAX >> (bit_count - (end - start + 1U));
    mask <<= start;

    return (value & mask) == 0U;
}

int main(void)
{
    uint32_t value;
    unsigned int start;
    unsigned int end;

    if (scanf("%" SCNu32 " %u %u", &value, &start, &end) != 3) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (start > end || end >= 32U) {
        fputs("Invalid range\n", stderr);
        return 1;
    }

    puts(are_bits_unset(value, start, end)
             ? "All bits are unset"
             : "Not all bits are unset");

    return 0;
}