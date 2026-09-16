#include <stdio.h>
#include <stdlib.h>

int find_max_sorted_rotated(int *arr, int size) {
    if (arr == NULL || size <= 0) {
        exit(1);
    }
    if (size == 1) {
        return arr[0];
    }
    int low = 0;
    int high = size - 1;
    while (low <= high) {
        if (arr[low] <= arr[high]) {
            return arr[high];
        }
        int mid = low + (high - low) / 2;
        int next = (mid + 1) % size;
        int prev = (mid - 1 + size) % size;
        if (arr[mid] >= arr[next] && arr[mid] >= arr[prev]) {
            return arr[mid];
        }
        if (arr[mid] >= arr[low]) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return arr[size - 1];
}

int main(void) {
    int arr1[] = {4, 5, 6, 7, 1, 2, 3};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", find_max_sorted_rotated(arr1, size1));

    int arr2[] = {1, 2, 3, 4, 5};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", find_max_sorted_rotated(arr2, size2));

    int arr3[] = {2};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%d\n", find_max_sorted_rotated(arr3, size3));

    return 0;
}