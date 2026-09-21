#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>

static int read_int64(int64_t *value)
{
    char buffer[128];

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    char *end;
    errno = 0;
    intmax_t parsed = strtoimax(buffer, &end, 10);

    if (end == buffer || errno == ERANGE || parsed < INT64_MIN || parsed > INT64_MAX) {
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

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    char *start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        return 0;
    }

    char *end;
    errno = 0;
    uintmax_t parsed = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || parsed > SIZE_MAX) {
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int64_t max_non_adjacent_sum(const int64_t *top,
                                    const int64_t *bottom,
                                    size_t n)
{
    int64_t previous = 0;
    int64_t previous_previous = 0;

    for (size_t i = 0; i < n; ++i) {
        int64_t column_max = top[i] > bottom[i] ? top[i] : bottom[i];
        int64_t include = previous_previous;

        if (column_max > 0) {
            if (include > INT64_MAX - column_max) {
                return INT64_MAX;
            }
            include += column_max;
        }

        int64_t current = previous > include ? previous : include;
        previous_previous = previous;
        previous = current;
    }

    return previous;
}

int main(void)
{
    size_t n;

    if (!read_size(&n) || n > SIZE_MAX / sizeof(int64_t)) {
        return EXIT_FAILURE;
    }

    int64_t *top = NULL;
    int64_t *bottom = NULL;

    if (n != 0) {
        top = malloc(n * sizeof *top);
        bottom = malloc(n * sizeof *bottom);

        if (top == NULL || bottom == NULL) {
            free(top);
            free(bottom);
            return EXIT_FAILURE;
        }
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

    int64_t result = max_non_adjacent_sum(top, bottom, n);

    if (printf("%" PRId64 "\n", result) < 0) {
        free(top);
        free(bottom);
        return EXIT_FAILURE;
    }

    free(top);
    free(bottom);
    return EXIT_SUCCESS;
}