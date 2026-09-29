#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

static int compare_ints(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

static bool has_triplet_with_sum(const int array[], size_t length, long long target)
{
    if (array == NULL || length < 3U) {
        return false;
    }

    int *sorted = malloc(length * sizeof(*sorted));
    if (sorted == NULL) {
        return false;
    }

    for (size_t i = 0U; i < length; ++i) {
        sorted[i] = array[i];
    }

    qsort(sorted, length, sizeof(*sorted), compare_ints);

    bool found = false;

    for (size_t i = 0U; i + 2U < length && !found; ++i) {
        size_t left = i + 1U;
        size_t right = length - 1U;

        while (left < right) {
            const long long sum = (long long)sorted[i]
                                + (long long)sorted[left]
                                + (long long)sorted[right];

            if (sum == target) {
                found = true;
                break;
            }

            if (sum < target) {
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
    int array[] = {12, 3, 4, 1, 6, 9};
    const size_t length = sizeof(array) / sizeof(array[0]);
    const long long target = 24;

    if (has_triplet_with_sum(array, length, target)) {
        printf("Triplet found\n");
    } else {
        printf("Triplet not found\n");
    }

    return EXIT_SUCCESS;
}