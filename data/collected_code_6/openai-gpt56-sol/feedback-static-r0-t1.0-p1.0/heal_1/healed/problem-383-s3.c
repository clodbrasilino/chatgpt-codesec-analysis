#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static uint32_t toggle_odd_bits(uint32_t value)
{
    return value ^ UINT32_C(0xAAAAAAAA);
}

int main(void)
{
    uint32_t value;
    char extra;

    if (scanf("%" SCNu32 " %c", &value, &extra) != 1) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    printf("%" PRIu32 "\n", toggle_odd_bits(value));
    return 0;
}