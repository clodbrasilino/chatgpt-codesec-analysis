#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int read_line(char **line, size_t *capacity)
{
    size_t length = 0;
    int ch;

    if (line == NULL || capacity == NULL) {
        return -1;
    }

    if (*line == NULL || *capacity == 0) {
        *capacity = 128;
        *line = malloc(*capacity);
        if (*line == NULL) {
            return -1;
        }
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length + 1 >= *capacity) {
            size_t new_capacity;
            char *new_line;

            if (*capacity > SIZE_MAX / 2) {
                return -1;
            }

            new_capacity = *capacity * 2;
            new_line = realloc(*line, new_capacity);
            if (new_line == NULL) {
                return -1;
            }

            *line = new_line;
            *capacity = new_capacity;
        }

        (*line)[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        return -1;
    }

    (*line)[length] = '\0';
    return 0;
}

static int read_size(size_t *value)
{
    char *line = NULL;
    size_t capacity = 0;
    char *end;
    uintmax_t parsed;
    int status = -1;

    if (value == NULL || read_line(&line, &capacity) != 0) {
        free(line);
        return -1;
    }

    errno = 0;
    parsed = strtoumax(line, &end, 10);

    if (end != line && errno != ERANGE && parsed != 0 &&
        parsed <= SIZE_MAX) {
        while (*end == ' ' || *end == '\t' ||
               *end == '\r' || *end == '\n') {
            ++end;
        }

        if (*end == '\0') {
            *value = (size_t)parsed;
            status = 0;
        }
    }

    free(line);
    return status;
}

static int read_int64(int64_t *value)
{
    char *line = NULL;
    size_t capacity = 0;
    char *end;
    intmax_t parsed;
    int status = -1;

    if (value == NULL || read_line(&line, &capacity) != 0) {
        free(line);
        return -1;
    }

    errno = 0;
    parsed = strtoimax(line, &end, 10);

    if (end != line && errno != ERANGE &&
        parsed >= INT64_MIN && parsed <= INT64_MAX) {
        while (*end == ' ' || *end == '\t' ||
               *end == '\r' || *end == '\n') {
            ++end;
        }

        if (*end == '\0') {
            *value = (int64_t)parsed;
            status = 0;
        }
    }

    free(line);
    return status;
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