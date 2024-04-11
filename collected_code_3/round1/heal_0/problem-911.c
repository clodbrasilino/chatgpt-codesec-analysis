#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAP_SIZE 100000

typedef struct {
    int size;
    int data[MAX_HEAP_SIZE];
} Heap;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void maxHeapify(Heap *heap, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap->size && heap->data[left] > heap->data[largest])
        largest = left;

    if (right < heap->size && heap->data[right] > heap->data[largest])
        largest = right;

    if (largest != i) {
        swap(&heap->data[i], &heap->data[largest]);
        maxHeapify(heap, largest);
    }
}

void buildMaxHeap(Heap *heap, int *arr, int n) {
    int i;
    for (i = 0; i < n; i++)
        heap->data[i] = arr[i];
    heap->size = n;

    for (i = n / 2 - 1; i >= 0; i--)
        maxHeapify(heap, i);
}

int extractMax(Heap *heap) {
    int max = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    maxHeapify(heap, 0);
    return max;
}

int maxProduct(int *arr, int n) {
    Heap heap;
    buildMaxHeap(&heap, arr, n);

    int max1 = extractMax(&heap);
    int max2 = extractMax(&heap);
    int max3 = extractMax(&heap);

    return max1 * max2 * max3;
}

int main() {
    int arr[] = {1, 20, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Maximum product is %d\n", maxProduct(arr, n));

    return 0;
}