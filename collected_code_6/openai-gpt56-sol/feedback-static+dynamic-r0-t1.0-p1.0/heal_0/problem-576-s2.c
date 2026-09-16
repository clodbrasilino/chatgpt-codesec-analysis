#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool is_subarray(const int array[], size_t array_size,
                        const int candidate[], size_t candidate_size)
{
    if (candidate_size == 0U) {
        return true;
    }

    if (array == NULL || candidate == NULL || candidate_size > array_size) {
        return false;
    }

    for (size_t i = 0U; i <= array_size - candidate_size; ++i) {
        size_t j = 0U;

        while (j < candidate_size && array[i + j] == candidate[j]) {
            ++j;
        }

        if (j == candidate_size) {
            return true;
        }
    }

    return false;
}

int main(void)
{
    const int array[] = {1, 2, 3, 4, 5, 6};
    const int candidate[] = {3, 4, 5};
    const size_t array_size = sizeof(array) / sizeof(array[0]);
    const size_t candidate_size = sizeof(candidate) / sizeof(candidate[0]);

    if (is_subarray(array, array_size, candidate, candidate_size)) {
        (void)printf("The candidate is a subarray.\n");
    } else {
        (void)printf("The candidate is not a subarray.\n");
    }

    return 0;
}