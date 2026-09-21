#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static uint32_t toggle_inner_bits(uint32_t number)
{
    const uint32_t inner_mask = (UINT32_MAX >> 1U) & ~UINT32_C(1);
    return number ^ inner_mask;
}

int main(void)
{
    char input[64];
    uint32_t number;
    char extra;

    if (fgets(input, sizeof input, stdin) == NULL ||
        sscanf(input, " %" SCNu32 " %c", &number, &extra) != 1) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    printf("%" PRIu32 "\n", toggle_inner_bits(number));
    return 0;
}