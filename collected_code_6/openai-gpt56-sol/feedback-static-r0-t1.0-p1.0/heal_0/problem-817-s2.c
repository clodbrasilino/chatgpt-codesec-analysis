#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int is_divisible_by_either(int value, int m, int n)
{
    return (value % m == 0) || (value % n == 0);
}

static int find_divisible(const int *numbers, size_t count, int m, int n,
                          int *results, size_t capacity, size_t *result_count)
{
    size_t found = 0;

    if (numbers == NULL || results == NULL || result_count == NULL ||
        m == 0 || n == 0) {
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
        if (is_divisible_by_either(numbers[i], m, n)) {
            if (found >= capacity) {
                return -1;
            }
            results[found++] = numbers[i];
        }
    }

    *result_count = found;
    return 0;
}

static int parse_int(const char *text, int *value)
{
    char *end = NULL;
    long parsed;

    if (text == NULL || value == NULL || *text == '\0') {
        return -1;
    }

    errno = 0;
    parsed = strtol(text, &end, 10);

    if (errno != 0 || end == text || *end != '\0' ||
        parsed < INT_MIN || parsed > INT_MAX) {
        return -1;
    }

    *value = (int)parsed;
    return 0;
}

int main(int argc, char *argv[])
{
    int m;
    int n;
    int *numbers = NULL;
    int *results = NULL;
    size_t count;
    size_t result_count = 0;
    int status = EXIT_FAILURE;

    if (argc < 4) {
        fprintf(stderr, "Usage: %s m n number [number ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (parse_int(argv[1], &m) != 0 || parse_int(argv[2], &n) != 0 ||
        m == 0 || n == 0) {
        fprintf(stderr, "m and n must be valid nonzero integers.\n");
        return EXIT_FAILURE;
    }

    count = (size_t)(argc - 3);

    if (count > SIZE_MAX / sizeof(*numbers)) {
        fprintf(stderr, "Input is too large.\n");
        return EXIT_FAILURE;
    }

    numbers = malloc(count * sizeof(*numbers));
    results = malloc(count * sizeof(*results));

    if (numbers == NULL || results == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        goto cleanup;
    }

    for (size_t i = 0; i < count; ++i) {
        if (parse_int(argv[i + 3], &numbers[i]) != 0) {
            fprintf(stderr, "Invalid integer: %s\n", argv[i + 3]);
            goto cleanup;
        }
    }

    if (find_divisible(numbers, count, m, n, results, count,
                       &result_count) != 0) {
        fprintf(stderr, "Unable to find divisible numbers.\n");
        goto cleanup;
    }

    for (size_t i = 0; i < result_count; ++i) {
        if (printf("%d%s", results[i],
                   i + 1 < result_count ? " " : "\n") < 0) {
            fprintf(stderr, "Output failed.\n");
            goto cleanup;
        }
    }

    if (result_count == 0 && putchar('\n') == EOF) {
        fprintf(stderr, "Output failed.\n");
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(results);
    free(numbers);
    return status;
}