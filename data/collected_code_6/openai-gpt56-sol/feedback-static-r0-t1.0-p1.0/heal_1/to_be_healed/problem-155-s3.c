#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static uint32_t toggle_even_bits(uint32_t value)
{
    return value ^ UINT32_C(0x55555555);
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

    if (printf("%" PRIu32 "\n", toggle_even_bits(value)) < 0) {
        return 1;
    }

    return 0;
}