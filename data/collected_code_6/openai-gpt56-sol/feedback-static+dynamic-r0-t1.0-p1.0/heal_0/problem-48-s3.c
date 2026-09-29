#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint32_t set_odd_bits(uint32_t value)
{
    return value | UINT32_C(0xAAAAAAAA);
}

int main(void)
{
    uint32_t value;

    if (scanf("%" SCNu32, &value) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu32 "\n", set_odd_bits(value));
    return EXIT_SUCCESS;
}