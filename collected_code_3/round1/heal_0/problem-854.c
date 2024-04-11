#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* data;
    int size;
    int capacity;
} Heap;

Heap* createHeap(int capacity) {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    heap->data = (int*)malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(Heap* heap, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap->size && heap->data[left] > heap->data[largest])
        largest = left;

    if (right < heap->size && heap->data[right] > heap->data[largest])
        largest = right;

    if (largest != i) {
        swap(&heap->data[i], &heap->data[largest]);
        heapify(heap, largest);
    }
}

void insertHeap(Heap* heap, int value) {
    if (heap->size == heap->capacity) {
        return;
    }

    heap->data[heap->size] = value;
    heap->size++;

    for (int i = heap->size / 2 - 1; i >= 0; i--)
        heapify(heap, i);
}

Heap* convertListToHeap(int* list, int size) {
    Heap* heap = createHeap(size);
    for (int i = 0; i < size; i++) {
        insertHeap(heap, list[i]);
    }
    return heap;
}

int main() {
    int list[] = {12, 11, 13, 5, 6, 7};
    int size = sizeof(list) / sizeof(list[0]);

    Heap* heap = convertListToHeap(list, size);

    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->data[i]);
    }

    free(heap->data);
    free(heap);

    return 0;
}