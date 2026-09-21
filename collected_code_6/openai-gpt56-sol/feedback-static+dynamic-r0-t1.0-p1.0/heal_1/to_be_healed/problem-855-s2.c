#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

static bool has_even_parity(uint64_t value)
{
    bool parity = false;

    while (value != UINT64_C(0)) {
        parity = !parity;
        value &= value - UINT64_C(1);
    }

    return !parity;
}

int main(void)
{
    uint64_t value;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNu64, &value) != 1) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    puts(has_even_parity(value) ? "Even parity" : "Odd parity");
    return 0;
}