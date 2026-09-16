#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

typedef struct {
    uint32_t value;
    uint32_t idx;
    uint32_t prime;
} HeapNode;

typedef struct {
    HeapNode *data;
    int size, capacity;
} MinHeap;

int cmp(const void *a, const void *b) {
    return ((HeapNode *)a)->value - ((HeapNode *)b)->value;
}

void heap_push(MinHeap *heap, HeapNode element) {
    if (heap->size == heap->capacity) {
        heap->capacity = 2 * heap->capacity + 1;
        heap->data = realloc(heap->data, sizeof(HeapNode) * heap->capacity);
    }
    heap->data[heap->size] = element;
    uint32_t i = heap->size;
    while (i != 0 && heap->data[(i - 1) / 2].value > heap->data[i].value) {
        HeapNode temp = heap->data[(i - 1) / 2];
        heap->data[(i - 1) / 2] = heap->data[i];
        heap->data[i] = temp;
        i = (i - 1) / 2;
    }
    heap->size++;
}

HeapNode heap_pop(MinHeap *heap) {
    HeapNode min = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    uint32_t i = 0;
    while (2 * i + 1 < heap->size) {
        uint32_t j = 2 * i + 1;
        if (j + 1 < heap->size && heap->data[j + 1].value < heap->data[j].value)
            j++;
        if (heap->data[i].value <= heap->data[j].value)
            break;
        HeapNode temp = heap->data[i];
        heap->data[i] = heap->data[j];
        heap->data[j] = temp;
        i = j;
    }
    return min;
}

uint32_t nthSuperUglyNumber(uint32_t n, int k, const uint32_t* primes) {
    MinHeap heap;
    heap.capacity = k;
    heap.size = 0;
    heap.data = malloc(sizeof(HeapNode) * heap.capacity);

    for (int i = 0; i < k; ++i) {
        heap_push(&heap, (HeapNode){primes[i], 1, primes[i]});
    }

    uint32_t ugly_numbers[n];
    memset(ugly_numbers, 0, n * sizeof(uint32_t));
    ugly_numbers[0] = 1;

    for (uint32_t i = 1; i < n; ++i) {
        HeapNode next = heap_pop(&heap);
        while (next.value == ugly_numbers[i - 1]) {
            next = heap_pop(&heap);
        }
        ugly_numbers[i] = next.value;
        heap_push(&heap, (HeapNode){ugly_numbers[next.idx - 1] * next.prime, next.idx, next.prime});
    }
    free(heap.data);
    return ugly_numbers[n - 1];
}

int main() {
    uint32_t n = 12;
    int k = 4;
    const uint32_t primes[] = {2, 7, 13, 19};
    printf("The %uth super ugly number is: %u\n", n, nthSuperUglyNumber(n, k, primes));
    return 0;
}