#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int size;
    int data[MAX_SIZE];
} Heap;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(Heap *heap, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap->size && heap->data[left] < heap->data[smallest])
        smallest = left;

    if (right < heap->size && heap->data[right] < heap->data[smallest])
        smallest = right;

    if (smallest != i) {
        swap(&heap->data[i], &heap->data[smallest]);
        heapify(heap, smallest);
    }
}

void insertHeap(Heap *heap, int newNum) {
    if (heap->size == MAX_SIZE) {
        printf("Heap is full\n");
        return;
    }

    heap->size++;
    int i = heap->size - 1;
    heap->data[i] = newNum;

    while (i != 0 && heap->data[(i - 1) / 2] > heap->data[i]) {
        swap(&heap->data[i], &heap->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void deleteRoot(Heap *heap) {
    if (heap->size <= 0)
        return;
    if (heap->size == 1) {
        heap->size--;
        return;
    }

    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    heapify(heap, 0);
}

int main() {
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    heap->size = 0;

    insertHeap(heap, 3);
    insertHeap(heap, 2);
    insertHeap(heap, 15);
    insertHeap(heap, 5);
    insertHeap(heap, 4);
    insertHeap(heap, 45);

    deleteRoot(heap);
    insertHeap(heap, 1);

    for (int i = 0; i < heap->size; i++)
        printf("%d ", heap->data[i]);

    free(heap);

    return 0;
}