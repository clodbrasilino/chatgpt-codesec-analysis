#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <errno.h>
#include <ctype.h>

static int64_t max_value(int64_t a, int64_t b)
{
    return a > b ? a : b;
}

static int read_int64(int64_t *value)
{
    char buffer[128];
    char *end;

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    errno = 0;
    intmax_t parsed = strtoimax(buffer, &end, 10);

    if (end == buffer || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

static int read_size(size_t *value)
{
    char buffer[128];
    char *end;

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    errno = 0;
    uintmax_t parsed = strtoumax(buffer, &end, 10);

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (end == buffer || errno == ERANGE || *end != '\0' ||
        parsed == 0 || parsed > SIZE_MAX ||
        parsed > SIZE_MAX / sizeof(int64_t)) {
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

        if (column_value > 0 &&
            exclude_previous > INT64_MAX - column_value) {
            return 0;
        }

        int64_t include_current = exclude_previous + column_value;
        int64_t exclude_current =
            max_value(exclude_previous, include_previous);

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
    int64_t result;

    if (!read_size(&n)) {
        return EXIT_FAILURE;
    }

    int64_t *top = malloc(n * sizeof *top);
    int64_t *bottom = malloc(n * sizeof *bottom);

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