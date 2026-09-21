#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>

static int multiply_checked(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    if (a > 0) {
        if ((b > 0 && a > INT64_MAX / b) ||
            (b < 0 && b < INT64_MIN / a)) {
            return 0;
        }
    } else if (a < 0) {
        if ((b > 0 && a < INT64_MIN / b) ||
            (b < 0 && a < INT64_MAX / b)) {
            return 0;
        }
    }

    *result = a * b;
    return 1;
}

static int maximum_product_subarray(const int64_t *array, size_t length,
                                    int64_t *maximum_product)
{
    int64_t current_max;
    int64_t current_min;
    int64_t best;

    if (array == NULL || maximum_product == NULL || length == 0) {
        return 0;
    }

    current_max = array[0];
    current_min = array[0];
    best = array[0];

    for (size_t i = 1; i < length; ++i) {
        int64_t product_max;
        int64_t product_min;
        int64_t next_max = array[i];
        int64_t next_min = array[i];

        if (!multiply_checked(current_max, array[i], &product_max) ||
            !multiply_checked(current_min, array[i], &product_min)) {
            return 0;
        }

        if (product_max > next_max) {
            next_max = product_max;
        }
        if (product_min > next_max) {
            next_max = product_min;
        }
        if (product_max < next_min) {
            next_min = product_max;
        }
        if (product_min < next_min) {
            next_min = product_min;
        }

        current_max = next_max;
        current_min = next_min;

        if (current_max > best) {
            best = current_max;
        }
    }

    *maximum_product = best;
    return 1;
}

static int read_token(char **token)
{
    size_t length = 0;
    size_t capacity = 32;
    char *buffer;
    int c;

    if (token == NULL) {
        return 0;
    }

    *token = NULL;

    do {
        c = fgetc(stdin);
    } while (c != EOF && isspace((unsigned char)c));

    if (c == EOF) {
        return 0;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    while (c != EOF && !isspace((unsigned char)c)) {
        if (length == SIZE_MAX - 1) {
            free(buffer);
            return 0;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)c;
        c = fgetc(stdin);
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

    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
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

    if (text == NULL || value == NULL || *text == '\0') {
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
    int status = EXIT_FAILURE;

    if (!read_token(&token) || !parse_size(token, &length) ||
        length > SIZE_MAX / sizeof(*array)) {
        fprintf(stderr, "Invalid array length.\n");
        free(token);
        return EXIT_FAILURE;
    }

    free(token);
    token = NULL;

    array = malloc(length * sizeof(*array));
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (!read_token(&token) || !parse_int64(token, &array[i])) {
            fprintf(stderr, "Invalid array element.\n");
            goto cleanup;
        }

        free(token);
        token = NULL;
    }

    if (!maximum_product_subarray(array, length, &result)) {
        fprintf(stderr, "Product overflow or invalid input.\n");
        goto cleanup;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        fprintf(stderr, "Output failed.\n");
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(token);
    free(array);
    return status;
}