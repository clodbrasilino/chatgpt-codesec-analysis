#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>

static uint32_t toggle_inner_bits(uint32_t number)
{
    const unsigned int bit_count = sizeof(number) * CHAR_BIT;
    const uint32_t inner_mask = (UINT32_MAX >> 1U) & ~UINT32_C(1);

    if (bit_count <= 2U) {
        return number;
    }

    return number ^ inner_mask;
}

int main(void)
{
    uint32_t number;

    if (scanf("%" SCNu32, &number) != 1) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    printf("%" PRIu32 "\n", toggle_inner_bits(number));
    return 0;
}