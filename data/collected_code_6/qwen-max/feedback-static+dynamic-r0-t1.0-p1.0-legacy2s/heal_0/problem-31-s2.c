#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAP_SIZE 1000

typedef struct {
    int value;
    int count;
} HeapNode;

typedef struct {
    HeapNode* array;
    int size;
    int capacity;
} MinHeap;

MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->array = (HeapNode*)malloc(sizeof(HeapNode) * capacity);
    minHeap->size = 0;
    minHeap->capacity = capacity;
    return minHeap;
}

void swap(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left].count < minHeap->array[smallest].count)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right].count < minHeap->array[smallest].count)
        smallest = right;

    if (smallest != idx) {
        swap(&minHeap->array[idx], &minHeap->array[smallest]);
        minHeapify(minHeap, smallest);
    }
}

HeapNode extractMin(MinHeap* minHeap) {
    HeapNode root = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return root;
}

void insertKey(MinHeap* minHeap, HeapNode key) {
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && key.count > minHeap->array[(i - 1) / 2].count) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = key;
}

int* topKFrequent(int* nums, int numsSize, int k, int* returnSize) {
    int countMap[10001] = {0};
    for (int i = 0; i < numsSize; ++i) {
        countMap[nums[i]]++;
    }

    MinHeap* minHeap = createMinHeap(k + 1);
    for (int i = 0; i < 10001; ++i) {
        if (countMap[i]) {
            HeapNode node = {i, countMap[i]};
            insertKey(minHeap, node);

            if (minHeap->size > k) {
                extractMin(minHeap);
            }
        }
    }

    *returnSize = k;
    int* result = (int*)malloc(sizeof(int) * k);
    for (int i = k - 1; i >= 0; --i) {
        result[i] = extractMin(minHeap).value;
    }

    free(minHeap->array);
    free(minHeap);
    return result;
}

int main() {
    int nums[] = {1, 1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
    int k = 2;
    int returnSize = 0;
    int* topK = topKFrequent(nums, 11, k, &returnSize);

    for (int i = 0; i < returnSize; ++i) {
        printf("%d ", topK[i]);
    }
    printf("\n");

    free(topK);
    return 0;
}