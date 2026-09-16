#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int compare_ints(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

static int find_triplet(const int *array, size_t length, int target,
                        int *first, int *second, int *third)
{
    int *sorted;
    size_t bytes;

    if (array == NULL || first == NULL || second == NULL || third == NULL ||
        length < 3 || length > SIZE_MAX / sizeof(*sorted)) {
        return 0;
    }

    bytes = length * sizeof(*sorted);
    sorted = malloc(bytes);
    if (sorted == NULL) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        sorted[i] = array[i];
    }

    qsort(sorted, length, sizeof(*sorted), compare_ints);

    for (size_t i = 0; i < length - 2; ++i) {
        size_t left = i + 1;
        size_t right = length - 1;

        while (left < right) {
            int64_t sum = (int64_t)sorted[i] +
                          (int64_t)sorted[left] +
                          (int64_t)sorted[right];

            if (sum == (int64_t)target) {
                *first = sorted[i];
                *second = sorted[left];
                *third = sorted[right];
                free(sorted);
                return 1;
            }

            if (sum < (int64_t)target) {
                ++left;
            } else {
                --right;
            }
        }
    }

    free(sorted);
    return 0;
}

int main(void)
{
    size_t length;
    int target;
    int *array = NULL;
    int first;
    int second;
    int third;

    if (scanf("%zu", &length) != 1 || length < 3 ||
        length > SIZE_MAX / sizeof(*array)) {
        return EXIT_FAILURE;
    }

    array = malloc(length * sizeof(*array));
    if (array == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (scanf("%d", &array[i]) != 1) {
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (scanf("%d", &target) != 1) {
        free(array);
        return EXIT_FAILURE;
    }

    if (find_triplet(array, length, target, &first, &second, &third)) {
        printf("%d %d %d\n", first, second, third);
    } else {
        printf("No triplet found\n");
    }

    free(array);
    return EXIT_SUCCESS;
}