#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    long long *data;
    int capacity;
    int size;
} MinHeap;

MinHeap* create_heap(int capacity) {
    MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
    if (!heap) return NULL;
    heap->data = (long long*)malloc(sizeof(long long) * capacity);
    if (!heap->data) {
        free(heap);
        return NULL;
    }
    heap->capacity = capacity;
    heap->size = 0;
    return heap;
}

void free_heap(MinHeap *heap) {
    if (heap) {
        if (heap->data) {
            free(heap->data);
        }
        free(heap);
    }
}

void push_heap(MinHeap *heap, long long val) {
    if (heap->size >= heap->capacity) {
        int new_capacity = heap->capacity == 0 ? 8 : heap->capacity * 2;
        long long *new_data = (long long*)realloc(heap->data, sizeof(long long) * new_capacity);
        if (!new_data) {
            exit(EXIT_FAILURE);
        }
        heap->data = new_data;
        heap->capacity = new_capacity;
    }
    heap->data[heap->size] = val;
    int i = heap->size;
    heap->size++;
    while (i > 0 && heap->data[i] < heap->data[(i - 1) / 2]) {
        long long temp = heap->data[i];
        heap->data[i] = heap->data[(i - 1) / 2];
        heap->data[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

void heapify(MinHeap *heap, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < heap->size && heap->data[left] < heap->data[smallest]) {
        smallest = left;
    }
    if (right < heap->size && heap->data[right] < heap->data[smallest]) {
        smallest = right;
    }
    if (smallest != i) {
        long long temp = heap->data[i];
        heap->data[i] = heap->data[smallest];
        heap->data[smallest] = temp;
        heapify(heap, smallest);
    }
}

long long pop_heap(MinHeap *heap) {
    if (heap->size <= 0) {
        exit(EXIT_FAILURE);
    }
    long long val = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    if (heap->size > 0) {
        heapify(heap, 0);
    }
    return val;
}

long long nthSuperUglyNumber(int n, const int* primes, int k) {
    if (n <= 0 || primes == NULL || k <= 0) {
        return -1;
    }
    MinHeap *heap = create_heap(n * k + 2);
    if (!heap) {
        return -1;
    }
    push_heap(heap, 1);
    long long prev = 0;
    long long val = 1;
    for (int i = 0; i < n; ) {
        val = pop_heap(heap);
        if (val == prev) {
            continue;
        }
        prev = val;
        i++;
        for (int j = 0; j < k; j++) {
            if (primes[j] != 0 && val > LLONG_MAX / primes[j]) {
                continue;
            }
            push_heap(heap, val * primes[j]);
        }
    }
    free_heap(heap);
    return val;
}

int main(void) {
    int primes[] = {2, 7, 13, 19};
    int k = sizeof(primes) / sizeof(primes[0]);
    int n = 12;
    long long result = nthSuperUglyNumber(n, primes, k);
    printf("%lld\n", result);
    return 0;
}