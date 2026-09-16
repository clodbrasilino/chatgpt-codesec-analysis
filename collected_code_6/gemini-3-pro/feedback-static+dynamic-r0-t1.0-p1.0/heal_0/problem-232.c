#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(int heap[], int size, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && heap[left] < heap[smallest]) {
        smallest = left;
    }
    if (right < size && heap[right] < heap[smallest]) {
        smallest = right;
    }
    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        minHeapify(heap, size, smallest);
    }
}

void buildMinHeap(int heap[], int size) {
    for (int i = size / 2 - 1; i >= 0; i--) {
        minHeapify(heap, size, i);
    }
}

int* getNLargest(const int dataset[], int dataset_size, int n, int *result_size) {
    if (dataset == NULL || dataset_size <= 0 || n <= 0 || result_size == NULL) {
        if (result_size != NULL) {
            *result_size = 0;
        }
        return NULL;
    }

    if (n > dataset_size) {
        n = dataset_size;
    }

    int *heap = (int *)malloc(n * sizeof(int));
    if (heap == NULL) {
        *result_size = 0;
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        heap[i] = dataset[i];
    }

    buildMinHeap(heap, n);

    for (int i = n; i < dataset_size; i++) {
        if (dataset[i] > heap[0]) {
            heap[0] = dataset[i];
            minHeapify(heap, n, 0);
        }
    }

    *result_size = n;
    return heap;
}

int main() {
    int dataset[] = {10, 4, 25, 1, 9, 34, 15, 2, 7, 21};
    int dataset_size = sizeof(dataset) / sizeof(dataset[0]);
    int n = 3;
    int result_size = 0;

    int *largest = getNLargest(dataset, dataset_size, n, &result_size);

    if (largest != NULL) {
        for (int i = 0; i < result_size; i++) {
            printf("%d ", largest[i]);
        }
        printf("\n");
        free(largest);
    }

    return 0;
}