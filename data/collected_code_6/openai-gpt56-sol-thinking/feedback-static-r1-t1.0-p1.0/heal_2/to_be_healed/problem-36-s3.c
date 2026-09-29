#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t add_mod(uint64_t a, uint64_t b, uint64_t modulus)
{
    if (a >= modulus - b) {
        return a - (modulus - b);
    }

    return a + b;
}

static uint64_t multiply_mod(uint64_t a, uint64_t b, uint64_t modulus)
{
    uint64_t result = 0;

    a %= modulus;

    while (b != 0) {
        if ((b & UINT64_C(1)) != 0) {
            result = add_mod(result, a, modulus);
        }

        b >>= 1;

        if (b != 0) {
            a = add_mod(a, a, modulus);
        }
    }

    return result;
}

static uint64_t power_mod(uint64_t base, uint64_t exponent, uint64_t modulus)
{
    uint64_t result = UINT64_C(1) % modulus;

    base %= modulus;

    while (exponent != 0) {
        if ((exponent & UINT64_C(1)) != 0) {
            result = multiply_mod(result, base, modulus);
        }

        exponent >>= 1;

        if (exponent != 0) {
            base = multiply_mod(base, base, modulus);
        }
    }

    return result;
}

static int nth_fraction_digit(uint64_t numerator, uint64_t denominator,
                              uint64_t position, unsigned int *digit)
{
    uint64_t remainder;
    uint64_t accumulator = 0;
    unsigned int quotient = 0;
    unsigned int i;

    if (digit == NULL || denominator == 0 || numerator >= denominator ||
        position == 0) {
        return 0;
    }

    remainder = multiply_mod(
        numerator,
        power_mod(UINT64_C(10), position - 1, denominator),
        denominator
    );

    for (i = 0; i < 10; ++i) {
        if (accumulator >= denominator - remainder) {
            accumulator -= denominator - remainder;
            ++quotient;
        } else {
            accumulator += remainder;
        }
    }

    *digit = quotient;
    return 1;
}

static int read_uint64(FILE *stream, uint64_t *value)
{
    uint64_t result = 0;
    int overflow = 0;
    int c;

    if (stream == NULL || value == NULL) {
        return 0;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = fgetc(stream);
    } while (c != EOF && isspace((unsigned char)c));

    if (c == EOF || !isdigit((unsigned char)c)) {
        return 0;
    }

    do {
        unsigned int digit = (unsigned int)(c - '0');

        if (result > (UINT64_MAX - digit) / UINT64_C(10)) {
            overflow = 1;
        } else if (!overflow) {
            result = result * UINT64_C(10) + digit;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = fgetc(stream);
    } while (c != EOF && isdigit((unsigned char)c));

    if (c != EOF && !isspace((unsigned char)c)) {
        return 0;
    }

    if (overflow || ferror(stream)) {
        return 0;
    }

    *value = result;
    return 1;
}

static int only_whitespace_remains(FILE *stream)
{
    int c;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = fgetc(stream)) != EOF) {
        if (!isspace((unsigned char)c)) {
            return 0;
        }
    }

    return !ferror(stream);
}

int main(void)
{
    uint64_t numerator;
    uint64_t denominator;
    uint64_t position;
    unsigned int digit;

    if (!read_uint64(stdin, &numerator) ||
        !read_uint64(stdin, &denominator) ||
        !read_uint64(stdin, &position) ||
        !only_whitespace_remains(stdin)) {
        return EXIT_FAILURE;
    }

    if (!nth_fraction_digit(numerator, denominator, position, &digit)) {
        return EXIT_FAILURE;
    }

    if (printf("%u\n", digit) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}