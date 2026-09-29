#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct {
    int* data;
    int size;
    int capacity;
} MinHeap;

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(MinHeap* heap, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap->size && heap->data[left] < heap->data[smallest])
        smallest = left;

    if (right < heap->size && heap->data[right] < heap->data[smallest])
        smallest = right;

    if (smallest != i) {
        swap(&heap->data[i], &heap->data[smallest]);
        minHeapify(heap, smallest);
    }
}

void insertMinHeap(MinHeap* heap, int key) {
    if (heap->size == heap->capacity) {
        printf("Overflow: Could not insertKey\n");
        return;
    }

    int i = heap->size;
    heap->data[i] = key;
    heap->size++;
    while (i != 0 && heap->data[(i - 1) / 2] > heap->data[i]) {
        swap(&heap->data[i], &heap->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int extractMin(MinHeap* heap) {
    if (heap->size <= 0)
        return INT_MAX;
    if (heap->size == 1) {
        heap->size--;
        return heap->data[0];
    }

    int root = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    minHeapify(heap, 0);

    return root;
}

int nthSuperUglyNumber(int n, int k, int* primes) {
    int ugly[n];
    memset(ugly, 0, sizeof(ugly));
    ugly[0] = 1;

    MinHeap heap;
    heap.data = (int*)malloc(k * sizeof(int));
    heap.size = 0;
    heap.capacity = k;

    for (int i = 0; i < k; i++)
        insertMinHeap(&heap, primes[i]);

    for (int i = 1; i < n; i++) {
        int next_ugly_no = extractMin(&heap);
        ugly[i] = next_ugly_no;

        for (int j = 0; j < k; j++) {
            long long new_ugly = (long long)primes[j] * next_ugly_no;
            if (new_ugly > INT_MAX)
                break;
            if (new_ugly > ugly[i-1]) {
                insertMinHeap(&heap, (int)new_ugly);
                break;
            }
        }
    }

    free(heap.data);
    return ugly[n-1];
}

int main() {
    int n = 12;
    int k = 4;
    int primes[] = {2, 7, 13, 19};
    int result = nthSuperUglyNumber(n, k, primes);
    printf("%d\n", result);
    return 0;
}