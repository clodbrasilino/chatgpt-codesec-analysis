#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static uint32_t toggle_even_bits(uint32_t value)
{
    return value ^ UINT32_C(0x55555555);
}

int main(void)
{
    char input[64];
    uint32_t value;
    char extra;

    if (fgets(input, sizeof input, stdin) == NULL ||
        sscanf(input, "%" SCNu32 " %c", &value, &extra) != 1) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (printf("%" PRIu32 "\n", toggle_even_bits(value)) < 0) {
        return 1;
    }

    return 0;
}