#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static uint32_t set_rightmost_unset_bit(uint32_t value)
{
    if (value == 0) {
        return value;
    }

    uint32_t bit = UINT32_C(1) << (31U - (uint32_t)__builtin_clz(value));

    return value | (bit - UINT32_C(1));
}

int main(void)
{
    uint32_t value;

    if (scanf("%" SCNu32, &value) != 1) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    printf("%" PRIu32 "\n", set_rightmost_unset_bit(value));
    return 0;
}