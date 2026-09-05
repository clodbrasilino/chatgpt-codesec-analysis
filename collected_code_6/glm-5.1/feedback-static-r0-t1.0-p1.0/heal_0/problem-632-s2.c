#include <stdio.h>
#include <stdlib.h>

void move_zeroes(int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return;
    }
    size_t write_index = 0;
    for (size_t i = 0; i < size; i++) {
        if (arr[i] != 0) {
            arr[write_index++] = arr[i];
        }
    }
    while (write_index < size) {
        arr[write_index++] = 0;
    }
}

void print_array(const int *arr, size_t size) {
    for (size_t i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void) {
    int arr1[] = {1, 0, 2, 0, 3, 4, 0, 5};
    size_t size1 = sizeof(arr1) / sizeof(arr1[0]);
    move_zeroes(arr1, size1);
    print_array(arr1, size1);

    int arr2[] = {0, 0, 0, 1, 2, 3};
    size_t size2 = sizeof(arr2) / sizeof(arr2[0]);
    move_zeroes(arr2, size2);
    print_array(arr2, size2);

    int arr3[] = {1, 2, 3, 0, 0, 0};
    size_t size3 = sizeof(arr3) / sizeof(arr3[0]);
    move_zeroes(arr3, size3);
    print_array(arr3, size3);

    int *arr4 = NULL;
    move_zeroes(arr4, 0);

    return 0;
}