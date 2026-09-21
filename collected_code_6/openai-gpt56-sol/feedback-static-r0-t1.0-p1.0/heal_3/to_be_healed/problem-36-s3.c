#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static int nth_fractional_digit(uint64_t numerator, uint64_t denominator,
                                uint64_t n, unsigned int *digit)
{
    uint64_t remainder;

    if (denominator == 0 || n == 0 || digit == NULL) {
        return -1;
    }

    remainder = numerator % denominator;

    for (uint64_t position = 0; position < n; ++position) {
        unsigned int quotient_digit = 0;

        for (unsigned int i = 0; i < 10; ++i) {
            if (remainder >= denominator - remainder) {
                remainder -= denominator - remainder;
                ++quotient_digit;
            } else {
                remainder += remainder;
            }
        }

        *digit = quotient_digit;
    }

    return 0;
}

int main(void)
{
    uint64_t numerator;
    uint64_t denominator;
    uint64_t n;
    unsigned int digit;
    int trailing;

    errno = 0;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNu64 " %" SCNu64 " %" SCNu64,
              &numerator, &denominator, &n) != 3 ||
        errno == ERANGE) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        trailing = getchar();
    } while (trailing == ' ' || trailing == '\t' ||
             trailing == '\n' || trailing == '\r' ||
             trailing == '\f' || trailing == '\v');

    if (trailing != EOF) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (nth_fractional_digit(numerator, denominator, n, &digit) != 0) {
        fputs("Unable to calculate digit\n", stderr);
        return 1;
    }

    printf("%u\n", digit);
    return 0;
}