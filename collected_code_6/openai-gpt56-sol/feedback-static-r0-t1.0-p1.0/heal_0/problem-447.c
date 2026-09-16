#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int cube_elements(const int64_t *input, int64_t *output, size_t count)
{
    const int64_t max_root = INT64_C(2097151);
    const int64_t min_root = -INT64_C(2097152);

    if ((input == NULL || output == NULL) && count != 0U) {
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

int main(void)
{
    size_t count = 0U;

    if (scanf("%zu", &count) != 1) {
        fputs("Failed to read the element count.\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(int64_t)) {
        fputs("Element count is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    int64_t *values = NULL;
    int64_t *cubes = NULL;

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
        if (scanf("%" SCNd64, &values[i]) != 1) {
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
        if (printf("%" PRId64 "%c", cubes[i], i + 1U == count ? '\n' : ' ') < 0) {
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