#include <stdio.h>
#include <stdlib.h>

int find_smallest_missing(int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return 1;
    }

    for (size_t i = 0; i < size; i++) {
        if (arr[i] <= 0 || arr[i] > size) {
            continue;
        }

        size_t idx = (size_t)arr[i] - 1;
        if (arr[idx] != arr[i]) {
            int temp = arr[idx];
            arr[idx] = arr[i];
            arr[i] = temp;
            i--;
        }
    }

    for (size_t i = 0; i < size; i++) {
        if (arr[i] != (int)(i + 1)) {
            return (int)(i + 1);
        }
    }

    return (int)(size + 1);
}

int main(void) {
    int arr1[] = {3, 4, -1, 1};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    int ret1 = find_smallest_missing(arr1, size1);
    printf("%d\n", ret1);

    int arr2[] = {1, 2, 0};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    int ret2 = find_smallest_missing(arr2, size2);
    printf("%d\n", ret2);

    int arr3[] = {7, 8, 9, 11, 12};
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);
    int ret3 = find_smallest_missing(arr3, size3);
    printf("%d\n", ret3);

    int ret4 = find_smallest_missing(NULL, 0);
    printf("%d\n", ret4);

    return 0;
}