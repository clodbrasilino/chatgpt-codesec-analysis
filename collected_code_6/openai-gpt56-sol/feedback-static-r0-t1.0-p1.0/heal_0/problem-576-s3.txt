#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int is_subarray(const int *array, size_t array_size,
                       const int *candidate, size_t candidate_size)
{
    size_t i;
    size_t j;

    if (candidate_size == 0U) {
        return 1;
    }

    if (array == NULL || candidate == NULL || candidate_size > array_size) {
        return 0;
    }

    for (i = 0U; i <= array_size - candidate_size; ++i) {
        for (j = 0U; j < candidate_size; ++j) {
            if (array[i + j] != candidate[j]) {
                break;
            }
        }

        if (j == candidate_size) {
            return 1;
        }
    }

    return 0;
}

int main(void)
{
    const int array[] = {1, 2, 3, 4, 5, 6};
    const int candidate[] = {3, 4, 5};
    const size_t array_size = sizeof(array) / sizeof(array[0]);
    const size_t candidate_size = sizeof(candidate) / sizeof(candidate[0]);

    if (is_subarray(array, array_size, candidate, candidate_size) != 0) {
        if (puts("The candidate is a subarray.") == EOF) {
            return EXIT_FAILURE;
        }
    } else {
        if (puts("The candidate is not a subarray.") == EOF) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}