#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>

static uint32_t set_leftmost_unset_bit(uint32_t value)
{
    uint32_t mask = UINT32_C(1) << (UINT32_WIDTH - 1);

    while (mask != 0U) {
        if ((value & mask) == 0U) {
            return value | mask;
        }
        mask >>= 1;
    }

    return value;
}

int main(void)
{
    char input[64];
    uintmax_t parsed;
    char trailing;

    if (fgets(input, sizeof input, stdin) == NULL ||
        sscanf(input, " %" SCNuMAX " %c", &parsed, &trailing) != 1 ||
        parsed > UINT32_MAX) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    uint32_t value = (uint32_t)parsed;
    printf("%" PRIu32 "\n", set_leftmost_unset_bit(value));

    return 0;
}