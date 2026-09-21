#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>

static uint32_t set_leftmost_unset_bit(uint32_t value)
{
    /* Possible weaknesses found:
     *  use of undeclared identifier 'UINT32_WIDTH'
     *  'UINT32_WIDTH' undeclared (first use in this function); did you mean 'UINT_WIDTH'?
     *  each undeclared identifier is reported only once for each function it appears in
     */
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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