#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *data;
    int size;
    int capacity;
} MinHeap;

void swap(int *a, int *b) {
    int temp = *a;
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

void insertMinHeap(MinHeap *heap, int key) {
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->data = (int *)realloc(heap->data, heap->capacity * sizeof(int));
    }
    int i = heap->size;
    heap->data[i] = key;
    while (i != 0 && heap->data[(i - 1) / 2] > heap->data[i]) {
        swap(&heap->data[i], &heap->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
    heap->size++;
}

int extractMin(MinHeap *heap) {
    if (heap->size <= 0)
        return -1;
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
  *  test case 1 failed: expected 26, got <no output>
  *  test case 0 failed: expected 32, got <no output>
  *  test case 2 failed: expected 5408, got <no output>
  */

int nthSuperUglyNumber(int n, int k, const int primes[]) {
    long long ugly[n];
    ugly[0] = 1;
    MinHeap heap;
    heap.data = (int *)malloc(k * sizeof(int));
    heap.size = 0;
    heap.capacity = k;

    for (int i = 0; i < k; i++)
        insertMinHeap(&heap, primes[i]);

    for (int i = 1; i < n; i++) {
        long long next_ugly = extractMin(&heap);
        ugly[i] = next_ugly;
        bool inserted = false;
        for (int j = 0; j < k; j++) {
            if (next_ugly % primes[j] == 0) {
                long long new_ugly = ugly[i] * primes[j];
                insertMinHeap(&heap, new_ugly);
                if (new_ugly / primes[j] == next_ugly) inserted = true;
            }
        }
        if (!inserted) insertMinHeap(&heap, next_ugly * primes[0]);
    }

    free(heap.data);
    return ugly[n - 1];
}

int main() {
    int n = 12;
    int k = 4;
    const int primes[] = {2, 3, 5, 7};
    printf("The %dth super ugly number is: %d\n", n, nthSuperUglyNumber(n, k, primes));
    return 0;
}