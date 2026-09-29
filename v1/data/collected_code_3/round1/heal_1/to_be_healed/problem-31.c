#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int freq;
} heapNode;

typedef struct {
    heapNode *arr;
    int size;
    int capacity;
} MinHeap;

MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*) malloc(sizeof(MinHeap));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'minHeap' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->arr = (heapNode*) malloc(minHeap->capacity * sizeof(heapNode));
    return minHeap;
}

void swap(heapNode* a, heapNode* b) {
    heapNode temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap* minHeap, int idx) {
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->arr[left].freq < minHeap->arr[smallest].freq)
        smallest = left;

    if (right < minHeap->size && minHeap->arr[right].freq < minHeap->arr[smallest].freq)
        smallest = right;

    if (smallest != idx) {
        swap(&minHeap->arr[smallest], &minHeap->arr[idx]);
        minHeapify(minHeap, smallest);
    }
}

void insert(MinHeap* minHeap, int key, int freq) {
    if (minHeap->size == minHeap->capacity) {
        if (minHeap->arr[0].freq < freq) {
            minHeap->arr[0].key = key;
            minHeap->arr[0].freq = freq;
            minHeapify(minHeap, 0);
        }
    } else {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL '*minHeap.arr + (long unsigned int)*minHeap.size * 8' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        minHeap->arr[minHeap->size].key = key;
        minHeap->arr[minHeap->size].freq = freq;
        minHeap->size++;
        for (int i = (minHeap->size - 1) / 2; i >= 0; --i)
            minHeapify(minHeap, i);
    }
}

void printHeap(MinHeap* minHeap) {
    for (int i = 0; i < minHeap->size; ++i)
        printf("%d ", minHeap->arr[i].key);
    printf("\n");
}

void topKFrequent(int* nums, int numsSize, int k) {
    int i, j;
    MinHeap* minHeap = createMinHeap(k);
    for (i = 0; i < numsSize; i = j) {
        for (j = i; j < numsSize; ++j)
            if (nums[j] != nums[i])
                break;
        insert(minHeap, nums[i], j - i);
    }
    printHeap(minHeap);
}

int main() {
    int nums[] = {1, 1, 1, 2, 2, 3};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int k = 2;
    topKFrequent(nums, numsSize, k);
    return 0;
}