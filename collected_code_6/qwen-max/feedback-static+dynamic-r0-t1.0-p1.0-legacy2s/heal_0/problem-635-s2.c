#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *array;
    size_t size;
    size_t count;
} MinHeap;

void minHeapify(MinHeap *heap, size_t i) {
    size_t smallest = i;
    size_t left = 2 * i + 1;
    size_t right = 2 * i + 2;

    if (left < heap->count && heap->array[left] < heap->array[smallest])
        smallest = left;

    if (right < heap->count && heap->array[right] < heap->array[smallest])
        smallest = right;

    if (smallest != i) {
        int temp = heap->array[i];
        heap->array[i] = heap->array[smallest];
        heap->array[smallest] = temp;
        minHeapify(heap, smallest);
    }
}

void push(MinHeap *heap, int val) {
    if (heap->count == heap->size) {
        heap->size *= 2;
        heap->array = realloc(heap->array, heap->size * sizeof(int));
    }
    heap->array[heap->count] = val;
    size_t i = heap->count;
    while (i != 0 && heap->array[(i - 1) / 2] > heap->array[i]) {
        int temp = heap->array[i];
        heap->array[i] = heap->array[(i - 1) / 2];
        heap->array[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
    heap->count++;
}

int pop(MinHeap *heap) {
    if (heap->count == 0) {
        return -1; // Assuming -1 indicates an error
    }
    int root = heap->array[0];
    heap->array[0] = heap->array[heap->count - 1];
    heap->count--;
    minHeapify(heap, 0);
    return root;
}

MinHeap *createHeap(size_t initialSize) {
    MinHeap *heap = (MinHeap *)malloc(sizeof(MinHeap));
    if (!heap) exit(EXIT_FAILURE);
    heap->array = (int *)malloc(initialSize * sizeof(int));
    if (!heap->array) {
        free(heap);
        exit(EXIT_FAILURE);
    }
    heap->size = initialSize;
    heap->count = 0;
    return heap;
}

void freeHeap(MinHeap *heap) {
    free(heap->array);
    free(heap);
}

int main() {
    MinHeap *heap = createHeap(5);

    int values[] = {3, 1, 8, 2, 5};
    for (size_t i = 0; i < 5; ++i) {
        push(heap, values[i]);
    }

    for (size_t i = 0; i < 5; ++i) {
        int val = pop(heap);
        if (val != -1) {
            printf("%d ", val);
        } else {
            break;
        }
    }
    printf("\n");

    freeHeap(heap);
    return 0;
}