#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int cube_elements(const int64_t *input, int64_t *output, size_t count)
{
    const int64_t max_root = INT64_C(2097151);
    const int64_t min_root = -INT64_C(2097152);

    if (count != 0U && (input == NULL || output == NULL)) {
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
        if (input[i] < min_root || input[i] > max_root) {
            return -1;
        }

        output[i] = input[i] * input[i] * input[i];
    }

    return 0;
}

static int read_size(size_t *value)
{
    char buffer[128];
    char *end;
    uintmax_t parsed;

    if (value == NULL || fgets(buffer, sizeof buffer, stdin) == NULL) {
        return -1;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (end == buffer || errno == ERANGE || parsed > SIZE_MAX) {
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r') {
        ++end;
    }

    if (*end != '\n' && *end != '\0') {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int read_int64(int64_t *value)
{
    char buffer[128];
    char *end;
    intmax_t parsed;

    if (value == NULL || fgets(buffer, sizeof buffer, stdin) == NULL) {
        return -1;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    if (end == buffer || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r') {
        ++end;
    }

    if (*end != '\n' && *end != '\0') {
        return -1;
    }

    *value = (int64_t)parsed;
    return 0;
}

int main(void)
{
    size_t count;
    int64_t *values = NULL;
    int64_t *cubes = NULL;

    if (read_size(&count) != 0) {
        fputs("Failed to read the element count.\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*values)) {
        fputs("Element count is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    if (count != 0U) {
        values = malloc(count * sizeof(*values));
        cubes = malloc(count * sizeof(*cubes));

        if (values == NULL || cubes == NULL) {
            fputs("Memory allocation failed.\n", stderr);
            free(values);
            free(cubes);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (read_int64(&values[i]) != 0) {
            fputs("Failed to read an element.\n", stderr);
            free(values);
            free(cubes);
            return EXIT_FAILURE;
        }
    }

    if (cube_elements(values, cubes, count) != 0) {
        fputs("An element cannot be cubed without overflow.\n", stderr);
        free(values);
        free(cubes);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (printf("%" PRId64 "%c",
                   cubes[i],
                   i + 1U == count ? '\n' : ' ') < 0) {
            fputs("Failed to write output.\n", stderr);
            free(values);
            free(cubes);
            return EXIT_FAILURE;
        }
    }

    free(values);
    free(cubes);
    return EXIT_SUCCESS;
}