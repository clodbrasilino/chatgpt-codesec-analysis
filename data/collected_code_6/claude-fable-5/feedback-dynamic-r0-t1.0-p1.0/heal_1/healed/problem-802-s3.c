#include <stdio.h>
#include <stdlib.h>

int count_rotations(const int *arr, int n);

int count_rotations(const int *arr, int n)
{
    int low;
    int high;
    int mid;

    if (arr == NULL || n <= 0) {
        return -1;
    }

    low = 0;
    high = n - 1;

    while (low < high) {
        if (arr[low] <= arr[high]) {
            return low;
        }

        mid = low + (high - low) / 2;

        if (arr[mid] >= arr[low]) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }

    return low;
}

int main(void)
{
    int arr1[] = {15, 18, 2, 3, 6, 12};
    int arr2[] = {7, 9, 11, 12, 5};
    int arr3[] = {1, 2, 3, 4, 5};
    int n1 = (int)(sizeof(arr1) / sizeof(arr1[0]));
    int n2 = (int)(sizeof(arr2) / sizeof(arr2[0]));
    int n3 = (int)(sizeof(arr3) / sizeof(arr3[0]));
    int result;

    result = count_rotations(arr1, n1);
    if (result < 0) {
        fprintf(stderr, "Error computing rotations for arr1\n");
        return EXIT_FAILURE;
    }
    printf("Rotations for arr1: %d\n", result);

    result = count_rotations(arr2, n2);
    if (result < 0) {
        fprintf(stderr, "Error computing rotations for arr2\n");
        return EXIT_FAILURE;
    }
    printf("Rotations for arr2: %d\n", result);

    result = count_rotations(arr3, n3);
    if (result < 0) {
        fprintf(stderr, "Error computing rotations for arr3\n");
        return EXIT_FAILURE;
    }
    printf("Rotations for arr3: %d\n", result);

    return EXIT_SUCCESS;
}