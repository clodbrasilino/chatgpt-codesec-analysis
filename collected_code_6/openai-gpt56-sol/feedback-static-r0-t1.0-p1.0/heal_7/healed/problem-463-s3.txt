#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <errno.h>
#include <ctype.h>

#define TOKEN_LIMIT ((size_t)1024 * 1024)

static int multiply_checked(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    if ((a > 0 && b > 0 && a > INT64_MAX / b) ||
        (a > 0 && b < 0 && b < INT64_MIN / a) ||
        (a < 0 && b > 0 && a < INT64_MIN / b) ||
        (a < 0 && b < 0 && a < INT64_MAX / b)) {
        return 0;
    }

    *result = a * b;
    return 1;
}

static int maximum_product_subarray(const int64_t *array, size_t length,
                                    int64_t *maximum_product)
{
    int64_t maximum_ending;
    int64_t minimum_ending;
    int64_t overall_maximum;

    if (array == NULL || maximum_product == NULL || length == 0) {
        return 0;
    }

    maximum_ending = array[0];
    minimum_ending = array[0];
    overall_maximum = array[0];

    for (size_t i = 1; i < length; ++i) {
        int64_t product_with_maximum;
        int64_t product_with_minimum;
        int64_t next_maximum = array[i];
        int64_t next_minimum = array[i];

        if (!multiply_checked(array[i], maximum_ending,
                              &product_with_maximum) ||
            !multiply_checked(array[i], minimum_ending,
                              &product_with_minimum)) {
            return 0;
        }

        if (product_with_maximum > next_maximum) {
            next_maximum = product_with_maximum;
        }
        if (product_with_minimum > next_maximum) {
            next_maximum = product_with_minimum;
        }
        if (product_with_maximum < next_minimum) {
            next_minimum = product_with_maximum;
        }
        if (product_with_minimum < next_minimum) {
            next_minimum = product_with_minimum;
        }

        maximum_ending = next_maximum;
        minimum_ending = next_minimum;

        if (maximum_ending > overall_maximum) {
            overall_maximum = maximum_ending;
        }
    }

    *maximum_product = overall_maximum;
    return 1;
}

static int read_token(char **token)
{
    size_t capacity = 32;
    size_t length = 0;
    char *buffer;
    int character;

    if (token == NULL) {
        return 0;
    }

    *token = NULL;
    buffer = malloc(capacity);

    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        character = fgetc(stdin);

        if (character == EOF) {
            free(buffer);
            return 0;
        }

        if (!isspace((unsigned char)character)) {
            break;
        }
    }

    while (character != EOF && !isspace((unsigned char)character)) {
        if (length == TOKEN_LIMIT) {
            free(buffer);
            return 0;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity >= TOKEN_LIMIT + 1) {
                free(buffer);
                return 0;
            }

            if (capacity > (TOKEN_LIMIT + 1) / 2) {
                new_capacity = TOKEN_LIMIT + 1;
            } else {
                new_capacity = capacity * 2;
            }

            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return 0;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)character;
        character = fgetc(stdin);
    }

    if (ferror(stdin)) {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';
    *token = buffer;
    return 1;
}

static int parse_size(const char *text, size_t *value)
{
    char *end;
    uintmax_t parsed;

    if (text == NULL || value == NULL || text[0] == '\0' ||
        text[0] == '-' || isspace((unsigned char)text[0])) {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed == 0 || parsed > SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int parse_int64(const char *text, int64_t *value)
{
    char *end;
    intmax_t parsed;

    if (text == NULL || value == NULL || text[0] == '\0' ||
        isspace((unsigned char)text[0])) {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

int main(void)
{
    char *token = NULL;
    size_t length;
    int64_t *array = NULL;
    int64_t result;

    if (!read_token(&token) ||
        !parse_size(token, &length) ||
        length > SIZE_MAX / sizeof(*array)) {
        free(token);
        fputs("Invalid array length\n", stderr);
        return EXIT_FAILURE;
    }

    free(token);
    token = NULL;

    array = malloc(length * sizeof(*array));
    if (array == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (!read_token(&token) || !parse_int64(token, &array[i])) {
            free(token);
            free(array);
            fputs("Invalid array element\n", stderr);
            return EXIT_FAILURE;
        }

        free(token);
        token = NULL;
    }

    if (!maximum_product_subarray(array, length, &result)) {
        free(array);
        fputs("Unable to calculate maximum product\n", stderr);
        return EXIT_FAILURE;
    }

    free(array);

    if (printf("%" PRId64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}