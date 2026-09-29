#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct {
    long long *data;
    int size;
    int capacity;
} MinHeap;

void swap(long long *a, long long *b) {
    long long temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(MinHeap *heap, int i) {
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

void insertMinHeap(MinHeap *heap, long long key) {
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->data = (long long *)realloc(heap->data, heap->capacity * sizeof(long long));
    }

    int i = heap->size;
    heap->data[i] = key;
    heap->size++;

    while (i != 0 && heap->data[(i - 1) / 2] > heap->data[i]) {
        swap(&heap->data[i], &heap->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

long long extractMin(MinHeap *heap) {
    if (heap->size <= 0)
        return LLONG_MAX;

    if (heap->size == 1) {
        long long root = heap->data[0];
        heap->size--;
        return root;
    }

    long long root = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    minHeapify(heap, 0);

    return root;
}

int nthSuperUglyNumber(int n, int k, const int primes[]) {
    long long ugly[n];
    ugly[0] = 1;

    MinHeap heap;
    heap.data = (long long *)malloc(k * sizeof(long long));
    heap.size = k;
    heap.capacity = k;

    for (int i = 0; i < k; i++)
        heap.data[i] = (long long)primes[i];

    int index[k];
    for (int i = 0; i < k; i++)
        index[i] = 0;

    for (int i = 1; i < n; i++) {
        long long nextUgly = extractMin(&heap);
        ugly[i] = nextUgly;

        for (int j = 0; j < k; j++) {
            if (nextUgly % primes[j] == 0) {
                index[j]++;
                insertMinHeap(&heap, (long long)primes[j] * ugly[index[j]]);
            }
        }
    }

    free(heap.data);
    return (int)ugly[n - 1];
}

int main() {
    int n = 12;
    int k = 4;
    const int primes[] = {2, 7, 13, 19};

    int result = nthSuperUglyNumber(n, k, primes);
    printf("The %dth super ugly number is: %d\n", n, result);

    return 0;
}