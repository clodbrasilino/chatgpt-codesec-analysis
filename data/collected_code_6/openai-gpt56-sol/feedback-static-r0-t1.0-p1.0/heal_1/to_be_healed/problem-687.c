#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uintmax_t gcd_recursive(uintmax_t a, uintmax_t b)
{
    return b == 0U ? a : gcd_recursive(b, a % b);
}

static uintmax_t magnitude(intmax_t value)
{
    return value < 0 ? (uintmax_t)(-(value + 1)) + 1U : (uintmax_t)value;
}

int main(void)
{
    intmax_t first;
    intmax_t second;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNdMAX " %" SCNdMAX, &first, &second) != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIuMAX "\n",
           gcd_recursive(magnitude(first), magnitude(second)));

    return EXIT_SUCCESS;
}