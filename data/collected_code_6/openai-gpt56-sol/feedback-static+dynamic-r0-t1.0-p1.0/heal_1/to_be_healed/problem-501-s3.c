#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uintmax_t magnitude(intmax_t value)
{
    return value < 0 ? (uintmax_t)(-(value + 1)) + 1U : (uintmax_t)value;
}

static uintmax_t greatest_common_divisor(intmax_t first, intmax_t second)
{
    uintmax_t a = magnitude(first);
    uintmax_t b = magnitude(second);

    while (b != 0U) {
        const uintmax_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
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

    if (first == 0 && second == 0) {
        fputs("The greatest common divisor of zero and zero is undefined\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIuMAX "\n", greatest_common_divisor(first, second)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}