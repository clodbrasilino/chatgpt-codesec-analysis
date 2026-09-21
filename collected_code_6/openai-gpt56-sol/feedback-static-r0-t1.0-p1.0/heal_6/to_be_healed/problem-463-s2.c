#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <errno.h>
#include <ctype.h>

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
    int64_t result;

    if (array == NULL || maximum_product == NULL || length == 0) {
        return 0;
    }

    current_max = array[0];
    current_min = array[0];
    result = array[0];

    for (size_t i = 1; i < length; ++i) {
        int64_t product_with_max;
        int64_t product_with_min;
        int64_t next_max;
        int64_t next_min;

        if (!multiply_checked(current_max, array[i], &product_with_max) ||
            !multiply_checked(current_min, array[i], &product_with_min)) {
            return 0;
        }

        next_max = array[i];
        if (product_with_max > next_max) {
            next_max = product_with_max;
        }
        if (product_with_min > next_max) {
            next_max = product_with_min;
        }

        next_min = array[i];
        if (product_with_max < next_min) {
            next_min = product_with_max;
        }
        if (product_with_min < next_min) {
            next_min = product_with_min;
        }

        current_max = next_max;
        current_min = next_min;

        if (current_max > result) {
            result = current_max;
        }
    }

    *maximum_product = result;
    return 1;
}

static int read_token(char **token)
{
    size_t capacity = 32;
    size_t length = 0;
    char *buffer;
    int ch;

    if (token == NULL) {
        return 0;
    }

    *token = NULL;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();

        if (ch == EOF) {
            return 0;
        }

        if (!isspace((unsigned char)ch)) {
            break;
        }
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
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

        buffer[length++] = (char)ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    }

    if (ch == EOF && ferror(stdin)) {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';
    *token = buffer;
    return 1;
}

static int read_size(size_t *value)
{
    char *token = NULL;
    char *end = NULL;
    uintmax_t parsed;
    int valid = 0;

    if (value == NULL || !read_token(&token)) {
        return 0;
    }

    if (token[0] == '\0' || token[0] == '-' || token[0] == '+') {
        goto cleanup;
    }

    errno = 0;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed == 0 || parsed > SIZE_MAX) {
        goto cleanup;
    }

    *value = (size_t)parsed;
    valid = 1;

cleanup:
    free(token);
    return valid;
}

static int read_int64(int64_t *value)
{
    char *token = NULL;
    char *end = NULL;
    intmax_t parsed;
    int valid = 0;

    if (value == NULL || !read_token(&token)) {
        return 0;
    }

    if (token[0] == '\0') {
        goto cleanup;
    }

    errno = 0;
    parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        goto cleanup;
    }

    *value = (int64_t)parsed;
    valid = 1;

cleanup:
    free(token);
    return valid;
}

int main(void)
{
    size_t length;
    int64_t *array = NULL;
    int64_t result;
    int status = EXIT_FAILURE;

    if (!read_size(&length) || length > SIZE_MAX / sizeof(*array)) {
        fprintf(stderr, "Invalid array length.\n");
        return EXIT_FAILURE;
    }

    array = malloc(length * sizeof(*array));
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (!read_int64(&array[i])) {
            fprintf(stderr, "Invalid array element.\n");
            goto cleanup;
        }
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
    free(array);
    return status;
}