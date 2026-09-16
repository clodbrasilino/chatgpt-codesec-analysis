#include <stdio.h>
#include <stdlib.h>

static int compare_ints(const void *a, const void *b)
{
    const int left = *(const int *)a;
    const int right = *(const int *)b;

    return (left > right) - (left < right);
}

static void find_pairs(const int *array, size_t length, int target)
{
    int *copy;
    size_t left = 0;
    size_t right;

    if (array == NULL || length < 2) {
        return;
    }

    if (length > SIZE_MAX / sizeof(*copy)) {
        fputs("Array is too large.\n", stderr);
        return;
    }

    copy = malloc(length * sizeof(*copy));
    if (copy == NULL) {
        fputs("Memory allocation failed.\n", stderr);
        return;
    }

    for (size_t i = 0; i < length; ++i) {
        copy[i] = array[i];
    }

    qsort(copy, length, sizeof(*copy), compare_ints);
    right = length - 1;

    while (left < right) {
        const long long sum = (long long)copy[left] + copy[right];

        if (sum == target) {
            const int left_value = copy[left];
            const int right_value = copy[right];

            printf("(%d, %d)\n", left_value, right_value);

            while (left < right && copy[left] == left_value) {
                ++left;
            }

            while (left < right && copy[right] == right_value) {
                --right;
            }
        } else if (sum < target) {
            ++left;
        } else {
            --right;
        }
    }

    free(copy);
}

int main(void)
{
    int array[] = {1, 5, 7, -1, 5, 3, 9, 2};
    const size_t length = sizeof(array) / sizeof(array[0]);
    const int target = 6;

    find_pairs(array, length, target);

    return EXIT_SUCCESS;
}