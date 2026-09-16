#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int compare_ints(const void *lhs, const void *rhs)
{
    const int left = *(const int *)lhs;
    const int right = *(const int *)rhs;

    return (left > right) - (left < right);
}

static bool is_subset(const int *array, size_t array_size,
                      const int *subset, size_t subset_size)
{
    int *sorted;
    size_t i;

    if (subset_size == 0U) {
        return true;
    }

    if (array == NULL || subset == NULL || subset_size > array_size ||
        array_size > SIZE_MAX / sizeof(*sorted)) {
        return false;
    }

    sorted = malloc(array_size * sizeof(*sorted));
    if (sorted == NULL) {
        return false;
    }

    for (i = 0U; i < array_size; ++i) {
        sorted[i] = array[i];
    }

    qsort(sorted, array_size, sizeof(*sorted), compare_ints);

    for (i = 0U; i < subset_size; ++i) {
        if (bsearch(&subset[i], sorted, array_size, sizeof(*sorted),
                    compare_ints) == NULL) {
            free(sorted);
            return false;
        }
    }

    free(sorted);
    return true;
}

int main(void)
{
    const int array[] = {11, 1, 13, 21, 3, 7};
    const int subset[] = {11, 3, 7, 1};
    const size_t array_size = sizeof(array) / sizeof(array[0]);
    const size_t subset_size = sizeof(subset) / sizeof(subset[0]);

    puts(is_subset(array, array_size, subset, subset_size)
             ? "The second array is a subset of the first."
             : "The second array is not a subset of the first.");

    return EXIT_SUCCESS;
}