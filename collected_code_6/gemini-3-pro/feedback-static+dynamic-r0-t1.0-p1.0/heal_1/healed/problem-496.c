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

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void buildMaxHeap(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
}

int* findSmallest(const int arr[], int n, int k, int *out_count) {
    if (arr == NULL || n <= 0 || k <= 0 || out_count == NULL) {
        if (out_count) *out_count = 0;
        return NULL;
    }

    if (k > n) k = n;

    int *heap = (int *)malloc(k * sizeof(int));
    if (heap == NULL) {
        *out_count = 0;
        return NULL;
    }

    for (int i = 0; i < k; i++) {
        heap[i] = arr[i];
    }

    buildMaxHeap(heap, k);

    for (int i = k; i < n; i++) {
        if (arr[i] < heap[0]) {
            heap[0] = arr[i];
            heapify(heap, k, 0);
        }
    }

    *out_count = k;
    return heap;
}

int main(void) {
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 4;
    int out_count = 0;

    int *smallest_elements = findSmallest(arr, n, k, &out_count);

    if (smallest_elements != NULL) {
        for (int i = 0; i < out_count; i++) {
            printf("%d ", smallest_elements[i]);
        }
        printf("\n");
        free(smallest_elements);
    } else {
        printf("Failed to find smallest elements or invalid input.\n");
    }

    return 0;
}