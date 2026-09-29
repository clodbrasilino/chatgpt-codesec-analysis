#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int read_line(char **line)
{
    size_t capacity = 64;
    size_t length = 0;
    char *buffer;

    if (line == NULL) {
        return 0;
    }

    *line = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = getchar();

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                free(buffer);
                return 0;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

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
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

static int is_horizontal_space(char ch)
{
    return ch == ' ' || ch == '\t' || ch == '\r' ||
           ch == '\v' || ch == '\f';
}

static int read_size(size_t *value)
{
    char *buffer = NULL;
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_line(&buffer)) {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (end == buffer || errno == ERANGE || parsed > SIZE_MAX) {
        free(buffer);
        return 0;
    }

    while (is_horizontal_space(*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(buffer);
        return 0;
    }

    *value = (size_t)parsed;
    free(buffer);
    return 1;
}

static int read_int64(int64_t *value)
{
    char *buffer = NULL;
    char *end;
    intmax_t parsed;

    if (value == NULL || !read_line(&buffer)) {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    if (end == buffer || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        free(buffer);
        return 0;
    }

    while (is_horizontal_space(*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(buffer);
        return 0;
    }

    *value = (int64_t)parsed;
    free(buffer);
    return 1;
}

static int sum_of_subarray_products(const int64_t *array, size_t length,
                                    int64_t *result)
{
    int64_t ending_sum = 0;
    int64_t total_sum = 0;

    if (array == NULL || result == NULL) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        int64_t product_sum;
        int64_t new_ending_sum;
        int64_t new_total_sum;

        if (__builtin_mul_overflow(array[i], ending_sum, &product_sum) ||
            __builtin_add_overflow(array[i], product_sum, &new_ending_sum) ||
            __builtin_add_overflow(total_sum, new_ending_sum, &new_total_sum)) {
            return 0;
        }

        ending_sum = new_ending_sum;
        total_sum = new_total_sum;
    }

    *result = total_sum;
    return 1;
}

int main(void)
{
    size_t length;
    int64_t *array;
    int64_t result;

    if (!read_size(&length) || length == 0 ||
        length > SIZE_MAX / sizeof(*array)) {
        return EXIT_FAILURE;
    }

    array = malloc(length * sizeof(*array));
    if (array == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (!read_int64(&array[i])) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (!sum_of_subarray_products(array, length, &result)) {
        free(array);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}