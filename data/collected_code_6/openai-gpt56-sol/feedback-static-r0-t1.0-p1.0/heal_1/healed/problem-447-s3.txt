#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int cube_elements(const intmax_t *input, intmax_t *output, size_t count)
{
    if (count != 0U && (input == NULL || output == NULL)) {
        return -1;
    }

    for (size_t i = 0U; i < count; ++i) {
        const intmax_t value = input[i];

        if (value != 0 &&
            ((value > 0 && value > INTMAX_MAX / value) ||
             (value < 0 && value < INTMAX_MAX / value))) {
            return -1;
        }

        const intmax_t square = value * value;

        if ((value > 0 && square > INTMAX_MAX / value) ||
            (value < 0 && square > INTMAX_MIN / value)) {
            return -1;
        }

        output[i] = square * value;
    }

    return 0;
}

int main(void)
{
    size_t count = 0U;

    if (scanf("%zu", &count) != 1) {
        fputs("Invalid element count\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(intmax_t)) {
        fputs("Element count is too large\n", stderr);
        return EXIT_FAILURE;
    }

    intmax_t *values = NULL;
    intmax_t *cubes = NULL;

    if (count != 0U) {
        values = malloc(count * sizeof(*values));
        cubes = malloc(count * sizeof(*cubes));

        if (values == NULL || cubes == NULL) {
            free(values);
            free(cubes);
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0U; i < count; ++i) {
        if (scanf("%" SCNdMAX, &values[i]) != 1) {
            fputs("Invalid element\n", stderr);
            free(values);
            free(cubes);
            return EXIT_FAILURE;
        }
    }

    if (cube_elements(values, cubes, count) != 0) {
        fputs("Cube calculation overflow\n", stderr);
        free(values);
        free(cubes);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (printf("%" PRIdMAX "%c", cubes[i],
                   i + 1U == count ? '\n' : ' ') < 0) {
            free(values);
            free(cubes);
            return EXIT_FAILURE;
        }
    }

    free(values);
    free(cubes);
    return EXIT_SUCCESS;
}