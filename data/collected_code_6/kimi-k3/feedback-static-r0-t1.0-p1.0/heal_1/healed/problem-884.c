#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>

bool bits_in_range(uint32_t value, uint32_t low, uint32_t high)
{
    if (low > high || high >= 32) {
        return false;
    }
    uint32_t mask = (UINT32_C(1) << (high - low + 1)) - 1;
    return ((value >> low) & mask) == mask;
}

int main(void)
{
    uint32_t value = 0x3C;
    uint32_t low = 2;
    uint32_t high = 5;
    if (bits_in_range(value, low, high)) {
        printf("All bits in range [%u, %u] are set.\n", low, high);
    } else {
        printf("Not all bits in range [%u, %u] are set.\n", low, high);
    }
    return 0;
}