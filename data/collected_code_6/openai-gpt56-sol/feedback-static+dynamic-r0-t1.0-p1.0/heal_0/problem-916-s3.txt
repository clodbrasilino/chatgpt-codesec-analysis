#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

static int compare_ints(const void *lhs, const void *rhs)
{
    const int a = *(const int *)lhs;
    const int b = *(const int *)rhs;

    return (a > b) - (a < b);
}

static bool find_triplet(const int *array, size_t length, int target,
                         int *first, int *second, int *third)
{
    if (array == NULL || first == NULL || second == NULL || third == NULL ||
        length < 3U || length > SIZE_MAX / sizeof(*array)) {
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
            const int64_t sum = (int64_t)sorted[i] +
                                (int64_t)sorted[left] +
                                (int64_t)sorted[right];

            if (sum == (int64_t)target) {
                *first = sorted[i];
                *second = sorted[left];
                *third = sorted[right];
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
    int array[] = {12, 3, 4, 1, 6, 9};
    const size_t length = sizeof(array) / sizeof(array[0]);
    const int target = 24;
    int first = 0;
    int second = 0;
    int third = 0;

    if (find_triplet(array, length, target, &first, &second, &third)) {
        if (printf("%d %d %d\n", first, second, third) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("No triplet found\n") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}