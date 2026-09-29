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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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