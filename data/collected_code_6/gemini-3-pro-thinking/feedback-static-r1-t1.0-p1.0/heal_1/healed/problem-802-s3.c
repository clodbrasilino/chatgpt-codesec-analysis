#include <stdio.h>
#include <stddef.h>

long count_rotations(const int *arr, size_t n) {
    if (arr == NULL || n == 0) {
        return -1;
    }

    size_t low = 0;
    size_t high = n - 1;

    while (low < high) {
        size_t mid = low + (high - low) / 2;

        if (arr[mid] > arr[high]) {
            low = mid + 1;
        } else if (arr[mid] < arr[high]) {
            high = mid;
        } else {
            high--;
        }
    }

    return (long)low;
}

int main(void) {
    int arr1[] = {15, 18, 2, 3, 6, 12};
    size_t n1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%ld\n", count_rotations(arr1, n1));

    int arr2[] = {7, 9, 11, 12, 5};
    size_t n2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%ld\n", count_rotations(arr2, n2));

    int arr3[] = {1, 2, 3, 4, 5};
    size_t n3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%ld\n", count_rotations(arr3, n3));

    printf("%ld\n", count_rotations(NULL, 0));

    return 0;
}