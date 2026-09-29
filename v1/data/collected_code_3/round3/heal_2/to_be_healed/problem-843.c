#include <stdio.h>
#include <stdlib.h>

typedef struct HeapNode {
    int val;
    int prime;
    int index;
} HeapNode;

void swap(HeapNode** a, HeapNode** b) {
    HeapNode* temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(HeapNode** heap, int i, int heapSize) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heapSize && heap[left]->val < heap[smallest]->val)
        smallest = left;

    if (right < heapSize && heap[right]->val < heap[smallest]->val)
        smallest = right;

    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        heapify(heap, smallest, heapSize);
    }
}

int nthSuperUglyNumber(int n, int* primes, int primesSize) {
    int* ugly = (int*)malloc(sizeof(int) * n);
    if (!ugly) {
        return -1;
    }

    HeapNode** heap = (HeapNode**)malloc(sizeof(HeapNode*) * primesSize);
    if (!heap) {
        free(ugly);
        return -1;
    }

    for (int i = 0; i < primesSize; i++) {
        heap[i] = (HeapNode*)malloc(sizeof(HeapNode));
        if (!heap[i]) {
            for(int j = 0; j < i; j++)
                free(heap[j]);
            free(heap);
            free(ugly);
            return -1;
        }
        heap[i]->val = primes[i];
        heap[i]->prime = primes[i];
        heap[i]->index = 1;
    }

    ugly[0] = 1;
    for (int i = 1; i < n; i++) {
        ugly[i] = heap[0]->val;
        while (heap[0]->val == ugly[i]) {
            heap[0]->val = heap[0]->prime * ugly[heap[0]->index++];
            heapify(heap, 0, primesSize);
        }
    }

    /* Possible weaknesses found:
     *  use of uninitialized value '*ugly_82 + _62' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
     */
    int result = ugly[n - 1];
    free(ugly);
    for(int i = 0; i < primesSize; i++)
        free(heap[i]);
    free(heap);
    
    return result;
}

int main() {
    int primes[] = {2, 7, 13, 19};
    int n = 12;
    int primesSize = sizeof(primes) / sizeof(primes[0]);
    int result = nthSuperUglyNumber(n, primes, primesSize);
    if (result == -1) {
        printf("Memory allocation failed.\n");
        return -1;
    }
    printf("%d\n", result);
    return 0;
}