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

static int read_token(char *buffer, size_t capacity)
{
    int ch;
    size_t length = 0;

    if (buffer == NULL || capacity < 2) {
        return 0;
    }

    do {
        ch = getchar();
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return 0;
    }

    do {
        if (length + 1 >= capacity) {
            do {
                ch = getchar();
            } while (ch != EOF && !isspace((unsigned char)ch));
            return 0;
        }

        buffer[length++] = (char)ch;
        ch = getchar();
    } while (ch != EOF && !isspace((unsigned char)ch));

    buffer[length] = '\0';
    return 1;
}

static int read_size(size_t *value)
{
    char token[64];
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_token(token, sizeof(token)) ||
        token[0] == '\0' || token[0] == '-') {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed == 0 || parsed > SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int read_int64(int64_t *value)
{
    char token[64];
    char *end;
    intmax_t parsed;

    if (value == NULL || !read_token(token, sizeof(token)) ||
        token[0] == '\0') {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
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