#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

void heapify(int *arr, size_t n, size_t i) {
    size_t largest = i;
    size_t left = 2 * i + 1;
    size_t right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

int heap_queue(int **arr, size_t n) {
    if (arr == NULL || *arr == NULL) {
        return -1;
    }

    if (n <= 1) {
        return 0;
    }

    for (size_t i = n / 2; i-- > 0;) {
        heapify(*arr, n, i);
    }

    return 0;
}

int main(void) {
    int *arr = malloc(6 * sizeof(int));
    if (arr == NULL) {
        return EXIT_FAILURE;
    }

    arr[0] = 12;
    arr[1] = 11;
    arr[2] = 13;
    arr[3] = 5;
    arr[4] = 6;
    arr[5] = 7;

    size_t n = 6;

    if (heap_queue(&arr, n) != 0) {
        free(arr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    return EXIT_SUCCESS;
}