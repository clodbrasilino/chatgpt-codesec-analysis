#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    long long val;
    int prime_idx;
    int index;
} HeapNode;

typedef struct {
    HeapNode* array;
    int size;
    int capacity;
} MinHeap;

MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    if (!minHeap) return NULL;
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (HeapNode*)malloc(capacity * sizeof(HeapNode));
    if (!minHeap->array) {
        free(minHeap);
        return NULL;
    }
    return minHeap;
}

void swapHeapNode(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap* minHeap, int idx) {
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

void buildMinHeap(MinHeap* minHeap) {
    int n = minHeap->size - 1;
    for (int i = (n - 1) / 2; i >= 0; i--)
        minHeapify(minHeap, i);
}

long long nthSuperUglyNumber(int n, int* primes, int k) {
    if (n <= 0 || k <= 0 || !primes) return 0;

    long long* ugly = (long long*)malloc(n * sizeof(long long));
    if (!ugly) return 0;

    ugly[0] = 1;

    MinHeap* minHeap = createMinHeap(k);
    if (!minHeap) {
        free(ugly);
        return 0;
    }

    for (int i = 0; i < k; i++) {
        minHeap->array[i].val = primes[i];
        minHeap->array[i].prime_idx = i;
        minHeap->array[i].index = 0;
    }
    minHeap->size = k;
    buildMinHeap(minHeap);

    for (int i = 1; i < n; i++) {
        ugly[i] = minHeap->array[0].val;

        while (minHeap->array[0].val == ugly[i]) {
            int p_idx = minHeap->array[0].prime_idx;
            int idx = minHeap->array[0].index + 1;
            minHeap->array[0].index = idx;
            minHeap->array[0].val = ugly[idx] * primes[p_idx];
            minHeapify(minHeap, 0);
        }
    }

    long long result = ugly[n - 1];
    
    free(minHeap->array);
    free(minHeap);
    free(ugly);
    
    return result;
}

int main(void) {
    int primes[] = {2, 7, 13, 19};
    int k = sizeof(primes) / sizeof(primes[0]);
    int n = 12;

    long long result = nthSuperUglyNumber(n, primes, k);
    printf("%lld\n", result);

    return 0;
}