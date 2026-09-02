#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

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
    heap->size++;

    while (i != 0 && heap->data[(i - 1) / 2] > heap->data[i]) {
        swap(&heap->data[i], &heap->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int extractMin(MinHeap *heap) {
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
  *  test case 0 failed: expected 32, got 0
  *  test case 2 failed: expected 5408, got 0
  *  test case 1 failed: expected 26, got 0
  */

int nthSuperUglyNumber(int n, int k, const int primes[]) {
    int ugly[n];
    ugly[0] = 1;

    MinHeap heap;
    heap.data = (int *)malloc(k * sizeof(int));
    heap.size = k;
    heap.capacity = k;

    for (int i = 0; i < k; i++)
        heap.data[i] = primes[i];

    int index[k];
    for (int i = 0; i < k; i++)
        index[i] = 0;

    for (int i = 1; i < n; i++) {
        int nextUgly = extractMin(&heap);
        ugly[i] = nextUgly;

        for (int j = 0; j < k; j++) {
            if (primes[j] * ugly[index[j]] == nextUgly) {
                index[j]++;
                insertMinHeap(&heap, primes[j] * ugly[index[j]]);
            }
        }
    }

    free(heap.data);
    return ugly[n - 1];
}

int main() {
    int n = 12;
    int k = 4;
    const int primes[] = {2, 7, 13, 19};

    int result = nthSuperUglyNumber(n, k, primes);
    printf("The %dth super ugly number is: %d\n", n, result);

    return 0;
}