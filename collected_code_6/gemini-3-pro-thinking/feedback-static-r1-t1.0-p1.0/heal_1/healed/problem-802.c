#include <stdio.h>
#include <stddef.h>

size_t count_rotations(const int *arr, size_t n) {
    if (arr == NULL || n == 0) {
        return 0;
    }

    size_t low = 0;
    size_t high = n - 1;

    while (low < high) {
        if (arr[low] <= arr[high]) {
            return low;
        }

        size_t mid = low + (high - low) / 2;

        if (arr[mid] > arr[high]) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }

    return low;
}

int main(void) {
    const int arr1[] = {15, 18, 2, 3, 6, 12};
    const int arr2[] = {7, 9, 11, 12, 5};
    const int arr3[] = {1, 2, 3, 4, 5};
    
    size_t n1 = sizeof(arr1) / sizeof(arr1[0]);
    size_t n2 = sizeof(arr2) / sizeof(arr2[0]);
    size_t n3 = sizeof(arr3) / sizeof(arr3[0]);

    if (printf("%zu\n", count_rotations(arr1, n1)) < 0) {
        return 1;
    }
    if (printf("%zu\n", count_rotations(arr2, n2)) < 0) {
        return 1;
    }
    if (printf("%zu\n", count_rotations(arr3, n3)) < 0) {
        return 1;
    }

    return 0;
}