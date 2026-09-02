#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *array;
    size_t size;
    size_t capacity;
} MinHeap;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap *heap, size_t index) {
    size_t smallest = index;
    size_t left = 2 * index + 1;
    size_t right = 2 * index + 2;

    if (left < heap->size && heap->array[left] < heap->array[smallest]) {
        smallest = left;
    }

    if (right < heap->size && heap->array[right] < heap->array[smallest]) {
        smallest = right;
    }

    if (smallest != index) {
        swap(&heap->array[index], &heap->array[smallest]);
        minHeapify(heap, smallest);
    }
}

void push(MinHeap *heap, int value) {
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->array = realloc(heap->array, heap->capacity * sizeof(int));
    }
    size_t i = heap->size;
    heap->array[i] = value;
    while (i > 0 && heap->array[(i - 1) / 2] > heap->array[i]) {
        swap(&heap->array[i], &heap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
    heap->size++;
}

int pop(MinHeap *heap) {
    if (heap->size == 0) {
        return -1; // Assuming -1 is an invalid value for the context
    }
    int root = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;
    minHeapify(heap, 0);
    return root;
}

MinHeap* createMinHeap() {
    MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->array = (int*)malloc(10 * sizeof(int));
    heap->size = 0;
    heap->capacity = 10;
    return heap;
}

void freeMinHeap(MinHeap *heap) {
    free(heap->array);
    free(heap);
}

int main() {
    MinHeap *heap = createMinHeap();
    int values[] = {3, 5, 2, 7, 6, 8, 1, 9, 4};
    size_t n = sizeof(values) / sizeof(values[0]);

    for (size_t i = 0; i < n; ++i) {
        push(heap, values[i]);
    }

    for (size_t i = 0; i < n; ++i) {
        printf("%d ", pop(heap));
    }

    freeMinHeap(heap);
    return 0;
}