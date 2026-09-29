#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned long long val;
    int prime_idx;
    int ptr;
} HeapNode;

typedef struct {
    HeapNode *data;
    int size;
} MinHeap;

void heapify_down(MinHeap *heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->data[left].val < heap->data[smallest].val) {
        smallest = left;
    }
    if (right < heap->size && heap->data[right].val < heap->data[smallest].val) {
        smallest = right;
    }

    if (smallest != idx) {
        HeapNode temp = heap->data[idx];
        heap->data[idx] = heap->data[smallest];
        heap->data[smallest] = temp;
        heapify_down(heap, smallest);
    }
}

void build_heap(MinHeap *heap) {
    for (int i = (heap->size / 2) - 1; i >= 0; i--) {
        heapify_down(heap, i);
    }
}

unsigned long long nthSuperUglyNumber(int n, int* primes, int k) {
    if (n <= 0 || k <= 0 || !primes) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }

    unsigned long long *ugly = (unsigned long long *)malloc(sizeof(unsigned long long) * (size_t)n);
    if (!ugly) {
        return 0;
    }

    MinHeap heap;
    heap.size = k;
    heap.data = (HeapNode *)malloc(sizeof(HeapNode) * (size_t)k);
    if (!heap.data) {
        free(ugly);
        return 0;
    }

    ugly[0] = 1;

    for (int i = 0; i < k; i++) {
        heap.data[i].val = (unsigned long long)primes[i];
        heap.data[i].prime_idx = i;
        heap.data[i].ptr = 0;
    }

    build_heap(&heap);

    for (int i = 1; i < n; i++) {
        ugly[i] = heap.data[0].val;
        while (heap.data[0].val == ugly[i]) {
            int p_idx = heap.data[0].prime_idx;
            int ptr = heap.data[0].ptr + 1;
            heap.data[0].ptr = ptr;
            heap.data[0].val = ugly[ptr] * (unsigned long long)primes[p_idx];
            heapify_down(&heap, 0);
        }
    }

    unsigned long long result = ugly[n - 1];
    
    free(heap.data);
    free(ugly);
    
    return result;
}

int main(void) {
    int primes[] = {2, 7, 13, 19};
    int k = sizeof(primes) / sizeof(primes[0]);
    int n = 12;

    unsigned long long result = nthSuperUglyNumber(n, primes, k);
    printf("%llu\n", result);

    return 0;
}