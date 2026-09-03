#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int count;
} Element;

typedef struct {
    Element *elements;
    int size;
    int capacity;
} MinHeap;

MinHeap* createMinHeap(int capacity) {
    MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->elements = (Element*)malloc(capacity * sizeof(Element));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(Element *a, Element *b) {
    Element temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap *heap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size && heap->elements[left].count < heap->elements[smallest].count)
        smallest = left;

    if (right < heap->size && heap->elements[right].count < heap->elements[smallest].count)
        smallest = right;

    if (smallest != index) {
        swap(&heap->elements[index], &heap->elements[smallest]);
        minHeapify(heap, smallest);
    }
}

void insert(MinHeap *heap, Element element) {
    if (heap->size == heap->capacity) {
        if (element.count > heap->elements[0].count) {
            heap->elements[0] = element;
            minHeapify(heap, 0);
        }
    } else {
        int i = heap->size;
        heap->elements[i] = element;
        while (i != 0 && heap->elements[(i - 1) / 2].count > heap->elements[i].count) {
            swap(&heap->elements[i], &heap->elements[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
        heap->size++;
    }
}

void printTopK(MinHeap *heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->elements[i].value);
    }
    printf("\n");
}

void findTopKFrequent(int *arr, int n, int k) {
    MinHeap *heap = createMinHeap(k);
    int *counts = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        counts[arr[i]]++;
    }
    for (int i = 0; i < n; i++) {
        if (counts[i] > 0) {
            Element element = {i, counts[i]};
            insert(heap, element);
        }
    }
    printTopK(heap);
    free(counts);
    free(heap->elements);
    free(heap);
}

int main() {
    int arr[] = {1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    int k = 2;
    findTopKFrequent(arr, n, k);
    return 0;
}