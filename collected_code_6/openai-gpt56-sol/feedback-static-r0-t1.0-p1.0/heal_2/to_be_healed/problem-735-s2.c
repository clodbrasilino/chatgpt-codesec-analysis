#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>

static uint32_t toggle_inner_bits(uint32_t number)
{
    const unsigned int bit_count = sizeof(number) * CHAR_BIT;

    if (bit_count <= 2U) {
        return number;
    }

    const uint32_t inner_mask = (UINT32_MAX >> 1U) & ~UINT32_C(1);
    return number ^ inner_mask;
}

int main(void)
{
    uint32_t number;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNu32, &number) != 1) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    printf("%" PRIu32 "\n", toggle_inner_bits(number));
    return 0;
}