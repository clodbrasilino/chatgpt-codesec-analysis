#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *arr;
    int count;
    int capacity;
} MinHeap;

MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*) malloc(sizeof(MinHeap));
    if (heap == NULL) {
        return NULL;
    }

    heap->arr = (int*) malloc(sizeof(int)*capacity);
    if (heap->arr == NULL) {
        free(heap);
        return NULL;
    }

    heap->count = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap* heap, int idx) {
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < heap->count && heap->arr[left] < heap->arr[smallest])
        smallest = left;

    if (right < heap->count && heap->arr[right] < heap->arr[smallest])
        smallest = right;

    if (smallest != idx) {
        swap(&heap->arr[smallest], &heap->arr[idx]);
        minHeapify(heap, smallest);
    }
}

int extractMin(MinHeap* heap) {
    if (heap->count == 0)
        return -1;

    int root = heap->arr[0];

    if (heap->count > 1) {
        heap->arr[0] = heap->arr[heap->count - 1];
        minHeapify(heap, 0);
    }

    heap->count--;

    return root;
}

void insertKey(MinHeap* heap, int key) {
    if (heap->count == heap->capacity)
        return;

    heap->count++;
    int i = heap->count - 1;

    heap->arr[i] = key;

    while (i != 0 && heap->arr[(i - 1) / 2] > heap->arr[i]) {
        swap(&heap->arr[i], &heap->arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int main() {
    MinHeap* heap = createMinHeap(11);
    if (heap == NULL) {
        return -1;
    }

    insertKey(heap, 3);
    insertKey(heap, 2);
    insertKey(heap, 15);
    insertKey(heap, 5);
    insertKey(heap, 4);
    insertKey(heap, 45);

    printf("%d ", extractMin(heap));
    printf("%d ", extractMin(heap));
    printf("%d ", extractMin(heap));
    printf("%d ", extractMin(heap));
    printf("%d ", extractMin(heap));
    printf("%d ", extractMin(heap));

    free(heap->arr);
    free(heap);

    return 0;
}