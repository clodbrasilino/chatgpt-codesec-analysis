#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

static int read_int64(int64_t *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    char *start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    errno = 0;
    char *end;
    intmax_t parsed = strtoimax(start, &end, 10);

    if (start == end || errno == ERANGE ||
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
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

    errno = 0;
    char *end;
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

static int add_int64_checked(int64_t a, int64_t b, int64_t *result)
{
    if ((b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int max_non_adjacent_sum(const int64_t *top,
                                const int64_t *bottom,
                                size_t n,
                                int64_t *result)
{
    int64_t previous = 0;
    int64_t current = 0;

    for (size_t i = 0; i < n; ++i) {
        int64_t column_max = top[i] > bottom[i] ? top[i] : bottom[i];
        int64_t include;

        if (!add_int64_checked(previous, column_max, &include)) {
            return 0;
        }

        int64_t next = include > current ? include : current;
        previous = current;
        current = next;
    }

    *result = current;
    return 1;
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

    int64_t result;

    if (!max_non_adjacent_sum(top, bottom, n, &result)) {
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