#include <stdio.h>
#include <stdlib.h>

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

void insertMinHeap(MinHeap *heap, int value) {
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->data = realloc(heap->data, heap->capacity * sizeof(int));
    }

    int i = heap->size;
    heap->data[i] = value;
    heap->size++;

    while (i != 0 && heap->data[(i - 1) / 2] > heap->data[i]) {
        swap(&heap->data[i], &heap->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int extractMin(MinHeap *heap) {
    if (heap->size <= 0)
        return -1;

    int root = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    minHeapify(heap, 0);

    return root;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 26, got 0
  *  test case 2 failed: expected 5408, got 0
  *  test case 0 failed: expected 32, got 0
  */

int nthSuperUglyNumber(int n, int k, const int primes[]) {
    int *ugly = malloc(n * sizeof(int));
    if (ugly == NULL) return -1;
    ugly[0] = 1;

    MinHeap heap;
    heap.data = malloc(k * sizeof(int));
    if (heap.data == NULL) {
        free(ugly);
        return -1;
    }
    heap.size = 0;
    heap.capacity = k;

    for (int i = 0; i < k; i++)
        insertMinHeap(&heap, primes[i]);

    int *nextMultiple = malloc(k * sizeof(int));
    if (nextMultiple == NULL) {
        free(ugly);
        free(heap.data);
        return -1;
    }
    for (int i = 0; i < k; i++)
        nextMultiple[i] = primes[i];

    int *index = malloc(k * sizeof(int));
    if (index == NULL) {
        free(ugly);
        free(heap.data);
        free(nextMultiple);
        return -1;
    }
    for (int i = 0; i < k; i++)
        index[i] = 0;

    for (int i = 1; i < n; i++) {
        int nextUgly = extractMin(&heap);
        ugly[i] = nextUgly;

        for (int j = 0; j < k; j++) {
            if (nextMultiple[j] == nextUgly) {
                index[j]++;
                nextMultiple[j] = ugly[index[j]] * primes[j];
                insertMinHeap(&heap, nextMultiple[j]);
            }
        }
    }

    free(heap.data);
    free(nextMultiple);
    free(index);
    int result = ugly[n - 1];
    free(ugly);
    return result;
}

int main() {
    const int primes[] = {2, 3, 5};
    int k = 3;
    int n = 12;
    printf("The %dth super ugly number is: %d\n", n, nthSuperUglyNumber(n, k, primes));
    return 0;
}