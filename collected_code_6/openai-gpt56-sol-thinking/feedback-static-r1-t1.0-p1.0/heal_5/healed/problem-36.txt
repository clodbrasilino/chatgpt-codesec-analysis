#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_LENGTH 4096U

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

    base %= modulus;

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
        modular_power(UINT64_C(10) % denominator, position - 1, denominator),
        denominator
    );

    for (i = 0; i < 10U; ++i) {
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

static bool read_input_line(FILE *stream, char *buffer, size_t capacity)
{
    size_t length = 0;
    int character;

    if (stream == NULL || buffer == NULL || capacity < 2U) {
        return false;
    }

    while ((character = fgetc(stream)) != EOF) {
        if (character == 0) {
            return false;
        }

        if (length >= capacity - 1U) {
            return false;
        }

        buffer[length++] = (char)(unsigned char)character;

        if (character == '\n') {
            break;
        }
    }

    if (ferror(stream) != 0 || length == 0U) {
        return false;
    }

    buffer[length] = '\0';
    return true;
}

static void skip_whitespace(char **text)
{
    while (isspace((unsigned char)**text) != 0) {
        ++(*text);
    }
}

static bool parse_int64(char **text, int64_t *value)
{
    char *end;
    intmax_t parsed;

    if (text == NULL || *text == NULL || value == NULL) {
        return false;
    }

    errno = 0;
    parsed = strtoimax(*text, &end, 10);

    if (end == *text || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return false;
    }

    *value = (int64_t)parsed;
    *text = end;
    return true;
}

int main(void)
{
    char *input;
    char *cursor;
    int64_t numerator;
    int64_t denominator;
    int64_t position;
    unsigned int digit;
    int status = EXIT_FAILURE;

    input = malloc((size_t)MAX_INPUT_LENGTH + 1U);
    if (input == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (!read_input_line(stdin, input, (size_t)MAX_INPUT_LENGTH + 1U)) {
        fprintf(stderr, "Invalid input\n");
        goto cleanup;
    }

    cursor = input;
    skip_whitespace(&cursor);

    if (!parse_int64(&cursor, &numerator) ||
        isspace((unsigned char)*cursor) == 0) {
        fprintf(stderr, "Invalid input\n");
        goto cleanup;
    }

    skip_whitespace(&cursor);

    if (!parse_int64(&cursor, &denominator) ||
        isspace((unsigned char)*cursor) == 0) {
        fprintf(stderr, "Invalid input\n");
        goto cleanup;
    }

    skip_whitespace(&cursor);

    if (!parse_int64(&cursor, &position)) {
        fprintf(stderr, "Invalid input\n");
        goto cleanup;
    }

    skip_whitespace(&cursor);

    if (*cursor != '\0') {
        fprintf(stderr, "Invalid input\n");
        goto cleanup;
    }

    if (numerator < 0 || denominator <= 0 || position <= 0 ||
        numerator >= denominator ||
        !find_nth_digit((uint64_t)numerator, (uint64_t)denominator,
                        (uint64_t)position, &digit)) {
        fprintf(stderr, "Invalid fraction or position\n");
        goto cleanup;
    }

    if (printf("%u\n", digit) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(input);
    return status;
}