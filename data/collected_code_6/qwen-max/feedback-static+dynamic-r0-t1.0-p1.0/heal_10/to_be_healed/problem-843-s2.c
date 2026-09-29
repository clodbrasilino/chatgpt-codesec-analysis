#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_HEAP_SIZE 10000

typedef struct {
    int* array;
    int size;
} MinHeap;

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(MinHeap* heap, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap->size && heap->array[left] < heap->array[smallest])
        smallest = left;

    if (right < heap->size && heap->array[right] < heap->array[smallest])
        smallest = right;

    if (smallest != i) {
        swap(&heap->array[i], &heap->array[smallest]);
        heapify(heap, smallest);
    }
}

void buildHeap(MinHeap* heap) {
    for (int i = (heap->size / 2) - 1; i >= 0; i--)
        heapify(heap, i);
}

void insert(MinHeap* heap, int key) {
    if (heap->size == MAX_HEAP_SIZE) return;
    int i = heap->size;
    heap->array[i] = key;
    heap->size++;
    while (i > 0 && heap->array[(i - 1) / 2] > heap->array[i]) {
        swap(&heap->array[(i - 1) / 2], &heap->array[i]);
        i = (i - 1) / 2;
    }
}

int extractMin(MinHeap* heap) {
    if (heap->size <= 0) return INT_MAX;
    if (heap->size == 1) {
        heap->size--;
        return heap->array[0];
    }

    int root = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;
    heapify(heap, 0);

    return root;
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected 32, got <no output>
  *  test case 2 failed: expected 5408, got <no output>
  *  test case 1 failed: expected 26, got <no output>
  */

int nthSuperUglyNumber(int n, int k, const int primes[]) {
    int* ugly = (int*)malloc(n * sizeof(int));
    int* index = (int*)malloc(k * sizeof(int));
    for (int i = 0; i < k; i++) index[i] = 0;

    MinHeap heap;
    heap.array = (int*)malloc(MAX_HEAP_SIZE * sizeof(int));
    /* Possible weaknesses found:
     *  Variable 'heap.size' is assigned a value that is never used. [unreadVariable]
     */
    heap.size = 0;

    ugly[0] = 1;
    for (int i = 1; i < n; i++) {
        int min_val = INT_MAX;
        for (int j = 0; j < k; j++)
            if (primes[j] * ugly[index[j]] < min_val) {
                min_val = primes[j] * ugly[index[j]];
            }

        ugly[i] = min_val;
        for (int j = 0; j < k; j++)
            if (primes[j] * ugly[index[j]] == ugly[i])
                index[j]++;
    }

    free(ugly);
    free(index);
    free(heap.array);

    return ugly[n - 1];
}

int main() {
    int n = 12;
    int k = 4;
    const int primes[] = {2, 7, 13, 19};
    printf("The %dth super ugly number is: %d\n", n, nthSuperUglyNumber(n, k, primes));
    return 0;
}