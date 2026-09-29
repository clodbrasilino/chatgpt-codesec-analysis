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
        return -1;
    }

    *line = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = getchar();

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                free(buffer);
                return -1;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length == capacity - 1) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 0;
}

static int only_trailing_space(const char *text)
{
    if (text == NULL) {
        return 0;
    }

    while (*text == ' ' || *text == '\t' || *text == '\r') {
        ++text;
    }

    return *text == '\0';
}

static int read_size(size_t *value)
{
    char *buffer = NULL;
    char *end = NULL;
    uintmax_t parsed;

    if (value == NULL || read_line(&buffer) != 0) {
        return -1;
    }

    if (buffer[0] == '-') {
        free(buffer);
        return -1;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (end == buffer || errno == ERANGE || parsed == 0 ||
        parsed > SIZE_MAX || !only_trailing_space(end)) {
        free(buffer);
        return -1;
    }

    *value = (size_t)parsed;
    free(buffer);
    return 0;
}

static int read_int64(int64_t *value)
{
    char *buffer = NULL;
    char *end = NULL;
    intmax_t parsed;

    if (value == NULL || read_line(&buffer) != 0) {
        return -1;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    if (end == buffer || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX ||
        !only_trailing_space(end)) {
        free(buffer);
        return -1;
    }

    *value = (int64_t)parsed;
    free(buffer);
    return 0;
}

static int sum_of_subarray_products(const int64_t *values, size_t count,
                                    int64_t *result)
{
    int64_t ending_sum = 0;
    int64_t total = 0;

    if (values == NULL || result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
        int64_t product;
        int64_t next_ending_sum;
        int64_t next_total;

        if (__builtin_mul_overflow(values[i], ending_sum, &product) ||
            __builtin_add_overflow(values[i], product, &next_ending_sum) ||
            __builtin_add_overflow(total, next_ending_sum, &next_total)) {
            return -1;
        }

        ending_sum = next_ending_sum;
        total = next_total;
    }

    *result = total;
    return 0;
}

int main(void)
{
    size_t count;
    int64_t *values;
    int64_t result;

    if (read_size(&count) != 0 ||
        count > SIZE_MAX / sizeof(*values)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    values = malloc(count * sizeof(*values));
    if (values == NULL) {
        fputs("Allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (read_int64(&values[i]) != 0) {
            fputs("Invalid input\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (sum_of_subarray_products(values, count, &result) != 0) {
        fputs("Arithmetic overflow\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        fputs("Output error\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}