#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int read_line(char **line)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer;

    if (line == NULL) {
        return 0;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                free(buffer);
                return 0;
            }
            break;
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

        buffer[length++] = (char)ch;

        if (ch == '\n') {
            break;
        }
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

static int only_trailing_whitespace(const char *text)
{
    if (text == NULL) {
        return 0;
    }

    while (*text != '\0') {
        if (!isspace((unsigned char)*text)) {
            return 0;
        }
        ++text;
    }

    return 1;
}

static int read_size(size_t *value)
{
    char *buffer;
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_line(&buffer)) {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || parsed > SIZE_MAX ||
        !only_trailing_whitespace(end)) {
        free(buffer);
        return 0;
    }

    *value = (size_t)parsed;
    free(buffer);
    return 1;
}

static int read_int64(int64_t *value)
{
    char *buffer;
    char *end;
    intmax_t parsed;

    if (value == NULL || !read_line(&buffer)) {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer ||
        parsed < INT64_MIN || parsed > INT64_MAX ||
        !only_trailing_whitespace(end)) {
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
        int64_t next_ending_sum;
        int64_t next_total_sum;

        if (__builtin_mul_overflow(array[i], ending_sum, &product_sum) ||
            __builtin_add_overflow(array[i], product_sum, &next_ending_sum) ||
            __builtin_add_overflow(total_sum, next_ending_sum,
                                   &next_total_sum)) {
            return 0;
        }

        ending_sum = next_ending_sum;
        total_sum = next_total_sum;
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
        length > SIZE_MAX / sizeof *array) {
        return EXIT_FAILURE;
    }

    array = malloc(length * sizeof *array);
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