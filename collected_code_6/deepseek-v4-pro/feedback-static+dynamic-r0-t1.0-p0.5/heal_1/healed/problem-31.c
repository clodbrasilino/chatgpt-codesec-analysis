#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int frequency;
} HeapNode;

typedef struct {
    HeapNode *data;
    int size;
    int capacity;
} MinHeap;

MinHeap* createMinHeap(int capacity) {
    MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
    if (!heap) return NULL;
    heap->data = (HeapNode*)malloc(sizeof(HeapNode) * capacity);
    if (!heap->data) {
        free(heap);
        return NULL;
    }
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyDown(MinHeap *heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->data[left].frequency < heap->data[smallest].frequency)
        smallest = left;
    if (right < heap->size && heap->data[right].frequency < heap->data[smallest].frequency)
        smallest = right;

    if (smallest != idx) {
        swap(&heap->data[idx], &heap->data[smallest]);
        heapifyDown(heap, smallest);
    }
}

void heapifyUp(MinHeap *heap, int idx) {
    int parent = (idx - 1) / 2;
    if (idx > 0 && heap->data[idx].frequency < heap->data[parent].frequency) {
        swap(&heap->data[idx], &heap->data[parent]);
        heapifyUp(heap, parent);
    }
}

void insertHeap(MinHeap *heap, int value, int frequency) {
    if (heap->size < heap->capacity) {
        heap->data[heap->size].value = value;
        heap->data[heap->size].frequency = frequency;
        heap->size++;
        heapifyUp(heap, heap->size - 1);
    } else if (frequency > heap->data[0].frequency) {
        heap->data[0].value = value;
        heap->data[0].frequency = frequency;
        heapifyDown(heap, 0);
    }
}

void freeMinHeap(MinHeap *heap) {
    if (heap) {
        free(heap->data);
        free(heap);
    }
}

int* topKFrequent(int** lists, int listCount, const int* listSizes, int k, int* returnSize) {
    if (listCount <= 0 || k <= 0) {
        *returnSize = 0;
        return NULL;
    }

    MinHeap *heap = createMinHeap(k);
    if (!heap) {
        *returnSize = 0;
        return NULL;
    }

    int *indices = (int*)calloc(listCount, sizeof(int));
    if (!indices) {
        freeMinHeap(heap);
        *returnSize = 0;
        return NULL;
    }

    int currentValue = 0;
    int currentFreq = 0;
    int hasCurrent = 0;

    while (1) {
        int minVal = 0;
        int minListIdx = -1;
        int found = 0;

        for (int i = 0; i < listCount; i++) {
            if (indices[i] < listSizes[i]) {
                if (!found || lists[i][indices[i]] < minVal) {
                    minVal = lists[i][indices[i]];
                    minListIdx = i;
                    found = 1;
                }
            }
        }

        if (!found) break;

        if (!hasCurrent) {
            currentValue = minVal;
            currentFreq = 1;
            hasCurrent = 1;
        } else if (currentValue == minVal) {
            currentFreq++;
        } else {
            insertHeap(heap, currentValue, currentFreq);
            currentValue = minVal;
            currentFreq = 1;
        }

        indices[minListIdx]++;
    }

    if (hasCurrent) {
        insertHeap(heap, currentValue, currentFreq);
    }

    free(indices);

    int *result = (int*)malloc(sizeof(int) * heap->size);
    if (!result) {
        freeMinHeap(heap);
        *returnSize = 0;
        return NULL;
    }

    for (int i = 0; i < heap->size; i++) {
        result[i] = heap->data[i].value;
    }

    *returnSize = heap->size;
    freeMinHeap(heap);
    return result;
}

int main() {
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {2, 3, 5, 7};
    int list3[] = {3, 5, 8, 9};

    int *lists[] = {list1, list2, list3};
    int listSizes[] = {5, 4, 4};
    int listCount = 3;
    int k = 3;
    int returnSize = 0;

    int *result = topKFrequent(lists, listCount, listSizes, k, &returnSize);

    printf("Top %d frequent elements: ", k);
    for (int i = 0; i < returnSize; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    return 0;
}