#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_HEAP_SIZE 1000

typedef struct {
    int value;
    int arrayIndex;
    int elementIndex;
} HeapNode;

typedef struct {
    HeapNode* data;
    int size;
    int capacity;
} MinHeap;

MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    if (!heap) return NULL;
    heap->data = (HeapNode*)malloc(capacity * sizeof(HeapNode));
    if (!heap->data) {
        free(heap);
        return NULL;
    }
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swapHeapNodes(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap* heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->data[left].value < heap->data[smallest].value)
        smallest = left;

    if (right < heap->size && heap->data[right].value < heap->data[smallest].value)
        smallest = right;

    if (smallest != idx) {
        swapHeapNodes(&heap->data[idx], &heap->data[smallest]);
        minHeapify(heap, smallest);
    }
}

void insertMinHeap(MinHeap* heap, HeapNode node) {
    if (heap->size >= heap->capacity) return;

    heap->size++;
    int i = heap->size - 1;
    heap->data[i] = node;

    while (i != 0 && heap->data[(i - 1) / 2].value > heap->data[i].value) {
        swapHeapNodes(&heap->data[i], &heap->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

HeapNode extractMin(MinHeap* heap) {
    HeapNode min = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    minHeapify(heap, 0);
    return min;
}

HeapNode getMin(MinHeap* heap) {
    return heap->data[0];
}

void freeMinHeap(MinHeap* heap) {
    if (heap) {
        if (heap->data) free(heap->data);
        free(heap);
    }
}

int findMaxValue(MinHeap* heap) {
    int max = heap->data[0].value;
    for (int i = 1; i < heap->size; i++) {
        if (heap->data[i].value > max)
            max = heap->data[i].value;
    }
    return max;
}

void findSmallestRange(int* arrays[], const int sizes[], int numArrays, int* rangeStart, int* rangeEnd) {
    if (numArrays <= 0) {
        *rangeStart = 0;
        *rangeEnd = 0;
        return;
    }

    for (int i = 0; i < numArrays; i++) {
        if (sizes[i] <= 0) {
            *rangeStart = 0;
            *rangeEnd = 0;
            return;
        }
    }

    MinHeap* heap = createMinHeap(numArrays);
    if (!heap) {
        *rangeStart = 0;
        *rangeEnd = 0;
        return;
    }

    int currentMax = INT_MIN;
    int minRange = INT_MAX;
    int resultStart = 0;
    int resultEnd = 0;

    for (int i = 0; i < numArrays; i++) {
        HeapNode node;
        node.value = arrays[i][0];
        node.arrayIndex = i;
        node.elementIndex = 0;
        insertMinHeap(heap, node);
        if (node.value > currentMax)
            currentMax = node.value;
    }

    while (1) {
        HeapNode minNode = getMin(heap);
        int currentRange = currentMax - minNode.value;

        if (currentRange < minRange) {
            minRange = currentRange;
            resultStart = minNode.value;
            resultEnd = currentMax;
        }

        HeapNode extractedMin = extractMin(heap);
        int nextElementIndex = extractedMin.elementIndex + 1;

        if (nextElementIndex >= sizes[extractedMin.arrayIndex]) {
            break;
        }

        HeapNode nextNode;
        nextNode.value = arrays[extractedMin.arrayIndex][nextElementIndex];
        nextNode.arrayIndex = extractedMin.arrayIndex;
        nextNode.elementIndex = nextElementIndex;
        insertMinHeap(heap, nextNode);

        if (nextNode.value > currentMax)
            currentMax = nextNode.value;
    }

    *rangeStart = resultStart;
    *rangeEnd = resultEnd;
    freeMinHeap(heap);
}

int main() {
    int arr1[] = {4, 7, 9, 12, 15};
    int arr2[] = {0, 8, 10, 14, 20};
    int arr3[] = {6, 12, 16, 30, 50};

    int* arrays[] = {arr1, arr2, arr3};
    int sizes[] = {5, 5, 5};

    int rangeStart, rangeEnd;
    findSmallestRange(arrays, sizes, 3, &rangeStart, &rangeEnd);

    printf("Smallest range: [%d, %d]\n", rangeStart, rangeEnd);

    int arr4[] = {1, 3, 5, 7, 9};
    int arr5[] = {2, 4, 6, 8, 10};
    int arr6[] = {11, 13, 15, 17, 19};

    int* arrays2[] = {arr4, arr5, arr6};
    int sizes2[] = {5, 5, 5};

    findSmallestRange(arrays2, sizes2, 3, &rangeStart, &rangeEnd);

    printf("Smallest range: [%d, %d]\n", rangeStart, rangeEnd);

    return 0;
}