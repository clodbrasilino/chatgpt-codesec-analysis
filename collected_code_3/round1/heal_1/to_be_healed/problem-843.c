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
    HeapNode** heap = (HeapNode**)malloc(sizeof(HeapNode*) * primesSize);
    for (int i = 0; i < primesSize; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'heap' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        heap[i] = (HeapNode*)malloc(sizeof(HeapNode));
        /* Possible weaknesses found:
         *  dereference of possibly-NULL '*heap_67 + _13' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        heap[i]->val = primes[i];
        heap[i]->prime = primes[i];
        heap[i]->index = 1;
    }

    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'ugly' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    ugly[0] = 1;
    for (int i = 1; i < n; i++) {
        ugly[i] = heap[0]->val;
        while (heap[0]->val == ugly[i]) {
            heap[0]->val = heap[0]->prime * ugly[heap[0]->index++];
            heapify(heap, 0, primesSize);
        }
    }

    return ugly[n - 1];
}

int main() {
    int primes[] = {2, 7, 13, 19};
    int n = 12;
    int primesSize = sizeof(primes) / sizeof(primes[0]);
    printf("%d\n", nthSuperUglyNumber(n, primes, primesSize));
    return 0;
}