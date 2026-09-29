#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct HeapNode {
    long long val;
    int prime;
    int index;
};

struct MinHeap {
    struct HeapNode* array;
    int size;
    int capacity;
};

struct MinHeap* createMinHeap(int capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    if (!minHeap) return NULL;
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct HeapNode*)malloc(capacity * sizeof(struct HeapNode));
    if (!minHeap->array) {
        free(minHeap);
        return NULL;
    }
    return minHeap;
}

void swap(struct HeapNode* a, struct HeapNode* b) {
    struct HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left].val < minHeap->array[smallest].val)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right].val < minHeap->array[smallest].val)
        smallest = right;

    if (smallest != idx) {
        swap(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

void insertMinHeap(struct MinHeap* minHeap, struct HeapNode node) {
    if (minHeap->size == minHeap->capacity) return;
    
    int i = minHeap->size++;
    minHeap->array[i] = node;

    while (i != 0 && minHeap->array[(i - 1) / 2].val > minHeap->array[i].val) {
        swap(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

struct HeapNode extractMin(struct MinHeap* minHeap) {
    if (minHeap->size <= 0) {
        struct HeapNode empty = {0, 0, 0};
        return empty;
    }
    if (minHeap->size == 1) {
        minHeap->size--;
        return minHeap->array[0];
    }

    struct HeapNode root = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    minHeap->size--;
    minHeapify(minHeap, 0);

    return root;
}

void freeMinHeap(struct MinHeap* minHeap) {
    if (minHeap) {
        if (minHeap->array) {
            free(minHeap->array);
        }
        free(minHeap);
    }
}

int nthSuperUglyNumber(int n, int* primes, int primesSize) {
    if (n <= 0 || !primes || primesSize <= 0) return 0;

    long long* ugly = (long long*)malloc(n * sizeof(long long));
    if (!ugly) return 0;

    struct MinHeap* minHeap = createMinHeap(primesSize);
    if (!minHeap) {
        free(ugly);
        return 0;
    }

    ugly[0] = 1;

    for (int i = 0; i < primesSize; i++) {
        struct HeapNode node = {primes[i], primes[i], 0};
        insertMinHeap(minHeap, node);
    }

    for (int i = 1; i < n; i++) {
        struct HeapNode minNode = extractMin(minHeap);
        ugly[i] = minNode.val;

        while (minHeap->size > 0 && minHeap->array[0].val == ugly[i]) {
            struct HeapNode duplicateNode = extractMin(minHeap);
            duplicateNode.index++;
            duplicateNode.val = (long long)duplicateNode.prime * ugly[duplicateNode.index];
            insertMinHeap(minHeap, duplicateNode);
        }

        minNode.index++;
        minNode.val = (long long)minNode.prime * ugly[minNode.index];
        insertMinHeap(minHeap, minNode);
    }

    int result = (int)ugly[n - 1];
    
    free(ugly);
    freeMinHeap(minHeap);
    
    return result;
}

int main() {
    int primes[] = {2, 7, 13, 19};
    int primesSize = sizeof(primes) / sizeof(primes[0]);
    int n = 12;
    
    int result = nthSuperUglyNumber(n, primes, primesSize);
    printf("%d\n", result);
    
    return 0;
}