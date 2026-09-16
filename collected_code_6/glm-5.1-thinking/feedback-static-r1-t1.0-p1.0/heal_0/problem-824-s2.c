#include <stdio.h>

size_t remove_even(int *arr, size_t size) {
    if (arr == NULL) {
        return 0;
    }
    size_t new_size = 0;
    for (size_t i = 0; i < size; i++) {
        if (arr[i] % 2 != 0) {
            arr[new_size++] = arr[i];
        }
    }
    return new_size;
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    size_t new_size = remove_even(arr, size);
    for (size_t i = 0; i < new_size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}