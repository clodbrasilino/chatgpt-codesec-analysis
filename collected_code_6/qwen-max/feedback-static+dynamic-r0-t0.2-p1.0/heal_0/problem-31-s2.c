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
    Element min = heap->elements[0];
    heap->elements[0] = heap->elements[heap->size - 1];
    heap->size--;
    heapify(heap, 0);
    return min;
}

void topKFrequent(int *nums, int numsSize, int k, int *result) {
    Element *counts = (Element *)calloc(numsSize, sizeof(Element));
    for (int i = 0; i < numsSize; i++) {
        counts[i].value = nums[i];
        counts[i].count = 1;
    }

    for (int i = 1; i < numsSize; i++) {
        if (nums[i] == nums[i - 1]) {
            counts[i - 1].count++;
        } else {
            counts[i].count = 1;
        }
    }

    qsort(counts, numsSize, sizeof(Element), compare);

    MinHeap heap;
    heap.size = 0;
    heap.capacity = k;
    heap.elements = (Element *)malloc(k * sizeof(Element));

    for (int i = 0; i < numsSize; i++) {
        if (heap.size < k) {
            insert(&heap, counts[i]);
        } else if (counts[i].count > heap.elements[0].count) {
            extractMin(&heap);
            insert(&heap, counts[i]);
        }
    }

    for (int i = 0; i < k; i++) {
        result[i] = extractMin(&heap).value;
    }

    free(counts);
    free(heap.elements);
}

int main() {
    int nums[] = {1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int k = 2;
    int *result = (int *)malloc(k * sizeof(int));
    topKFrequent(nums, numsSize, k, result);

    for (int i = 0; i < k; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    return 0;
}