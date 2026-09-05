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

        size_t val = (size_t)arr[i];
        while (arr[i] != arr[val - 1]) {
            if (arr[i] <= 0 || arr[i] > size) {
                break;
            }
            val = (size_t)arr[i];
            if (val - 1 < size) {
                int temp = arr[val - 1];
                arr[val - 1] = arr[i];
                arr[i] = temp;
            }
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
    printf("%d\n", find_smallest_missing(arr1, size1));

    int arr2[] = {1, 2, 0};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    printf("%d\n", find_smallest_missing(arr2, size2));

    int arr3[] = {7, 8, 9, 11, 12};
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);
    printf("%d\n", find_smallest_missing(arr3, size3));

    return 0;
}