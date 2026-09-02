#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool is_sorted(const int *arr, size_t size) {
    if (arr == NULL || size <= 1) {
        return true;
    }
    for (size_t i = 1; i < size; ++i) {
        if (arr[i - 1] > arr[i]) {
            return false;
        }
    }
    return true;
}

int main(void) {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {5, 4, 3, 2, 1};
    int arr3[] = {1, 3, 2, 4, 5};
    int arr4[] = {42};
    int arr5[] = {1, 1, 2, 2, 3};

    printf("arr1 sorted: %s\n", is_sorted(arr1, sizeof(arr1) / sizeof(arr1[0])) ? "true" : "false");
    printf("arr2 sorted: %s\n", is_sorted(arr2, sizeof(arr2) / sizeof(arr2[0])) ? "true" : "false");
    printf("arr3 sorted: %s\n", is_sorted(arr3, sizeof(arr3) / sizeof(arr3[0])) ? "true" : "false");
    printf("arr4 sorted: %s\n", is_sorted(arr4, sizeof(arr4) / sizeof(arr4[0])) ? "true" : "false");
    printf("arr5 sorted: %s\n", is_sorted(arr5, sizeof(arr5) / sizeof(arr5[0])) ? "true" : "false");

    return 0;
}