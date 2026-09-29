#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int num;
    int freq;
} NumFreq;

typedef struct {
    NumFreq* data;
    int size;
    int capacity;
} Heap;

Heap* createHeap(int capacity) {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    heap->data = (NumFreq*)malloc(capacity * sizeof(NumFreq));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(NumFreq* a, NumFreq* b) {
    NumFreq temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(Heap* heap, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap->size && heap->data[left].freq < heap->data[smallest].freq)
        smallest = left;

    if (right < heap->size && heap->data[right].freq < heap->data[smallest].freq)
        smallest = right;

    if (smallest != i) {
        swap(&heap->data[i], &heap->data[smallest]);
        heapify(heap, smallest);
    }
}

void insertHeap(Heap* heap, NumFreq numFreq) {
    if (heap->size == heap->capacity) {
        if (heap->data[0].freq < numFreq.freq) {
            heap->data[0] = numFreq;
            heapify(heap, 0);
        }
    } else {
        heap->data[heap->size] = numFreq;
        int i = heap->size;
        while (i != 0 && heap->data[(i - 1) / 2].freq > heap->data[i].freq) {
            swap(&heap->data[i], &heap->data[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
        heap->size++;
    }
}

void printHeap(Heap* heap) {
    for (int i = 0; i < heap->size; ++i)
        printf("%d ", heap->data[i].num);
    printf("\n");
}

void topKFrequent(int* nums, int numsSize, int k) {
    int* freq = (int*)calloc(numsSize, sizeof(int));
    for (int i = 0; i < numsSize; ++i)
        freq[nums[i]]++;

    Heap* heap = createHeap(k);
    for (int i = 0; i < numsSize; ++i) {
        if (freq[i] > 0) {
            NumFreq numFreq = {i, freq[i]};
            insertHeap(heap, numFreq);
        }
    }

    printHeap(heap);
}

int main() {
    int nums[] = {1, 1, 1, 2, 2, 3};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int k = 2;
    topKFrequent(nums, numsSize, k);
    return 0;
}