#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>

static int64_t max_value(int64_t a, int64_t b)
{
    return a > b ? a : b;
}

static int read_line(char **line, size_t *capacity)
{
    size_t length = 0;
    int ch = EOF;

    if (line == NULL || capacity == NULL) {
        return 0;
    }

    if (*line == NULL || *capacity < 2) {
        char *new_line;
        size_t new_capacity = 128;

        new_line = realloc(*line, new_capacity);
        if (new_line == NULL) {
            return 0;
        }

        *line = new_line;
        *capacity = new_capacity;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (length == SIZE_MAX - 1) {
            return 0;
        }

        if (length + 1 >= *capacity) {
            size_t required = length + 2;
            size_t new_capacity;
            char *new_line;

            if (*capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = *capacity * 2;
            }

            if (new_capacity < required) {
                new_capacity = required;
            }

            new_line = realloc(*line, new_capacity);
            if (new_line == NULL) {
                return 0;
            }

            *line = new_line;
            *capacity = new_capacity;
        }

        (*line)[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        return 0;
    }

    if (ch == EOF && length == 0) {
        return 0;
    }

    (*line)[length] = '\0';
    return 1;
}

static int only_trailing_space(const char *text)
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

static int parse_int64(const char *text, int64_t *value)
{
    char *end;
    intmax_t parsed;

    if (text == NULL || value == NULL) {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(text, &end, 10);

    if (end == text || errno == ERANGE || !only_trailing_space(end)) {
        return 0;
    }

    if (parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

static int parse_size(const char *text, size_t *value)
{
    const char *start;
    char *end;
    uintmax_t parsed;

    if (text == NULL || value == NULL) {
        return 0;
    }

    start = text;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-' || *start == '\0') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || !only_trailing_space(end)) {
        return 0;
    }

    if (parsed == 0 || parsed > SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int maximum_non_adjacent_sum(const int64_t *top,
                                    const int64_t *bottom,
                                    size_t n,
                                    int64_t *result)
{
    int64_t exclude_previous = 0;
    int64_t include_previous = 0;
    size_t i;

    if (top == NULL || bottom == NULL || result == NULL) {
        return 0;
    }

    for (i = 0; i < n; ++i) {
        int64_t column_value = max_value(top[i], bottom[i]);
        int64_t exclude_current =
            max_value(exclude_previous, include_previous);
        int64_t include_current = 0;

        if (column_value > 0) {
            if (exclude_previous > INT64_MAX - column_value) {
                return 0;
            }
            include_current = exclude_previous + column_value;
        }

        include_previous = include_current;
        exclude_previous = exclude_current;
    }

    *result = max_value(include_previous, exclude_previous);
    return 1;
}

int main(void)
{
    char *line = NULL;
    size_t line_capacity = 0;
    size_t n;
    size_t i;
    int64_t *top = NULL;
    int64_t *bottom = NULL;
    int64_t result;
    int status = EXIT_FAILURE;

    if (!read_line(&line, &line_capacity) || !parse_size(line, &n)) {
        goto cleanup;
    }

    if (n > SIZE_MAX / sizeof(*top)) {
        goto cleanup;
    }

    top = malloc(n * sizeof(*top));
    bottom = malloc(n * sizeof(*bottom));

    if (top == NULL || bottom == NULL) {
        goto cleanup;
    }

    for (i = 0; i < n; ++i) {
        if (!read_line(&line, &line_capacity) ||
            !parse_int64(line, &top[i])) {
            goto cleanup;
        }
    }

    for (i = 0; i < n; ++i) {
        if (!read_line(&line, &line_capacity) ||
            !parse_int64(line, &bottom[i])) {
            goto cleanup;
        }
    }

    if (!maximum_non_adjacent_sum(top, bottom, n, &result)) {
        goto cleanup;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(line);
    free(top);
    free(bottom);
    return status;
}