#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static uint32_t toggle_inner_bits(uint32_t value)
{
    if (value <= UINT32_C(1)) {
        return value;
    }

    uint32_t highest_bit = UINT32_C(1);

    while (highest_bit <= value / UINT32_C(2)) {
        highest_bit <<= 1;
    }

    return value ^ (highest_bit - UINT32_C(2));
}

int main(void)
{
    char input[64];
    uint32_t value;
    char extra;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (sscanf(input, " %" SCNu32 " %c", &value, &extra) != 1) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (printf("%" PRIu32 "\n", toggle_inner_bits(value)) < 0) {
        return 1;
    }

    return 0;
}