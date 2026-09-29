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

static bool find_triplet_with_sum(const int *array, size_t length, long long target,
                                  int *first, int *second, int *third)
{
    int *sorted = NULL;
    bool found = false;

    if (array == NULL || first == NULL || second == NULL || third == NULL ||
        length < 3 || length > SIZE_MAX / sizeof(*sorted)) {
        return false;
    }

    sorted = malloc(length * sizeof(*sorted));
    if (sorted == NULL) {
        return false;
    }

    for (size_t i = 0; i < length; ++i) {
        sorted[i] = array[i];
    }

    qsort(sorted, length, sizeof(*sorted), compare_ints);

    for (size_t i = 0; i + 2 < length && !found; ++i) {
        size_t left = i + 1;
        size_t right = length - 1;

        while (left < right) {
            const long long sum = (long long)sorted[i] +
                                  (long long)sorted[left] +
                                  (long long)sorted[right];

            if (sum == target) {
                *first = sorted[i];
                *second = sorted[left];
                *third = sorted[right];
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
    int first = 0;
    int second = 0;
    int third = 0;

    if (find_triplet_with_sum(array, length, target, &first, &second, &third)) {
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