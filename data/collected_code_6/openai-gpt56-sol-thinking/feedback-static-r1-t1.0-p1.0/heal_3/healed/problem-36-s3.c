#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_BUFFER_SIZE 4096U

typedef struct {
    FILE *stream;
    unsigned char *buffer;
    size_t capacity;
    size_t position;
    size_t length;
    int error;
} InputReader;

static int input_reader_init(InputReader *reader, FILE *stream, size_t capacity)
{
    if (reader == NULL || stream == NULL || capacity == 0) {
        return 0;
    }

    reader->buffer = malloc(capacity);
    if (reader->buffer == NULL) {
        return 0;
    }

    reader->stream = stream;
    reader->capacity = capacity;
    reader->position = 0;
    reader->length = 0;
    reader->error = 0;

    return 1;
}

static void input_reader_destroy(InputReader *reader)
{
    if (reader == NULL) {
        return;
    }

    free(reader->buffer);
    reader->buffer = NULL;
    reader->stream = NULL;
    reader->capacity = 0;
    reader->position = 0;
    reader->length = 0;
    reader->error = 0;
}

static int input_get(InputReader *reader)
{
    if (reader == NULL || reader->stream == NULL ||
        reader->buffer == NULL || reader->capacity == 0) {
        return EOF;
    }

    if (reader->position >= reader->length) {
        reader->length = fread(
            reader->buffer,
            sizeof(*reader->buffer),
            reader->capacity,
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
    InputReader reader;
    uint64_t numerator;
    uint64_t denominator;
    uint64_t position;
    unsigned int digit;
    int status = EXIT_FAILURE;

    if (!input_reader_init(&reader, stdin, INPUT_BUFFER_SIZE)) {
        return EXIT_FAILURE;
    }

    if (!read_uint64(&reader, &numerator) ||
        !read_uint64(&reader, &denominator) ||
        !read_uint64(&reader, &position) ||
        !only_whitespace_remains(&reader)) {
        goto cleanup;
    }

    if (!nth_fraction_digit(numerator, denominator, position, &digit)) {
        goto cleanup;
    }

    if (printf("%u\n", digit) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    input_reader_destroy(&reader);
    return status;
}