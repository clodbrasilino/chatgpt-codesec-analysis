#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

static int add_int64_checked(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    if ((b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int max_non_adjacent_sum(const int64_t *array, size_t length, int64_t *result)
{
    int64_t include = 0;
    int64_t exclude = 0;

    if (result == NULL || (array == NULL && length != 0U)) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        int64_t next_include = 0;
        int64_t next_exclude = include > exclude ? include : exclude;

        if (!add_int64_checked(exclude, array[i], &next_include)) {
            return 0;
        }

        include = next_include;
        exclude = next_exclude;
    }

    *result = include > exclude ? include : exclude;
    return 1;
}

int main(void)
{
    size_t length = 0;
    int64_t *array = NULL;
    int64_t result = 0;

    if (scanf("%zu", &length) != 1) {
        fputs("Invalid array length\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        fputs("Array is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (length != 0U) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            perror("malloc");
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < length; ++i) {
        if (scanf("%" SCNd64, &array[i]) != 1) {
            fputs("Invalid array element\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (!max_non_adjacent_sum(array, length, &result)) {
        fputs("Unable to calculate the sum\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}