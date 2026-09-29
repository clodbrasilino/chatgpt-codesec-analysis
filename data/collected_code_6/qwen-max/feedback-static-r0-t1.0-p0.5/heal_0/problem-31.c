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

int compare(const void *a, const void *b) {
    return ((Element *)a)->count - ((Element *)b)->count;
}

void swap(Element *a, Element *b) {
    Element temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(MinHeap *heap, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap->size && heap->elements[left].count < heap->elements[smallest].count)
        smallest = left;

    if (right < heap->size && heap->elements[right].count < heap->elements[smallest].count)
        smallest = right;

    if (smallest != i) {
        swap(&heap->elements[i], &heap->elements[smallest]);
        heapify(heap, smallest);
    }
}

void insert(MinHeap *heap, Element element) {
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->elements = realloc(heap->elements, heap->capacity * sizeof(Element));
    }
    int i = heap->size;
    heap->elements[i] = element;
    while (i > 0 && heap->elements[(i - 1) / 2].count > heap->elements[i].count) {
        swap(&heap->elements[i], &heap->elements[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
    heap->size++;
}

Element extractMin(MinHeap *heap) {
    if (heap->size <= 0) {
        Element e = {0, 0};
        return e;
    }
    if (heap->size == 1) {
        heap->size--;
        return heap->elements[0];
    }

    Element root = heap->elements[0];
    heap->elements[0] = heap->elements[heap->size - 1];
    heap->size--;
    heapify(heap, 0);
    return root;
}

int* topKFrequent(int* nums, int numsSize, int k, int* returnSize) {
    int *result = malloc(k * sizeof(int));
    *returnSize = k;

    int *counts = calloc(100001, sizeof(int));
    for (int i = 0; i < numsSize; i++) {
        counts[nums[i]]++;
    }

    MinHeap heap;
    heap.size = 0;
    heap.capacity = 10;
    heap.elements = malloc(heap.capacity * sizeof(Element));

    for (int i = 0; i < 100001; i++) {
        if (counts[i] > 0) {
            Element element = {i, counts[i]};
            insert(&heap, element);
            if (heap.size > k) {
                extractMin(&heap);
            }
        }
    }

    for (int i = k - 1; i >= 0; i--) {
        result[i] = extractMin(&heap).value;
    }

    free(counts);
    free(heap.elements);
    return result;
}

int main() {
    int nums[] = {1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
    int numsSize = 11;
    int k = 2;
    int returnSize;

    int *result = topKFrequent(nums, numsSize, k, &returnSize);

    for (int i = 0; i < returnSize; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    return 0;
}