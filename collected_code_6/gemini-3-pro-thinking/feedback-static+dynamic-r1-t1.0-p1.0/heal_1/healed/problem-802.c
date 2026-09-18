#include <stdio.h>
#include <stddef.h>

size_t count_rotations(const int *arr, size_t n) {
    size_t low;
    size_t high;

    if (arr == NULL || n == 0) {
        return 0;
    }

    low = 0;
    high = n - 1;

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
    size_t n1;
    size_t n2;
    size_t n3;

    n1 = sizeof(arr1) / sizeof(arr1[0]);
    n2 = sizeof(arr2) / sizeof(arr2[0]);
    n3 = sizeof(arr3) / sizeof(arr3[0]);

    if (printf("%lu\n", (unsigned long)count_rotations(arr1, n1)) < 0) {
        return 1;
    }
    if (printf("%lu\n", (unsigned long)count_rotations(arr2, n2)) < 0) {
        return 1;
    }
    if (printf("%lu\n", (unsigned long)count_rotations(arr3, n3)) < 0) {
        return 1;
    }

    return 0;
}