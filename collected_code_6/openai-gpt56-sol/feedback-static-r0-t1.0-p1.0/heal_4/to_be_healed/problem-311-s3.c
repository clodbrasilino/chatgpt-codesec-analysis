#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static uint32_t set_leftmost_unset_bit(uint32_t value)
{
    uint32_t mask = UINT32_C(1) << 31;

    while (mask != 0) {
        if ((value & mask) == 0) {
            return value | mask;
        }
        mask >>= 1;
    }

    return value;
}

int main(void)
{
    uintmax_t parsed;
    char trailing;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf(" %" SCNuMAX, &parsed) != 1 ||
        parsed > UINT32_MAX ||
        scanf(" %c", &trailing) == 1) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    uint32_t value = (uint32_t)parsed;
    printf("%" PRIu32 "\n", set_leftmost_unset_bit(value));

    return 0;
}