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

void freeMinHeap(MinHeap *heap) {
    free(heap->elements);
    free(heap);
}

int* findTopKFrequent(const int* nums, int numsSize, int k, int* returnSize) {
    int *result = (int*)malloc(k * sizeof(int));
    *returnSize = 0;

    if (numsSize == 0 || k <= 0) {
        return result;
    }

    MinHeap *minHeap = createMinHeap(k);

    int current = nums[0];
    int count = 1;

    for (int i = 1; i < numsSize; i++) {
        if (nums[i] == current) {
            count++;
        } else {
            insert(minHeap, (Element){current, count});
            current = nums[i];
            count = 1;
        }
    }
    insert(minHeap, (Element){current, count});

    *returnSize = minHeap->size;
    for (int i = 0; i < minHeap->size; i++) {
        result[i] = minHeap->elements[i].value;
    }

    freeMinHeap(minHeap);
    return result;
}

int main() {
    int nums[] = {1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int k = 2;
    int returnSize;

    int *topK = findTopKFrequent(nums, numsSize, k, &returnSize);

    for (int i = 0; i < returnSize; i++) {
        printf("%d ", topK[i]);
    }
    printf("\n");

    free(topK);
    return 0;
}