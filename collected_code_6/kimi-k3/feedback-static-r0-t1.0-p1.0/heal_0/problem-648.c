#include <stdio.h>
#include <stdlib.h>

void exchange_nth(int *arr, size_t size, size_t n) {
    if (arr == NULL || n == 0 || size < n + 1) {
        return;
    }
    for (size_t i = n - 1; i + 1 < size; i += n) {
        int temp = arr[i];
        arr[i] = arr[i + 1];
        arr[i + 1] = temp;
    }
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    size_t n = 2;

    printf("Original array: ");
    for (size_t i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    exchange_nth(arr, size, n);

    printf("Modified array: ");
    for (size_t i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}