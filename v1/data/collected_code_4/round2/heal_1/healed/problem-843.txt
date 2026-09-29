#include <stdio.h>
#include <stdlib.h>

#define SIZE 100000

int cmpfunc(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

typedef struct HeapNode {
    int val;
    int prime;
    int index;
    int valUgly;
} HeapNode;

void swapNode(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(HeapNode heap[], int i, int heapSize) {
    int smallest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < heapSize && heap[left].valUgly < heap[smallest].valUgly)
        smallest = left;

    if (right < heapSize && heap[right].valUgly < heap[smallest].valUgly)
        smallest = right;

    if (smallest != i) {
        swapNode(&heap[i], &heap[smallest]);
        minHeapify(heap, smallest, heapSize);
    }
}

void makeHeap(HeapNode heap[], int n) {
    for(int i = (n-2)/2; i >= 0; i--)
        minHeapify(heap, i, n);
}

int nthSuperUgly(int n, int primes[], int k) {
    int ugly[SIZE];  
    HeapNode heap[k];
    for (int i=0; i<k; i++) {
        heap[i].val = primes[i];
        heap[i].prime = i;
        heap[i].index = 1;
        heap[i].valUgly = primes[i];
    }

    makeHeap(heap, k);
    
    ugly[0] = 1;
    for (int i=1; i<n; i++) {
        ugly[i] = heap[0].valUgly;
        int j = 0;
        while (j<k && heap[j].valUgly == ugly[i]) {
            heap[j].valUgly = heap[j].val * ugly[heap[j].index++];
            minHeapify(heap, j, k);
            j++;
        }
    }
    return ugly[n-1];
}

int main() {
    int primes[] = {2, 7, 13, 19};
    int n = 18;
    int k = sizeof(primes)/sizeof(primes[0]);

    printf("%d\n", nthSuperUgly(n, primes, k));
    return 0;
}