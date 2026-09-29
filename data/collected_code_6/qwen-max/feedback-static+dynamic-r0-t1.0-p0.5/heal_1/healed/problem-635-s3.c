#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *array;
    size_t capacity;
    size_t count;
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

    if (left < heap->count && heap->array[left] < heap->array[smallest]) {
        smallest = left;
    }

    if (right < heap->count && heap->array[right] < heap->array[smallest]) {
        smallest = right;
    }

    if (smallest != index) {
        swap(&heap->array[index], &heap->array[smallest]);
        minHeapify(heap, smallest);
    }
}

void push(MinHeap *heap, int value) {
    if (heap->count == heap->capacity) {
        if (heap->capacity == 0) {
            heap->capacity = 1;
        } else {
            heap->capacity *= 2;
        }
        heap->array = realloc(heap->array, heap->capacity * sizeof(int));
    }
    size_t i = heap->count;
    heap->array[i] = value;
    while (i > 0 && heap->array[(i - 1) / 2] > heap->array[i]) {
        swap(&heap->array[i], &heap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
    heap->count++;
}

int pop(MinHeap *heap) {
    if (heap->count == 0) {
        return -1; // Indicate error
    }
    int root = heap->array[0];
    heap->array[0] = heap->array[heap->count - 1];
    heap->count--;
    minHeapify(heap, 0);
    return root;
}

void freeHeap(MinHeap *heap) {
    free(heap->array);
    heap->array = NULL;
    heap->capacity = 0;
    heap->count = 0;
}

int main() {
    MinHeap heap = {NULL, 0, 0};
    int values[] = {3, 1, 5, 2, 4, 6};
    size_t n = sizeof(values) / sizeof(values[0]);

    for (size_t i = 0; i < n; ++i) {
        push(&heap, values[i]);
    }

    for (size_t i = 0; i < n; ++i) {
        int val = pop(&heap);
        if (val != -1) {
            printf("%d ", val);
        }
    }
    printf("\n");

    freeHeap(&heap);
    return 0;
}