#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_second_smallest(int *arr, size_t size) {
    if (arr == NULL || size < 2) {
        return INT_MIN;
    }

    int smallest = (arr[0] < arr[1]) ? arr[0] : arr[1];
    int second_smallest = (arr[0] < arr[1]) ? arr[1] : arr[0];

    for (size_t i = 2; i < size; i++) {
        if (arr[i] < smallest) {
            second_smallest = smallest;
            smallest = arr[i];
        } else if (arr[i] < second_smallest && arr[i] != smallest) {
            second_smallest = arr[i];
        }
    }

    if (second_smallest == smallest) {
        return INT_MIN;
    }

    return second_smallest;
}

int main(void) {
    int arr1[] = {12, 13, 1, 10, 34, 1};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    int result1 = find_second_smallest(arr1, size1);
    printf("%d\n", result1);

    int arr2[] = {5, 5, 5, 5};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    int result2 = find_second_smallest(arr2, size2);
    printf("%d\n", result2);

    int arr3[] = {2, 1};
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);
    int result3 = find_second_smallest(arr3, size3);
    printf("%d\n", result3);

    int *arr4 = NULL;
    size_t size4 = 0;
    int result4 = find_second_smallest(arr4, size4);
    printf("%d\n", result4);

    return 0;
}