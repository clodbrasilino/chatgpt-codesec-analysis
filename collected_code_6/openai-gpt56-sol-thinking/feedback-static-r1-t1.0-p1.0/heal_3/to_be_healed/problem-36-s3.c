#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_BUFFER_SIZE 4096U

typedef struct {
    FILE *stream;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char buffer[INPUT_BUFFER_SIZE];
    size_t position;
    size_t length;
    int error;
} InputReader;

static int input_get(InputReader *reader)
{
    if (reader == NULL || reader->stream == NULL) {
        return EOF;
    }

    if (reader->position == reader->length) {
        reader->length = fread(
            reader->buffer,
            sizeof(reader->buffer[0]),
            INPUT_BUFFER_SIZE,
            reader->stream
        );
        reader->position = 0;

        if (reader->length == 0) {
            if (ferror(reader->stream)) {
                reader->error = 1;
            }
            return EOF;
        }
    }

    return (int)reader->buffer[reader->position++];
}

static int is_decimal_digit(int c)
{
    return c >= '0' && c <= '9';
}

static int is_input_whitespace(int c)
{
    return c == ' ' || c == '\t' || c == '\n' ||
           c == '\r' || c == '\f' || c == '\v';
}

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

    if (digit == NULL || denominator == 0 ||
        numerator >= denominator || position == 0) {
        return 0;
    }

    remainder = multiply_mod(
        numerator,
        power_mod(UINT64_C(10), position - UINT64_C(1), denominator),
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

static int read_uint64(InputReader *reader, uint64_t *value)
{
    uint64_t result = 0;
    int overflow = 0;
    int c;

    if (reader == NULL || value == NULL) {
        return 0;
    }

    do {
        c = input_get(reader);
    } while (c != EOF && is_input_whitespace(c));

    if (c == EOF || !is_decimal_digit(c)) {
        return 0;
    }

    do {
        unsigned int digit = (unsigned int)(c - '0');

        if (!overflow) {
            if (result > (UINT64_MAX - digit) / UINT64_C(10)) {
                overflow = 1;
            } else {
                result = result * UINT64_C(10) + digit;
            }
        }

        c = input_get(reader);
    } while (c != EOF && is_decimal_digit(c));

    if (c != EOF && !is_input_whitespace(c)) {
        return 0;
    }

    if (overflow || reader->error) {
        return 0;
    }

    *value = result;
    return 1;
}

static int only_whitespace_remains(InputReader *reader)
{
    int c;

    if (reader == NULL) {
        return 0;
    }

    while ((c = input_get(reader)) != EOF) {
        if (!is_input_whitespace(c)) {
            return 0;
        }
    }

    return !reader->error;
}

int main(void)
{
    InputReader reader = { stdin, { 0 }, 0, 0, 0 };
    uint64_t numerator;
    uint64_t denominator;
    uint64_t position;
    unsigned int digit;

    if (!read_uint64(&reader, &numerator) ||
        !read_uint64(&reader, &denominator) ||
        !read_uint64(&reader, &position) ||
        !only_whitespace_remains(&reader)) {
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