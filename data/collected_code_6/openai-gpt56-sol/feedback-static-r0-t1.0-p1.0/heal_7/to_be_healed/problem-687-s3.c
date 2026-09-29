#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uintmax_t magnitude(intmax_t value)
{
    if (value >= 0) {
        return (uintmax_t)value;
    }

    return (uintmax_t)(-(value + INTMAX_C(1))) + UINTMAX_C(1);
}

static uintmax_t gcd(uintmax_t a, uintmax_t b)
{
    while (b != 0) {
        uintmax_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static int read_intmax(intmax_t *value)
{
    int ch;
    intmax_t result = 0;
    uintmax_t limit;
    uintmax_t accumulated = 0;
    int negative = 0;
    int has_digit = 0;
    int invalid = 0;

    if (value == NULL) {
        return 0;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return 0;
    }

    if (ch == '+' || ch == '-') {
        negative = ch == '-';
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    limit = negative
        ? (uintmax_t)INTMAX_MAX + UINTMAX_C(1)
        : (uintmax_t)INTMAX_MAX;

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (isdigit((unsigned char)ch)) {
            unsigned int digit = (unsigned int)(ch - '0');

            has_digit = 1;

            if (!invalid) {
                if (accumulated > (limit - digit) / UINTMAX_C(10)) {
                    invalid = 1;
                } else {
                    accumulated = accumulated * UINTMAX_C(10) + digit;
                }
            }
        } else {
            invalid = 1;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    if (ferror(stdin) || !has_digit || invalid) {
        return 0;
    }

    if (negative) {
        if (accumulated == (uintmax_t)INTMAX_MAX + UINTMAX_C(1)) {
            result = INTMAX_MIN;
        } else {
            result = -(intmax_t)accumulated;
        }
    } else {
        result = (intmax_t)accumulated;
    }

    *value = result;
    return 1;
}

static int only_whitespace_remains(void)
{
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF) {
        if (!isspace((unsigned char)ch)) {
            return 0;
        }
    }

    return !ferror(stdin);
}

int main(void)
{
    intmax_t first;
    intmax_t second;

    if (!read_intmax(&first) ||
        !read_intmax(&second) ||
        !only_whitespace_remains()) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIuMAX "\n",
               gcd(magnitude(first), magnitude(second))) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}