#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static uint32_t toggle_even_bits(uint32_t value)
{
    return value ^ UINT32_C(0x55555555);
}

int main(void)
{
    uint32_t value;

    if (scanf("%" SCNu32, &value) != 1) {
        return 1;
    }

    printf("%" PRIu32 "\n", toggle_even_bits(value));
    return 0;
}