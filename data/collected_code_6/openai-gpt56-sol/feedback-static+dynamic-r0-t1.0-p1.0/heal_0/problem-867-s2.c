#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

static int minimum_number_to_make_sum_even(
    const int64_t array[],
    size_t length,
    int64_t *result)
{
    int parity = 0;

    if (result == NULL || (array == NULL && length != 0U)) {
        return -1;
    }

    for (size_t i = 0U; i < length; ++i) {
        parity ^= (int)(array[i] & INT64_C(1));
    }

    *result = (int64_t)parity;
    return 0;
}

int main(void)
{
    size_t length = 0U;

    if (scanf("%zu", &length) != 1) {
        fputs("Invalid array length.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(int64_t)) {
        fputs("Array is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    int64_t *array = NULL;

    if (length != 0U) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            fputs("Memory allocation failed.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0U; i < length; ++i) {
        if (scanf("%" SCNd64, &array[i]) != 1) {
            fputs("Invalid array element.\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    int64_t minimum = 0;

    if (minimum_number_to_make_sum_even(array, length, &minimum) != 0) {
        fputs("Unable to compute the result.\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", minimum);
    free(array);
    return EXIT_SUCCESS;
}