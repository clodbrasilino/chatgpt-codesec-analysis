#include <stdio.h>
#include <stdlib.h>

#define HEAP_SIZE 100

typedef struct {
    int size;
    int data[HEAP_SIZE];
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

void insert(Heap *heap, int newNum) {
    if (heap->size == HEAP_SIZE) {
        printf("\nHeap is full\n");
        return;
    }

    heap->data[heap->size++] = newNum;
    int i = heap->size - 1;

    while (i != 0 && heap->data[i] < heap->data[(i - 1) / 2]) {
        swap(&heap->data[i], &heap->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int deleteRoot(Heap *heap) {
    int deletedValue = heap->data[0];
    heap->data[0] = heap->data[--heap->size];
    heapify(heap, 0);
    return deletedValue;
}

int main() {
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    heap->size = 0;

    int arr[] = {10, 5, 3, 2, 8, 15, 6, 20};
    int n = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < n; i++)
        insert(heap, arr[i]);

    printf("Smallest element: %d\n", deleteRoot(heap));

    free(heap);
    return 0;
}