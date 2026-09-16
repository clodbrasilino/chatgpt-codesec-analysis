#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void exchange_adjacent(int *arr, size_t len) {
    for (size_t i = 0; i + 1 < len; i += 2) {
        swap(&arr[i], &arr[i + 1]);
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6};
    size_t len = sizeof(arr) / sizeof(arr[0]);

    exchange_adjacent(arr, len);

    for (size_t i = 0; i < len; ++i) {
        printf("%d ", arr[i]);
    }

    return 0;
}