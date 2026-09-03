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
 /* Possible weaknesses found:
  *  test case 2 failed: expected 5408, got 0
  *  test case 1 failed: expected 26, got 0
  *  test case 0 failed: expected 32, got 0
  */

int nthSuperUglyNumber(int n, int k, int* primes) {
    int ugly[n];
    memset(ugly, 0, sizeof(ugly));
    ugly[0] = 1;

    MinHeap heap;
    heap.data = (int*)malloc(n * sizeof(int));
    heap.size = 0;
    heap.capacity = n;

    for (int i = 0; i < k; i++)
        insertMinHeap(&heap, primes[i]);

    for (int i = 1; i < n; i++) {
        ugly[i] = extractMin(&heap);

        for (int j = 0; j < k; j++) {
            long long new_ugly = (long long)primes[j] * ugly[i];
            if (new_ugly > INT_MAX || new_ugly == ugly[i-1])
                continue;
            insertMinHeap(&heap, (int)new_ugly);
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