#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

static int compare_ints(const void *lhs, const void *rhs)
{
    const int a = *(const int *)lhs;
    const int b = *(const int *)rhs;

    return (a > b) - (a < b);
}

static void find_pairs(const int *array, size_t length, int target)
{
    int *sorted;
    size_t left;
    size_t right;

    if (array == NULL || length < 2U) {
        return;
    }

    if (length > SIZE_MAX / sizeof(*sorted)) {
        fputs("Array is too large.\n", stderr);
        return;
    }

    sorted = malloc(length * sizeof(*sorted));
    if (sorted == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return;
    }

    for (size_t i = 0U; i < length; ++i) {
        sorted[i] = array[i];
    }

    qsort(sorted, length, sizeof(*sorted), compare_ints);

    left = 0U;
    right = length - 1U;

    while (left < right) {
        const long long sum = (long long)sorted[left] + (long long)sorted[right];

        if (sum == (long long)target) {
            printf("(%d, %d)\n", sorted[left], sorted[right]);

            const int left_value = sorted[left];
            const int right_value = sorted[right];

            while (left < right && sorted[left] == left_value) {
                ++left;
            }

            while (left < right && sorted[right] == right_value) {
                --right;
            }
        } else if (sum < (long long)target) {
            ++left;
        } else {
            --right;
        }
    }

    free(sorted);
}

int main(void)
{
    const int values[] = {1, 5, 7, -1, 5, 3, 9, 0};
    const size_t length = sizeof(values) / sizeof(values[0]);
    const int target = 6;

    find_pairs(values, length, target);

    return EXIT_SUCCESS;
}