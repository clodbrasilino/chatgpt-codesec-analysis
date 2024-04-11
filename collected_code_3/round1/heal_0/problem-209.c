#include <stdio.h>
#include <stdlib.h>

#define HEAP_SIZE 100

typedef struct {
    int size;
    int data[HEAP_SIZE];
} Heap;

void heapify(Heap *heap, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap->size && heap->data[left] < heap->data[smallest])
        smallest = left;

    if (right < heap->size && heap->data[right] < heap->data[smallest])
        smallest = right;

    if (smallest != i) {
        int temp = heap->data[i];
        heap->data[i] = heap->data[smallest];
        heap->data[smallest] = temp;

        heapify(heap, smallest);
    }
}

void insert(Heap *heap, int newNum) {
    if (heap->size == HEAP_SIZE) {
        return;
    }

    heap->size++;
    int i = heap->size - 1;
    heap->data[i] = newNum;

    while (i != 0 && heap->data[(i - 1) / 2] > heap->data[i]) {
        int temp = heap->data[i];
        heap->data[i] = heap->data[(i - 1) / 2];
        heap->data[(i - 1) / 2] = temp;

        i = (i - 1) / 2;
    }
}

void deleteMin(Heap *heap) {
    if (heap->size == 0) {
        return;
    }

    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    heapify(heap, 0);
}

int main() {
    Heap heap;
    heap.size = 0;

    insert(&heap, 3);
    insert(&heap, 2);
    insert(&heap, 15);
    insert(&heap, 5);
    insert(&heap, 4);
    insert(&heap, 45);

    deleteMin(&heap);
    insert(&heap, 1);

    for (int i = 0; i < heap.size; i++) {
        printf("%d ", heap.data[i]);
    }

    return 0;
}