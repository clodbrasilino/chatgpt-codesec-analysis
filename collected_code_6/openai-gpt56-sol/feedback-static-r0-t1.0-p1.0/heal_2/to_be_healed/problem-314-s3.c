#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <errno.h>
#include <ctype.h>

static int read_int64(int64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *start;
    char *end;

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    errno = 0;
    intmax_t parsed = strtoimax(start, &end, 10);

    if (start == end || errno == ERANGE || parsed < INT64_MIN || parsed > INT64_MAX) {
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *start;
    char *end;

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        return 0;
    }

    errno = 0;
    uintmax_t parsed = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE || parsed > SIZE_MAX) {
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
    int64_t current = 0;

    for (size_t i = 0; i < n; ++i) {
        int64_t column_max = top[i] > bottom[i] ? top[i] : bottom[i];
        int64_t include;

        if (column_max > 0 && previous > INT64_MAX - column_max) {
            include = INT64_MAX;
        } else if (column_max < 0 && previous < INT64_MIN - column_max) {
            include = INT64_MIN;
        } else {
            include = previous + column_max;
        }

        int64_t next = include > current ? include : current;
        previous = current;
        current = next;
    }

    return current;
}

int main(void)
{
    size_t n;

    if (!read_size(&n) || n > SIZE_MAX / sizeof(int64_t)) {
        return EXIT_FAILURE;
    }

    int64_t *top = n == 0 ? NULL : malloc(n * sizeof(*top));
    int64_t *bottom = n == 0 ? NULL : malloc(n * sizeof(*bottom));

    if (n != 0 && (top == NULL || bottom == NULL)) {
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