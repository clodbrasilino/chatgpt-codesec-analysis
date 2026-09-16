#include <stdio.h>
#include <stdlib.h>

static int compare_ints(const void *left, const void *right)
{
    const int a = *(const int *)left;
    const int b = *(const int *)right;

    return (a > b) - (a < b);
}

static void find_pairs(const int *array, size_t length, int target)
{
    int *sorted;
    size_t left;
    size_t right;

    if (array == NULL || length < 2) {
        return;
    }

    if (length > SIZE_MAX / sizeof(*sorted)) {
        fprintf(stderr, "Array is too large\n");
        return;
    }

    sorted = malloc(length * sizeof(*sorted));
    if (sorted == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    for (size_t i = 0; i < length; ++i) {
        sorted[i] = array[i];
    }

    qsort(sorted, length, sizeof(*sorted), compare_ints);

    left = 0;
    right = length - 1;

    while (left < right) {
        const long long sum = (long long)sorted[left] + sorted[right];

        if (sum == target) {
            const int left_value = sorted[left];
            const int right_value = sorted[right];

            printf("(%d, %d)\n", left_value, right_value);

            while (left < right && sorted[left] == left_value) {
                ++left;
            }

            while (left < right && sorted[right] == right_value) {
                --right;
            }
        } else if (sum < target) {
            ++left;
        } else {
            --right;
        }
    }

    free(sorted);
}

int main(void)
{
    int array[] = {1, 5, 7, -1, 5, 2, 4, 3};
    const size_t length = sizeof(array) / sizeof(array[0]);
    const int target = 6;

    find_pairs(array, length, target);

    if (ferror(stdout)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}