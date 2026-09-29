#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *arr;
    int count;
    int capacity;
} MinHeap;

MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*) malloc(sizeof(MinHeap));
    heap->arr = (int*) malloc(sizeof(int)*capacity);
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
        swap(&heap->arr[idx], &heap->arr[smallest]);
        minHeapify(heap, smallest);
    }
}

void insert(MinHeap* heap, int data) {
    if (heap->count >= heap->capacity) {
        heap->arr = realloc(heap->arr, heap->capacity * 2);
        heap->capacity *= 2;
    }

    heap->arr[heap->count] = data;
    int i = (heap->count)++;
    while (i != 0 && heap->arr[(i-1)/2] > heap->arr[i]) {
        swap(&heap->arr[(i-1)/2], &heap->arr[i]);
        i = (i-1)/2;
    }
}

int pop(MinHeap* heap) {
    if (heap->count <= 0) return INT_MAX;

    int minVal = heap->arr[0];
    heap->arr[0] = heap->arr[--heap->count];
    minHeapify(heap, 0);
    
    return minVal;
}

void freeHeap(MinHeap* heap) {
    free(heap->arr);
    free(heap);
}

int main() {
    MinHeap* heap = createMinHeap(11);
    insert(heap, 3);
    insert(heap, 2);
    insert(heap, 15);
    insert(heap, 5);
    insert(heap, 4);
    insert(heap, 45);

    printf("%d ", pop(heap));
    printf("%d ", pop(heap));
    printf("%d ", pop(heap));
    printf("%d ", pop(heap));
    printf("%d ", pop(heap));

    freeHeap(heap);
  
    return 0;
}