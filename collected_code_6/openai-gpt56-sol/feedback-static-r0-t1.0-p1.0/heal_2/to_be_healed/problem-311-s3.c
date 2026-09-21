#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>

static uint32_t set_leftmost_unset_bit(uint32_t value)
{
    uint32_t mask = UINT32_C(1) << (sizeof(value) * CHAR_BIT - 1U);

    while (mask != 0U) {
        if ((value & mask) == 0U) {
            return value | mask;
        }
        mask >>= 1U;
    }

    return value;
}

int main(void)
{
    uint32_t value;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNu32, &value) != 1) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    printf("%" PRIu32 "\n", set_leftmost_unset_bit(value));
    return 0;
}