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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    char trailing;
    uint64_t numerator;
    uint64_t denominator;
    uint64_t n;
    unsigned int digit;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    errno = 0;
    if (sscanf(input, " %" SCNu64 " %" SCNu64 " %" SCNu64 " %c",
               &numerator, &denominator, &n, &trailing) != 3 ||
        errno == ERANGE) {
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