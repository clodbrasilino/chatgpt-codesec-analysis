#include <ctype.h>
#include <stdbool.h>
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

    while (b != 0) {
        if ((b & 1U) != 0) {
            result = add_mod(result, a, modulus);
        }

        b >>= 1U;

        if (b != 0) {
            a = add_mod(a, a, modulus);
        }
    }

    return result;
}

static uint64_t power_mod(uint64_t base, uint64_t exponent, uint64_t modulus)
{
    uint64_t result = 1U % modulus;

    base %= modulus;

    while (exponent != 0) {
        if ((exponent & 1U) != 0) {
            result = multiply_mod(result, base, modulus);
        }

        exponent >>= 1U;

        if (exponent != 0) {
            base = multiply_mod(base, base, modulus);
        }
    }

    return result;
}

bool find_nth_digit(uint64_t numerator, uint64_t denominator,
                    uint64_t position, unsigned int *digit)
{
    uint64_t remainder;
    uint64_t accumulated = 0;
    unsigned int quotient = 0;
    unsigned int i;

    if (digit == NULL || denominator == 0 || numerator >= denominator ||
        position == 0) {
        return false;
    }

    remainder = multiply_mod(
        numerator,
        power_mod(10U, position - 1U, denominator),
        denominator
    );

    for (i = 0; i < 10U; ++i) {
        if (accumulated >= denominator - remainder) {
            accumulated -= denominator - remainder;
            ++quotient;
        } else {
            accumulated += remainder;
        }
    }

    *digit = quotient;
    return true;
}

static bool read_uint64(uint64_t *value)
{
    uint64_t result = 0;
    int character;

    if (value == NULL) {
        return false;
    }

    do {
        character = getchar();
    } while (character != EOF && isspace((unsigned char)character));

    if (character < '0' || character > '9') {
        return false;
    }

    do {
        unsigned int digit = (unsigned int)(character - '0');

        if (result > (UINT64_MAX - digit) / 10U) {
            return false;
        }

        result = result * 10U + digit;
        character = getchar();
    } while (character >= '0' && character <= '9');

    if (character != EOF && !isspace((unsigned char)character)) {
        return false;
    }

    *value = result;
    return true;
}

static bool only_whitespace_remaining(void)
{
    int character;

    while ((character = getchar()) != EOF) {
        if (!isspace((unsigned char)character)) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    uint64_t numerator;
    uint64_t denominator;
    uint64_t position;
    unsigned int digit;

    if (!read_uint64(&numerator) ||
        !read_uint64(&denominator) ||
        !read_uint64(&position) ||
        !only_whitespace_remaining()) {
        return EXIT_FAILURE;
    }

    if (!find_nth_digit(numerator, denominator, position, &digit)) {
        return EXIT_FAILURE;
    }

    if (printf("%u\n", digit) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}