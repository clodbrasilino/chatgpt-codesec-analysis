#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>

static int read_token(char *buffer, size_t capacity)
{
    int ch;
    size_t length = 0;
    int valid = 1;

    if (buffer == NULL || capacity < 2U) {
        return 0;
    }

    do {
        ch = fgetc(stdin);
        if (ch == EOF) {
            return 0;
        }
    } while (isspace((unsigned char)ch));

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length < capacity - 1U) {
            buffer[length++] = (char)ch;
        } else {
            valid = 0;
        }
        ch = fgetc(stdin);
    }

    buffer[length] = '\0';
    return valid;
}

static int read_size(size_t *value)
{
    char buffer[128];
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_token(buffer, sizeof buffer) ||
        buffer[0] == '-' || buffer[0] == '+') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed > (uintmax_t)SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int read_int64(int64_t *value)
{
    char buffer[128];
    char *end;
    intmax_t parsed;

    if (value == NULL || !read_token(buffer, sizeof buffer)) {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed < (intmax_t)INT64_MIN || parsed > (intmax_t)INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

static int multiply_checked(int64_t left, int64_t right, int64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    if (left > 0) {
        if ((right > 0 && left > INT64_MAX / right) ||
            (right < 0 && right < INT64_MIN / left)) {
            return 0;
        }
    } else if (left < 0) {
        if ((right > 0 && left < INT64_MIN / right) ||
            (right < 0 && left < INT64_MAX / right)) {
            return 0;
        }
    }

    *result = left * right;
    return 1;
}

static int product_of_non_repeated(const int64_t *array, size_t length,
                                   int64_t *product)
{
    int64_t result = 1;
    int found = 0;

    if (array == NULL || length == 0U || product == NULL) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        int repeated = 0;

        for (size_t j = 0; j < length; ++j) {
            if (i != j && array[i] == array[j]) {
                repeated = 1;
                break;
            }
        }

        if (!repeated) {
            int64_t next;

            if (!multiply_checked(result, array[i], &next)) {
                return 0;
            }

            result = next;
            found = 1;
        }
    }

    if (!found) {
        return 0;
    }

    *product = result;
    return 1;
}

int main(void)
{
    size_t length;
    int64_t *array;
    int64_t product;

    if (!read_size(&length)) {
        fputs("Invalid array length.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length == 0U) {
        fputs("The array must not be empty.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof *array) {
        fputs("Array size is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    array = malloc(length * sizeof *array);
    if (array == NULL) {
        fputs("Unable to allocate memory.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (!read_int64(&array[i])) {
            fputs("Invalid array element.\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (!product_of_non_repeated(array, length, &product)) {
        fputs("No unique elements or product overflow.\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", product) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}