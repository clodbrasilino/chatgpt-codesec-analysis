#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static uint32_t set_leftmost_unset_bit(uint32_t value)
{
    for (uint32_t mask = UINT32_C(1) << 31; mask != 0; mask >>= 1) {
        if ((value & mask) == 0) {
            return value | mask;
        }
    }

    return value;
}

int main(void)
{
    uint32_t value;

    if (scanf("%" SCNu32, &value) != 1) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    printf("%" PRIu32 "\n", set_leftmost_unset_bit(value));
    return 0;
}