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

    if (a == 0 || b == 0) {
        *result = 0;
        return 1;
    }

    if ((a == -1 && b == INT64_MIN) ||
        (b == -1 && a == INT64_MIN)) {
        return 0;
    }

    if (a > 0) {
        if ((b > 0 && a > INT64_MAX / b) ||
            (b < 0 && b < INT64_MIN / a)) {
            return 0;
        }
    } else {
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
    char *buffer = NULL;
    size_t capacity = 32;
    size_t length = 0;
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

    for (;;) {
        if (length >= capacity - 1) {
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
        if (ch == EOF || isspace((unsigned char)ch)) {
            break;
        }
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
    char *token;
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_token(&token)) {
        return 0;
    }

    if (token[0] == '\0' || token[0] == '-') {
        free(token);
        return 0;
    }

    errno = 0;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed > (uintmax_t)SIZE_MAX) {
        free(token);
        return 0;
    }

    *value = (size_t)parsed;
    free(token);
    return 1;
}

static int read_int64(int64_t *value)
{
    char *token;
    char *end;
    intmax_t parsed;

    if (value == NULL || !read_token(&token)) {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        free(token);
        return 0;
    }

    *value = (int64_t)parsed;
    free(token);
    return 1;
}

int main(void)
{
    size_t length;
    int64_t result;
    int64_t *array;

    if (!read_size(&length) || length == 0 ||
        length > SIZE_MAX / sizeof(*array)) {
        fputs("Invalid array length\n", stderr);
        return EXIT_FAILURE;
    }

    array = malloc(length * sizeof(*array));
    if (array == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (!read_int64(&array[i])) {
            fputs("Invalid array element\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (!maximum_product_subarray(array, length, &result)) {
        fputs("Unable to calculate maximum product\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    free(array);

    if (printf("%" PRId64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}