#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 4096U
#define INITIAL_INPUT_CAPACITY 128U

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
        modular_power(UINT64_C(10) % denominator, position - 1, denominator),
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

static bool read_input_line(FILE *stream, char **line)
{
    size_t capacity = INITIAL_INPUT_CAPACITY;
    size_t length = 0;
    char *buffer;
    int ch = EOF;

    if (stream == NULL || line == NULL) {
        return false;
    }

    *line = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return false;
    }

    while ((ch = fgetc(stream)) != EOF) {
        size_t new_capacity;
        char *resized;

        if (ch == '\0' || length >= MAX_INPUT_LENGTH) {
            free(buffer);
            return false;
        }

        if (length + 1 >= capacity) {
            new_capacity = capacity * 2;

            if (new_capacity > MAX_INPUT_LENGTH + 1U) {
                new_capacity = MAX_INPUT_LENGTH + 1U;
            }

            if (new_capacity <= capacity) {
                free(buffer);
                return false;
            }

            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return false;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;

        if (ch == '\n') {
            break;
        }
    }

    if (ferror(stream) || (ch == EOF && length == 0)) {
        free(buffer);
        return false;
    }

    buffer[length] = '\0';
    *line = buffer;
    return true;
}

static void skip_whitespace(char **text)
{
    while (isspace((unsigned char)**text)) {
        ++*text;
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
    char *input = NULL;
    char *cursor;
    int64_t numerator;
    int64_t denominator;
    int64_t position;
    unsigned int digit;

    if (!read_input_line(stdin, &input)) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    cursor = input;
    skip_whitespace(&cursor);

    if (!parse_int64(&cursor, &numerator) ||
        !isspace((unsigned char)*cursor)) {
        free(input);
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    skip_whitespace(&cursor);

    if (!parse_int64(&cursor, &denominator) ||
        !isspace((unsigned char)*cursor)) {
        free(input);
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    skip_whitespace(&cursor);

    if (!parse_int64(&cursor, &position)) {
        free(input);
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    skip_whitespace(&cursor);

    if (*cursor != '\0') {
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

    printf("%u\n", digit);
    return EXIT_SUCCESS;
}