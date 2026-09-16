#include <stdio.h>
#include <stdlib.h>

static int compare_size_t(const void *lhs, const void *rhs)
{
    const size_t a = *(const size_t *)lhs;
    const size_t b = *(const size_t *)rhs;

    return (a > b) - (a < b);
}

static int minimum_adjacent_swaps(const int *array, size_t length, size_t *result)
{
    size_t *ones = NULL;
    size_t *adjusted = NULL;
    size_t one_count = 0;
    size_t index = 0;
    size_t median = 0;
    size_t swaps = 0;

    if (result == NULL || (array == NULL && length != 0)) {
        return -1;
    }

    *result = 0;

    for (size_t i = 0; i < length; ++i) {
        if (array[i] != 0 && array[i] != 1) {
            return -1;
        }

        if (array[i] == 1) {
            ++one_count;
        }
    }

    if (one_count < 2) {
        return 0;
    }

    if (one_count > SIZE_MAX / sizeof(*ones)) {
        return -1;
    }

    ones = malloc(one_count * sizeof(*ones));
    adjusted = malloc(one_count * sizeof(*adjusted));

    if (ones == NULL || adjusted == NULL) {
        free(ones);
        free(adjusted);
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        if (array[i] == 1) {
            ones[index++] = i;
        }
    }

    for (size_t i = 0; i < one_count; ++i) {
        adjusted[i] = ones[i] - i;
    }

    qsort(adjusted, one_count, sizeof(*adjusted), compare_size_t);
    median = adjusted[one_count / 2];

    for (size_t i = 0; i < one_count; ++i) {
        size_t difference = adjusted[i] > median
                                ? adjusted[i] - median
                                : median - adjusted[i];

        if (swaps > SIZE_MAX - difference) {
            free(ones);
            free(adjusted);
            return -1;
        }

        swaps += difference;
    }

    free(ones);
    free(adjusted);
    *result = swaps;
    return 0;
}

int main(void)
{
    int array[] = {1, 0, 1, 0, 1};
    size_t length = sizeof(array) / sizeof(array[0]);
    size_t swaps = 0;

    if (minimum_adjacent_swaps(array, length, &swaps) != 0) {
        fputs("Unable to calculate the minimum swaps.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", swaps) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}