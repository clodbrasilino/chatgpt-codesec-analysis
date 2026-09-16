#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

static int compare_ints(const void *lhs, const void *rhs)
{
    const int left = *(const int *)lhs;
    const int right = *(const int *)rhs;

    return (left > right) - (left < right);
}

static bool has_triplet_with_sum(const int *array, size_t length, int target)
{
    int *sorted = NULL;
    bool found = false;

    if (array == NULL || length < 3U || length > SIZE_MAX / sizeof(*sorted)) {
        return false;
    }

    sorted = malloc(length * sizeof(*sorted));
    if (sorted == NULL) {
        return false;
    }

    for (size_t i = 0U; i < length; ++i) {
        sorted[i] = array[i];
    }

    qsort(sorted, length, sizeof(*sorted), compare_ints);

    for (size_t i = 0U; i < length - 2U && !found; ++i) {
        size_t left = i + 1U;
        size_t right = length - 1U;

        while (left < right) {
            const int64_t sum = (int64_t)sorted[i] +
                                (int64_t)sorted[left] +
                                (int64_t)sorted[right];

            if (sum == (int64_t)target) {
                found = true;
                break;
            }

            if (sum < (int64_t)target) {
                ++left;
            } else {
                --right;
            }
        }
    }

    free(sorted);
    return found;
}

int main(void)
{
    int array[] = {1, 4, 45, 6, 10, 8};
    const size_t length = sizeof(array) / sizeof(array[0]);
    const int target = 22;

    if (has_triplet_with_sum(array, length, target)) {
        puts("Triplet found");
    } else {
        puts("Triplet not found");
    }

    return EXIT_SUCCESS;
}