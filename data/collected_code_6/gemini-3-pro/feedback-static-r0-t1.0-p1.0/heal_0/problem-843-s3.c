#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct HeapNode {
    unsigned long long val;
    int prime_idx;
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

void swapHeapNode(struct HeapNode* a, struct HeapNode* b) {
    struct HeapNode t = *a;
    *a = *b;
    *b = t;
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
        swapHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

void insertMinHeap(struct MinHeap* minHeap, struct HeapNode node) {
    if (minHeap->size == minHeap->capacity) return;
    int i = minHeap->size;
    minHeap->size++;
    minHeap->array[i] = node;

    while (i != 0 && minHeap->array[(i - 1) / 2].val > minHeap->array[i].val) {
        swapHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

struct HeapNode extractMin(struct MinHeap* minHeap) {
    if (minHeap->size == 0) {
        struct HeapNode emptyNode = {0, 0, 0};
        return emptyNode;
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
        free(minHeap->array);
        free(minHeap);
    }
}

int nthSuperUglyNumber(int n, int* primes, int k) {
    if (n <= 0 || !primes || k <= 0) return 0;

    unsigned long long* ugly = (unsigned long long*)malloc(n * sizeof(unsigned long long));
    if (!ugly) return 0;
    
    ugly[0] = 1;

    struct MinHeap* minHeap = createMinHeap(k);
    if (!minHeap) {
        free(ugly);
        return 0;
    }

    for (int i = 0; i < k; i++) {
        struct HeapNode node = {(unsigned long long)primes[i], i, 0};
        insertMinHeap(minHeap, node);
    }

    for (int i = 1; i < n; i++) {
        struct HeapNode minNode;
        do {
            minNode = minHeap->array[0];
            if (minNode.val != ugly[i - 1]) {
                ugly[i] = minNode.val;
            }
            
            struct HeapNode nextNode;
            nextNode.prime_idx = minNode.prime_idx;
            nextNode.index = minNode.index + 1;
            nextNode.val = (unsigned long long)primes[minNode.prime_idx] * ugly[nextNode.index];
            
            minHeap->array[0] = nextNode;
            minHeapify(minHeap, 0);
        } while (minNode.val == ugly[i - 1]);
    }

    int result = (int)ugly[n - 1];
    free(ugly);
    freeMinHeap(minHeap);
    return result;
}

int main(void) {
    int primes[] = {2, 7, 13, 19};
    int k = sizeof(primes) / sizeof(primes[0]);
    int n = 12;
    
    int result = nthSuperUglyNumber(n, primes, k);
    printf("%d\n", result);
    
    return 0;
}