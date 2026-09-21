#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_BUFFER_SIZE 4096U

typedef struct {
    FILE *stream;
    unsigned char buffer[INPUT_BUFFER_SIZE];
    size_t position;
    size_t length;
    int error;
    int end_of_file;
} Input;

static int input_get(Input *input)
{
    if (input == NULL || input->stream == NULL ||
        input->error || input->end_of_file) {
        return EOF;
    }

    if (input->position >= input->length) {
        input->length = fread(input->buffer, 1, sizeof input->buffer,
                              input->stream);
        input->position = 0;

        if (input->length == 0) {
            if (ferror(input->stream)) {
                input->error = 1;
            } else {
                input->end_of_file = 1;
            }

            return EOF;
        }
    }

    return (int)input->buffer[input->position++];
}

static int read_uint64(Input *input, uint64_t *value)
{
    uint64_t result = 0;
    int overflow = 0;
    int c;

    if (input == NULL || input->stream == NULL || value == NULL) {
        return 0;
    }

    do {
        c = input_get(input);
    } while (c != EOF && isspace((unsigned char)c));

    if (c < '0' || c > '9') {
        return 0;
    }

    do {
        uint64_t digit = (uint64_t)(c - '0');

        if (!overflow) {
            if (result > UINT64_MAX / UINT64_C(10) ||
                (result == UINT64_MAX / UINT64_C(10) &&
                 digit > UINT64_MAX % UINT64_C(10))) {
                overflow = 1;
            } else {
                result = result * UINT64_C(10) + digit;
            }
        }

        c = input_get(input);
    } while (c >= '0' && c <= '9');

    if (c != EOF && !isspace((unsigned char)c)) {
        return 0;
    }

    if (input->error || overflow) {
        return 0;
    }

    *value = result;
    return 1;
}

static int only_whitespace_remains(Input *input)
{
    int c;

    if (input == NULL || input->stream == NULL) {
        return 0;
    }

    while ((c = input_get(input)) != EOF) {
        if (!isspace((unsigned char)c)) {
            return 0;
        }
    }

    return !input->error;
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
    b %= modulus;

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

static uint64_t power_mod(uint64_t base, uint64_t exponent,
                          uint64_t modulus)
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

    for (i = 0; i < 10U; ++i) {
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

int main(void)
{
    Input input = {
        .stream = stdin,
        .buffer = {0},
        .position = 0,
        .length = 0,
        .error = 0,
        .end_of_file = 0
    };
    uint64_t numerator;
    uint64_t denominator;
    uint64_t position;
    unsigned int digit;

    if (!read_uint64(&input, &numerator) ||
        !read_uint64(&input, &denominator) ||
        !read_uint64(&input, &position) ||
        !only_whitespace_remains(&input)) {
        return EXIT_FAILURE;
    }

    if (!nth_fraction_digit(numerator, denominator, position, &digit)) {
        return EXIT_FAILURE;
    }

    if (printf("%u\n", digit) < 0 || fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}