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
    uint64_t result = UINT64_C(0);

    a %= modulus;

    while (b != UINT64_C(0)) {
        if ((b & UINT64_C(1)) != UINT64_C(0)) {
            result = add_mod(result, a, modulus);
        }

        b >>= 1;

        if (b != UINT64_C(0)) {
            a = add_mod(a, a, modulus);
        }
    }

    return result;
}

static uint64_t power_mod(uint64_t base, uint64_t exponent, uint64_t modulus)
{
    uint64_t result = UINT64_C(1) % modulus;

    base %= modulus;

    while (exponent != UINT64_C(0)) {
        if ((exponent & UINT64_C(1)) != UINT64_C(0)) {
            result = multiply_mod(result, base, modulus);
        }

        exponent >>= 1;

        if (exponent != UINT64_C(0)) {
            base = multiply_mod(base, base, modulus);
        }
    }

    return result;
}

static bool find_nth_digit(uint64_t numerator, uint64_t denominator,
                           uint64_t position, unsigned int *digit)
{
    uint64_t remainder;
    uint64_t accumulated = UINT64_C(0);
    unsigned int quotient = 0U;
    unsigned int i;

    if (digit == NULL ||
        denominator == UINT64_C(0) ||
        numerator >= denominator ||
        position == UINT64_C(0)) {
        return false;
    }

    remainder = multiply_mod(
        numerator,
        power_mod(UINT64_C(10), position - UINT64_C(1), denominator),
        denominator
    );

    for (i = 0U; i < 10U; ++i) {
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

static bool read_input(uint64_t *first, uint64_t *second, uint64_t *third)
{
    uint64_t values[3] = {
        UINT64_C(0),
        UINT64_C(0),
        UINT64_C(0)
    };
    uint64_t current = UINT64_C(0);
    size_t value_count = 0U;
    bool in_number = false;
    int character;

    if (first == NULL || second == NULL || third == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF) {
        if (character >= '0' && character <= '9') {
            uint64_t decimal_digit = (uint64_t)(character - '0');

            if (!in_number) {
                if (value_count >= 3U) {
                    return false;
                }

                current = UINT64_C(0);
                in_number = true;
            }

            if (current >
                (UINT64_MAX - decimal_digit) / UINT64_C(10)) {
                return false;
            }

            current = current * UINT64_C(10) + decimal_digit;
        } else if (isspace((unsigned char)character) != 0) {
            if (in_number) {
                values[value_count++] = current;
                in_number = false;
            }
        } else {
            return false;
        }
    }

    if (ferror(stdin) != 0) {
        return false;
    }

    if (in_number) {
        if (value_count >= 3U) {
            return false;
        }

        values[value_count++] = current;
    }

    if (value_count != 3U) {
        return false;
    }

    *first = values[0];
    *second = values[1];
    *third = values[2];

    return true;
}

int main(void)
{
    uint64_t numerator;
    uint64_t denominator;
    uint64_t position;
    unsigned int digit;

    if (!read_input(&numerator, &denominator, &position)) {
        return EXIT_FAILURE;
    }

    if (!find_nth_digit(numerator, denominator, position, &digit)) {
        return EXIT_FAILURE;
    }

    if (printf("%u\n", digit) < 0) {
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}