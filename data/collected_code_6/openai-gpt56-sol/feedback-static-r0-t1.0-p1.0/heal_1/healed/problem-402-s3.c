#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>

static uint64_t gcd_u64(uint64_t a, uint64_t b)
{
    while (b != 0) {
        uint64_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static uint64_t add_mod(uint64_t a, uint64_t b, uint64_t modulus)
{
    return (a >= modulus - b) ? a - (modulus - b) : a + b;
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

static int ncr_mod(uint64_t n, uint64_t r, uint64_t modulus,
                   uint64_t *result)
{
    uint64_t value = 1;

    if (result == NULL || modulus == 0) {
        return 0;
    }

    if (r > n) {
        *result = 0;
        return 1;
    }

    if (r > n - r) {
        r = n - r;
    }

    for (uint64_t i = 1; i <= r; ++i) {
        uint64_t numerator = n - r + i;
        uint64_t denominator = i;
        uint64_t divisor;
        uint64_t candidate;

        divisor = gcd_u64(numerator, denominator);
        numerator /= divisor;
        denominator /= divisor;

        divisor = gcd_u64(value, denominator);
        value /= divisor;
        denominator /= divisor;

        candidate = numerator;

        while (denominator != 1) {
            uint64_t quotient;
            uint64_t limit;

            divisor = gcd_u64(candidate, denominator);
            candidate /= divisor;
            denominator /= divisor;

            if (denominator == 1) {
                break;
            }

            quotient = candidate / numerator;
            limit = UINT64_MAX / numerator;

            if (quotient >= limit) {
                return 0;
            }

            candidate += numerator;
        }

        value = multiply_mod(value, candidate % modulus, modulus);
    }

    *result = value % modulus;
    return 1;
}

static int read_u64(uint64_t *value)
{
    int ch;
    uint64_t result = 0;
    int have_digit = 0;

    if (value == NULL) {
        return 0;
    }

    do {
        ch = getchar();
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == '+') {
        ch = getchar();
    } else if (ch == '-') {
        return 0;
    }

    while (ch != EOF && isdigit((unsigned char)ch)) {
        unsigned int digit = (unsigned int)(ch - '0');

        have_digit = 1;

        if (result > (UINT64_MAX - digit) / 10) {
            return 0;
        }

        result = result * 10 + digit;
        ch = getchar();
    }

    if (!have_digit) {
        return 0;
    }

    if (ch != EOF && !isspace((unsigned char)ch)) {
        return 0;
    }

    *value = result;
    return 1;
}

static int only_whitespace_remains(void)
{
    int ch;

    while ((ch = getchar()) != EOF) {
        if (!isspace((unsigned char)ch)) {
            return 0;
        }
    }

    return !ferror(stdin);
}

int main(void)
{
    uint64_t n;
    uint64_t r;
    uint64_t modulus;
    uint64_t result;

    errno = 0;

    if (!read_u64(&n) ||
        !read_u64(&r) ||
        !read_u64(&modulus) ||
        !only_whitespace_remains()) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (!ncr_mod(n, r, modulus, &result)) {
        fputs("Computation failed\n", stderr);
        return 1;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return 1;
    }

    return 0;
}