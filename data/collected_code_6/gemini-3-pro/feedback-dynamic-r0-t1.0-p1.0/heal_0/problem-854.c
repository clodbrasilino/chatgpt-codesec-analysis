#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void build_heap(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

int main(void) {
    int *arr = NULL;
    int n = 0;
    int capacity = 10;
    
    arr = malloc(capacity * sizeof(int));
    if (arr == NULL) {
        return 1;
    }

    int values[] = {4, 10, 3, 5, 1, 8, 7, 2, 9, 6};
    n = sizeof(values) / sizeof(values[0]);

    if (n > capacity) {
        int *temp = realloc(arr, n * sizeof(int));
        if (temp == NULL) {
            free(arr);
            return 1;
        }
        arr = temp;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = values[i];
    }

    build_heap(arr, n);

    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}