#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>

#define INPUT_LIMIT 4096U

static uint64_t modular_add(uint64_t left, uint64_t right, uint64_t modulus)
{
    if (left >= modulus - right) {
        return left - (modulus - right);
    }

    return left + right;
}

static uint64_t modular_multiply(uint64_t left, uint64_t right,
                                 uint64_t modulus)
{
    uint64_t result = 0;

    while (right != 0) {
        if ((right & UINT64_C(1)) != 0) {
            result = modular_add(result, left, modulus);
        }

        right >>= 1;

        if (right != 0) {
            left = modular_add(left, left, modulus);
        }
    }

    return result;
}

static uint64_t modular_power(uint64_t base, uint64_t exponent,
                              uint64_t modulus)
{
    uint64_t result = UINT64_C(1) % modulus;

    while (exponent != 0) {
        if ((exponent & UINT64_C(1)) != 0) {
            result = modular_multiply(result, base, modulus);
        }

        exponent >>= 1;

        if (exponent != 0) {
            base = modular_multiply(base, base, modulus);
        }
    }

    return result;
}

static bool find_nth_digit(uint64_t numerator, uint64_t denominator,
                           uint64_t position, unsigned int *digit)
{
    uint64_t remainder;
    uint64_t accumulated = 0;
    unsigned int result = 0;
    unsigned int i;

    if (digit == NULL || denominator == 0 || numerator >= denominator ||
        position == 0) {
        return false;
    }

    remainder = modular_multiply(
        numerator,
        modular_power(UINT64_C(10) % denominator,
                      position - UINT64_C(1), denominator),
        denominator
    );

    for (i = 0; i < 10; ++i) {
        if (accumulated >= denominator - remainder) {
            accumulated -= denominator - remainder;
            ++result;
        } else {
            accumulated += remainder;
        }
    }

    *digit = result;
    return true;
}

static bool parse_int64(const char **cursor, int64_t *value)
{
    const char *start;
    char *end;
    intmax_t parsed;

    if (cursor == NULL || *cursor == NULL || value == NULL) {
        return false;
    }

    start = *cursor;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0') {
        return false;
    }

    errno = 0;
    parsed = strtoimax(start, &end, 10);

    if (end == start || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return false;
    }

    *value = (int64_t)parsed;
    *cursor = end;
    return true;
}

static bool parse_input(const char *input, int64_t *numerator,
                        int64_t *denominator, int64_t *position)
{
    const char *cursor;

    if (input == NULL || numerator == NULL ||
        denominator == NULL || position == NULL) {
        return false;
    }

    cursor = input;

    if (!parse_int64(&cursor, numerator) ||
        !parse_int64(&cursor, denominator) ||
        !parse_int64(&cursor, position)) {
        return false;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    return *cursor == '\0';
}

static bool read_input_line(FILE *stream, char **output)
{
    char *buffer;
    size_t length = 0;
    int character;

    if (stream == NULL || output == NULL) {
        return false;
    }

    *output = NULL;

    buffer = malloc((size_t)INPUT_LIMIT + 1U);
    if (buffer == NULL) {
        return false;
    }

    while ((character = fgetc(stream)) != EOF) {
        if (character == '\0' || length == INPUT_LIMIT) {
            free(buffer);
            return false;
        }

        buffer[length++] = (char)character;

        if (character == '\n') {
            break;
        }
    }

    if (ferror(stream) || (character == EOF && length == 0)) {
        free(buffer);
        return false;
    }

    buffer[length] = '\0';
    *output = buffer;
    return true;
}

int main(void)
{
    char *input = NULL;
    int64_t numerator;
    int64_t denominator;
    int64_t position;
    unsigned int digit;

    if (!read_input_line(stdin, &input)) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!parse_input(input, &numerator, &denominator, &position)) {
        free(input);
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    free(input);

    if (numerator < 0 || denominator <= 0 || position <= 0 ||
        numerator >= denominator ||
        !find_nth_digit((uint64_t)numerator, (uint64_t)denominator,
                        (uint64_t)position, &digit)) {
        fprintf(stderr, "Invalid fraction or position\n");
        return EXIT_FAILURE;
    }

    if (printf("%u\n", digit) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}