#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    long long val;
    int prime_idx;
    int p_idx;
} HeapNode;

typedef struct {
    HeapNode* data;
    int size;
    int capacity;
} MinHeap;

MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
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

void swap(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap* heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->data[left].val < heap->data[smallest].val)
        smallest = left;

    if (right < heap->size && heap->data[right].val < heap->data[smallest].val)
        smallest = right;

    if (smallest != idx) {
        swap(&heap->data[idx], &heap->data[smallest]);
        minHeapify(heap, smallest);
    }
}

void insertMinHeap(MinHeap* heap, HeapNode node) {
    if (heap->size == heap->capacity) return;
    
    int i = heap->size++;
    heap->data[i] = node;

    while (i != 0 && heap->data[(i - 1) / 2].val > heap->data[i].val) {
        swap(&heap->data[i], &heap->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

HeapNode extractMin(MinHeap* heap) {
    if (heap->size <= 0) {
        HeapNode empty = {-1, -1, -1};
        return empty;
    }
    if (heap->size == 1) {
        heap->size--;
        return heap->data[0];
    }

    HeapNode root = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    minHeapify(heap, 0);

    return root;
}

void freeMinHeap(MinHeap* heap) {
    if (heap) {
        if (heap->data) free(heap->data);
        free(heap);
    }
}

int nthSuperUglyNumber(int n, int* primes, int primesSize) {
    if (n <= 0 || !primes || primesSize <= 0) return 0;

    long long* ugly = (long long*)malloc(sizeof(long long) * n);
    if (!ugly) return 0;

    MinHeap* heap = createMinHeap(primesSize);
    if (!heap) {
        free(ugly);
        return 0;
    }

    ugly[0] = 1;

    for (int i = 0; i < primesSize; i++) {
        HeapNode node = {primes[i], i, 0};
        insertMinHeap(heap, node);
    }

    for (int i = 1; i < n; i++) {
        HeapNode minNode = extractMin(heap);
        ugly[i] = minNode.val;

        while (heap->size > 0 && heap->data[0].val == ugly[i]) {
            HeapNode dupNode = extractMin(heap);
            dupNode.p_idx++;
            dupNode.val = (long long)primes[dupNode.prime_idx] * ugly[dupNode.p_idx];
            insertMinHeap(heap, dupNode);
        }

        minNode.p_idx++;
        minNode.val = (long long)primes[minNode.prime_idx] * ugly[minNode.p_idx];
        insertMinHeap(heap, minNode);
    }

    int result = (int)ugly[n - 1];
    free(ugly);
    freeMinHeap(heap);
    return result;
}

int main(void) {
    int primes[] = {2, 7, 13, 19};
    int primesSize = sizeof(primes) / sizeof(primes[0]);
    int n = 12;

    int result = nthSuperUglyNumber(n, primes, primesSize);
    printf("%d\n", result);

    return 0;
}