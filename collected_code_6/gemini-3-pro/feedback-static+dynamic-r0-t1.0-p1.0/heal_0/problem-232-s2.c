#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void min_heapify(int heap[], int size, int i) {
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
        min_heapify(heap, size, smallest);
    }
}

int* get_n_largest(const int dataset[], size_t dataset_size, size_t n) {
    if (dataset == NULL || dataset_size == 0 || n == 0) {
        return NULL;
    }

    if (n > dataset_size) {
        n = dataset_size;
    }

    int *heap = (int *)malloc(n * sizeof(int));
    if (heap == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < n; i++) {
        heap[i] = dataset[i];
    }

    for (int i = (n / 2) - 1; i >= 0; i--) {
        min_heapify(heap, n, i);
    }

    for (size_t i = n; i < dataset_size; i++) {
        if (dataset[i] > heap[0]) {
            heap[0] = dataset[i];
            min_heapify(heap, n, 0);
        }
    }

    return heap;
}

int main(void) {
    int dataset[] = {10, 5, 20, 8, 15, 30, 25, 3, 12};
    size_t dataset_size = sizeof(dataset) / sizeof(dataset[0]);
    size_t n = 3;

    int *largest = get_n_largest(dataset, dataset_size, n);

    if (largest != NULL) {
        for (size_t i = 0; i < n; i++) {
            printf("%d ", largest[i]);
        }
        printf("\n");
        free(largest);
    }

    return 0;
}