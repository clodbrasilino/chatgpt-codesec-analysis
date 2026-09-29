#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static uint32_t toggle_odd_bits(uint32_t value)
{
    return value ^ UINT32_C(0xAAAAAAAA);
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[64];
    uint32_t value;
    char extra;

    if (fgets(input, sizeof input, stdin) == NULL ||
        sscanf(input, "%" SCNu32 " %c", &value, &extra) != 1) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    printf("%" PRIu32 "\n", toggle_odd_bits(value));
    return 0;
}