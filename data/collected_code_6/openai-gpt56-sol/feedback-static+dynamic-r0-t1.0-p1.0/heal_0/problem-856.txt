#include <stdio.h>
#include <stdlib.h>

static int compare_size_t(const void *a, const void *b)
{
    const size_t lhs = *(const size_t *)a;
    const size_t rhs = *(const size_t *)b;

    return (lhs > rhs) - (lhs < rhs);
}

static int minimum_adjacent_swaps(const int *array, size_t length, size_t *result)
{
    size_t *ones = NULL;
    size_t ones_count = 0;
    size_t zeros_seen = 0;
    size_t swaps_zeros_first = 0;
    size_t swaps_ones_first = 0;

    if (result == NULL || (array == NULL && length != 0)) {
        return 0;
    }

    if (length > 0) {
        ones = malloc(length * sizeof(*ones));
        if (ones == NULL) {
            return 0;
        }
    }

    for (size_t i = 0; i < length; ++i) {
        if (array[i] == 0) {
            if (swaps_zeros_first > SIZE_MAX - ones_count) {
                free(ones);
                return 0;
            }
            swaps_zeros_first += ones_count;
            ++zeros_seen;
        } else if (array[i] == 1) {
            if (swaps_ones_first > SIZE_MAX - zeros_seen) {
                free(ones);
                return 0;
            }
            swaps_ones_first += zeros_seen;
            ones[ones_count++] = i;
        } else {
            free(ones);
            return 0;
        }
    }

    qsort(ones, ones_count, sizeof(*ones), compare_size_t);
    *result = swaps_zeros_first < swaps_ones_first
                  ? swaps_zeros_first
                  : swaps_ones_first;

    free(ones);
    return 1;
}

int main(void)
{
    size_t length = 0;
    size_t swaps = 0;
    int *array = NULL;

    if (scanf("%zu", &length) != 1) {
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        return EXIT_FAILURE;
    }

    if (length > 0) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < length; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (!minimum_adjacent_swaps(array, length, &swaps)) {
        free(array);
        return EXIT_FAILURE;
    }

    printf("%zu\n", swaps);
    free(array);
    return EXIT_SUCCESS;
}