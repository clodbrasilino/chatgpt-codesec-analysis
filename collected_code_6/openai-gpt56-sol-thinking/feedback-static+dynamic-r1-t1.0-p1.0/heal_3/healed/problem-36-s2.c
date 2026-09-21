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

static uint64_t power_mod(uint64_t base, uint64_t exponent,
                          uint64_t modulus)
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

    if (digit == NULL || denominator == UINT64_C(0) ||
        numerator >= denominator || position == UINT64_C(0)) {
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

static bool read_input(uint64_t values[3])
{
    unsigned char buffer[4096];
    uint64_t current = UINT64_C(0);
    size_t value_count = 0U;
    bool in_number = false;
    size_t bytes_read;

    if (values == NULL) {
        return false;
    }

    while ((bytes_read = fread(buffer, 1U, sizeof buffer, stdin)) != 0U) {
        size_t i;

        for (i = 0U; i < bytes_read; ++i) {
            unsigned char input = buffer[i];

            if (input >= (unsigned char)'0' &&
                input <= (unsigned char)'9') {
                uint64_t decimal_digit =
                    (uint64_t)(input - (unsigned char)'0');

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
            } else if (isspace((int)input) != 0) {
                if (in_number) {
                    values[value_count++] = current;
                    in_number = false;
                }
            } else {
                return false;
            }
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

    return value_count == 3U;
}

int main(void)
{
    uint64_t values[3];
    unsigned int digit;

    if (!read_input(values)) {
        return EXIT_FAILURE;
    }

    if (!find_nth_digit(values[0], values[1], values[2], &digit)) {
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