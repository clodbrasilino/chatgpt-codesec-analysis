#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint32_t get_rightmost_set_bit_position(uint32_t value)
{
    uint32_t position = 0;

    while (value != 0U) {
        ++position;
        if ((value & UINT32_C(1)) != 0U) {
            return position;
        }
        value >>= 1U;
    }

    return 0U;
}

int main(void)
{
    uint32_t value;

    if (scanf("%" SCNu32, &value) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu32 "\n", get_rightmost_set_bit_position(value));

    return EXIT_SUCCESS;
}