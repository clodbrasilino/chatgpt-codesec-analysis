#include <stdio.h>
#include <stdlib.h>

static int count_rotations(const int *arr, size_t n)
{
    size_t low;
    size_t high;

    if (arr == NULL || n == 0U) {
        return -1;
    }

    low = 0U;
    high = n - 1U;

    while (low < high) {
        size_t mid = low + ((high - low) / 2U);

        if (arr[mid] > arr[high]) {
            low = mid + 1U;
        } else if (arr[mid] < arr[high]) {
            high = mid;
        } else {
            high--;
        }
    }

    return (int)low;
}

int main(void)
{
    int arr1[] = {15, 18, 2, 3, 6, 12};
    int arr2[] = {7, 9, 11, 12, 5};
    int arr3[] = {7, 9, 11, 12, 15, 18, 2};
    size_t n1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t n2 = sizeof(arr2) / sizeof(arr2[0]);
    size_t n3 = sizeof(arr3) / sizeof(arr3[0]);
    int rotations;

    rotations = count_rotations(arr1, n1);
    if (rotations < 0) {
        if (fprintf(stderr, "Invalid input array\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }
    if (printf("Number of rotations: %d\n", rotations) < 0) {
        return EXIT_FAILURE;
    }

    rotations = count_rotations(arr2, n2);
    if (rotations < 0) {
        if (fprintf(stderr, "Invalid input array\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }
    if (printf("Number of rotations: %d\n", rotations) < 0) {
        return EXIT_FAILURE;
    }

    rotations = count_rotations(arr3, n3);
    if (rotations < 0) {
        if (fprintf(stderr, "Invalid input array\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }
    if (printf("Number of rotations: %d\n", rotations) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}