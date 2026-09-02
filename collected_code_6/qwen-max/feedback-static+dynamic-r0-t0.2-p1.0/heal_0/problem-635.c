#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *array;
    int size;
    int capacity;
} MinHeap;

MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->array = (int*)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    return minHeap;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap* minHeap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < minHeap->size && minHeap->array[left] < minHeap->array[smallest])
        smallest = left;

    if (right < minHeap->size && minHeap->array[right] < minHeap->array[smallest])
        smallest = right;

    if (smallest != index) {
        swap(&minHeap->array[index], &minHeap->array[smallest]);
        minHeapify(minHeap, smallest);
    }
}

void insertMinHeap(MinHeap* minHeap, int value) {
    if (minHeap->size == minHeap->capacity) {
        minHeap->capacity *= 2;
        minHeap->array = (int*)realloc(minHeap->array, minHeap->capacity * sizeof(int));
    }

    int i = minHeap->size;
    minHeap->array[i] = value;
    minHeap->size++;

    while (i != 0 && minHeap->array[(i - 1) / 2] > minHeap->array[i]) {
        swap(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int extractMin(MinHeap* minHeap) {
    if (minHeap->size <= 0) return -1;
    if (minHeap->size == 1) {
        minHeap->size--;
        return minHeap->array[0];
    }

    int root = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    minHeap->size--;
    minHeapify(minHeap, 0);

    return root;
}

void deleteMinHeap(MinHeap* minHeap) {
    free(minHeap->array);
    free(minHeap);
}

int main() {
    MinHeap* minHeap = createMinHeap(10);
    int values[] = {3, 2, 15, 5, 4, 45, 6, 6, 7, 8, 9};
    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; ++i) {
        insertMinHeap(minHeap, values[i]);
    }

    for (int i = 0; i < n; ++i) {
        printf("%d ", extractMin(minHeap));
    }

    deleteMinHeap(minHeap);
    return 0;
}