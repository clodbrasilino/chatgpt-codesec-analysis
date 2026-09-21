#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>

static int64_t max_value(int64_t a, int64_t b)
{
    return a > b ? a : b;
}

static int read_int64(int64_t *value)
{
    char buffer[128];
    char *end;
    intmax_t parsed;

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    parsed = strtoimax(buffer, &end, 10);

    if (end == buffer) {
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r') {
        ++end;
    }

    if (*end != '\n' && *end != '\0') {
        return 0;
    }

    if (parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

static int read_size(size_t *value)
{
    char buffer[128];
    char *end;
    uintmax_t parsed;

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    parsed = strtoumax(buffer, &end, 10);

    if (end == buffer || buffer[0] == '-') {
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r') {
        ++end;
    }

    if (*end != '\n' && *end != '\0') {
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

    for (size_t i = 0; i < n; ++i) {
        int64_t column_value = max_value(top[i], bottom[i]);
        int64_t include_current;
        int64_t exclude_current =
            max_value(exclude_previous, include_previous);

        if (column_value > 0 &&
            exclude_previous > INT64_MAX - column_value) {
            return 0;
        }

        include_current = exclude_previous + column_value;

        if (include_current < 0) {
            include_current = 0;
        }

        include_previous = include_current;
        exclude_previous = exclude_current;
    }

    *result = max_value(include_previous, exclude_previous);
    return 1;
}

int main(void)
{
    size_t n;
    int64_t *top = NULL;
    int64_t *bottom = NULL;
    int64_t result;

    if (!read_size(&n) || n > SIZE_MAX / sizeof(*top)) {
        return EXIT_FAILURE;
    }

    top = malloc(n * sizeof(*top));
    bottom = malloc(n * sizeof(*bottom));

    if (top == NULL || bottom == NULL) {
        free(top);
        free(bottom);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < n; ++i) {
        if (!read_int64(&top[i])) {
            free(top);
            free(bottom);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < n; ++i) {
        if (!read_int64(&bottom[i])) {
            free(top);
            free(bottom);
            return EXIT_FAILURE;
        }
    }

    if (!maximum_non_adjacent_sum(top, bottom, n, &result)) {
        free(top);
        free(bottom);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        free(top);
        free(bottom);
        return EXIT_FAILURE;
    }

    free(top);
    free(bottom);
    return EXIT_SUCCESS;
}