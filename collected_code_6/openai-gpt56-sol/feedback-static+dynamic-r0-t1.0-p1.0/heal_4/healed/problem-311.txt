#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static uint32_t set_rightmost_unset_bit(uint32_t value)
{
    return value | (value + UINT32_C(1));
}

int main(void)
{
    char input[64];
    uint32_t value;
    char extra;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return 1;
    }

    if (sscanf(input, " %" SCNu32 " %c", &value, &extra) != 1) {
        return 1;
    }

    printf("%" PRIu32 "\n", set_rightmost_unset_bit(value));
    return 0;
}