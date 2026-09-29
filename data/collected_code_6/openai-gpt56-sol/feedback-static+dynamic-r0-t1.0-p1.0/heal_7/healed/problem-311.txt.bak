#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static uint32_t set_rightmost_unset_bit(uint32_t value)
{
    return value | (value + UINT32_C(1));
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