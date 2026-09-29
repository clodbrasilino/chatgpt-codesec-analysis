#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

static bool are_bits_unset(uint64_t value, size_t start, size_t end)
{
    const size_t bit_count = sizeof(value) * CHAR_BIT;

    if (start > end || end >= bit_count) {
        return false;
    }

    const size_t width = end - start + 1U;
    const uint64_t mask = width == bit_count
                              ? UINT64_MAX
                              : ((UINT64_C(1) << width) - UINT64_C(1)) << start;

    return (value & mask) == UINT64_C(0);
}

int main(void)
{
    uint64_t value = UINT64_C(0x100);
    size_t start = 0U;
    size_t end = 7U;

    if (are_bits_unset(value, start, end)) {
        puts("All bits in the range are unset.");
    } else {
        puts("At least one bit in the range is set, or the range is invalid.");
    }

    return 0;
}