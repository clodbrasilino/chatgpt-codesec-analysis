#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <errno.h>

static int add_checked(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    if ((b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int max_sum_no_three_consecutive(const int64_t *values,
                                        size_t count,
                                        int64_t *result)
{
    int64_t previous[3] = {0, INT64_MIN, INT64_MIN};
    int64_t current[3];

    if (result == NULL || (values == NULL && count != 0U)) {
        return 0;
    }

    for (size_t i = 0; i < count; ++i) {
        current[0] = previous[0];

        if (previous[1] > current[0]) {
            current[0] = previous[1];
        }

        if (previous[2] > current[0]) {
            current[0] = previous[2];
        }

        if (!add_checked(previous[0], values[i], &current[1])) {
            return 0;
        }

        if (previous[1] == INT64_MIN) {
            current[2] = INT64_MIN;
        } else if (!add_checked(previous[1], values[i], &current[2])) {
            return 0;
        }

        previous[0] = current[0];
        previous[1] = current[1];
        previous[2] = current[2];
    }

    *result = previous[0];

    if (previous[1] > *result) {
        *result = previous[1];
    }

    if (previous[2] > *result) {
        *result = previous[2];
    }

    return 1;
}

static int read_line(char **line)
{
    size_t length = 0;
    size_t capacity = 64;
    int ch;
    char *buffer;

    if (line == NULL) {
        return 0;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
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
    }

    if (ch == EOF && length == 0) {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

static int only_trailing_space(const char *text)
{
    while (*text == ' ' || *text == '\t' || *text == '\r' ||
           *text == '\v' || *text == '\f') {
        ++text;
    }

    return *text == '\0';
}

static int read_size(size_t *value)
{
    char *buffer;
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_line(&buffer)) {
        return 0;
    }

    if (buffer[0] == '-') {
        free(buffer);
        return 0;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (end == buffer || errno == ERANGE || parsed > SIZE_MAX ||
        !only_trailing_space(end)) {
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

    if (end == buffer || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX ||
        !only_trailing_space(end)) {
        free(buffer);
        return 0;
    }

    *value = (int64_t)parsed;
    free(buffer);
    return 1;
}

int main(void)
{
    size_t count;
    int64_t *values = NULL;
    int64_t result;

    if (!read_size(&count)) {
        fputs("Invalid element count\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*values)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (count != 0U) {
        values = malloc(count * sizeof(*values));
        if (values == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_int64(&values[i])) {
            fputs("Invalid element\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    if (!max_sum_no_three_consecutive(values, count, &result)) {
        fputs("Unable to calculate the result safely\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}