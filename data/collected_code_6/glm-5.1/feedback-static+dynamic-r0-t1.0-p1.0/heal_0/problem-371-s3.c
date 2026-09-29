#include <stdio.h>
#include <stdlib.h>

int find_smallest_missing(int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return 1;
    }

    size_t left = 0;
    size_t right = size;

    while (left < right) {
        size_t mid = left + (right - left) / 2;
        if ((size_t)arr[mid] == mid + 1) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return (int)left + 1;
}

int main(void) {
    int arr1[] = {1, 2, 3, 5, 6};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    printf("%d\n", find_smallest_missing(arr1, size1));

    int arr2[] = {1, 2, 3, 4, 5};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", find_smallest_missing(arr2, size2));

    int arr3[] = {2, 3, 4, 5, 6};
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%d\n", find_smallest_missing(arr3, size3));

    int *arr4 = NULL;
    size_t size4 = 0;
    printf("%d\n", find_smallest_missing(arr4, size4));

    return 0;
}