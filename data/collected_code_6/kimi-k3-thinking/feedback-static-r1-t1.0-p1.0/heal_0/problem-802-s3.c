#include <stdio.h>
#include <stddef.h>

int count_rotations(const int arr[], size_t n, size_t *rotations)
{
    size_t i;
    size_t min_index;

    if (arr == NULL || rotations == NULL || n == 0U) {
        return -1;
    }

    min_index = 0U;
    for (i = 1U; i < n; ++i) {
        if (arr[i] < arr[min_index]) {
            min_index = i;
        }
    }

    *rotations = min_index;
    return 0;
}

int main(void)
{
    int arr1[] = {15, 18, 2, 3, 6, 12};
    int arr2[] = {1, 2, 3, 4, 5};
    int arr3[] = {5, 1, 2, 3, 4};
    size_t rotations = 0U;

    if (count_rotations(arr1, sizeof(arr1) / sizeof(arr1[0]), &rotations) != 0) {
        fprintf(stderr, "Error: invalid input for array 1\n");
        return 1;
    }
    printf("Array 1 rotations: %zu\n", rotations);

    if (count_rotations(arr2, sizeof(arr2) / sizeof(arr2[0]), &rotations) != 0) {
        fprintf(stderr, "Error: invalid input for array 2\n");
        return 1;
    }
    printf("Array 2 rotations: %zu\n", rotations);

    if (count_rotations(arr3, sizeof(arr3) / sizeof(arr3[0]), &rotations) != 0) {
        fprintf(stderr, "Error: invalid input for array 3\n");
        return 1;
    }
    printf("Array 3 rotations: %zu\n", rotations);

    return 0;
}