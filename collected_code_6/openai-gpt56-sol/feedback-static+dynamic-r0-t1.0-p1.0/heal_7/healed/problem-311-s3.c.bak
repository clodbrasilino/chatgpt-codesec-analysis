#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static uint32_t set_leftmost_unset_bit(uint32_t value)
{
    if (value == 0U) {
        return UINT32_C(1);
    }

    uint32_t mask = UINT32_C(1) << (31U - (uint32_t)__builtin_clz(value));

    while (mask != 0U && (value & mask) != 0U) {
        mask >>= 1U;
    }

    return value | mask;
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