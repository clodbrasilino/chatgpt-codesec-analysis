#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long value;
    int prime_index;
    long long last_value;
} HeapNode;

typedef struct {
    HeapNode *data;
    int capacity;
    int size;
} MinHeap;

void swap(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

MinHeap* create_heap(int capacity) {
    MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (HeapNode*)malloc(capacity * sizeof(HeapNode));
    heap->capacity = capacity;
    heap->size = 0;
    return heap;
}

void destroy_heap(MinHeap *heap) {
    free(heap->data);
    free(heap);
}

void push_heap(MinHeap *heap, HeapNode node) {
    if (heap->size == heap->capacity) {
        return;
    }
    heap->data[heap->size] = node;
    int current = heap->size;
    heap->size++;
    while (current > 0) {
        int parent = (current - 1) / 2;
        if (heap->data[current].value < heap->data[parent].value) {
            swap(&heap->data[current], &heap->data[parent]);
            current = parent;
        } else {
            break;
        }
    }
}

HeapNode pop_heap(MinHeap *heap) {
    if (heap->size == 0) {
        HeapNode empty = {0, 0, 0};
        return empty;
    }
    HeapNode root = heap->data[0];
    heap->size--;
    heap->data[0] = heap->data[heap->size];
    int current = 0;
    while (1) {
        int left = 2 * current + 1;
        int right = 2 * current + 2;
        int smallest = current;
        if (left < heap->size && heap->data[left].value < heap->data[smallest].value) {
            smallest = left;
        }
        if (right < heap->size && heap->data[right].value < heap->data[smallest].value) {
            smallest = right;
        }
        if (smallest != current) {
            swap(&heap->data[current], &heap->data[smallest]);
            current = smallest;
        } else {
            break;
        }
    }
    return root;
}

int nth_super_ugly_number(int n, const int *primes, int k) {
    if (n <= 0 || k <= 0) {
        return 0;
    }
    MinHeap *heap = create_heap(n * k + 1);
    HeapNode initial = {1, -1, 1};
    push_heap(heap, initial);
    long long result = 1;
    for (int i = 0; i < n; i++) {
        HeapNode top = pop_heap(heap);
        result = top.value;
        while (heap->size > 0 && heap->data[0].value == result) {
            pop_heap(heap);
        }
        int start = (top.prime_index == -1) ? 0 : top.prime_index;
        for (int j = start; j < k; j++) {
            HeapNode next = {result * primes[j], j, result};
            push_heap(heap, next);
        }
    }
    destroy_heap(heap);
    return (int)result;
}

int main() {
    int primes1[] = {2, 7, 13, 19};
    printf("%d\n", nth_super_ugly_number(12, primes1, sizeof(primes1) / sizeof(primes1[0])));
    int primes2[] = {2, 3, 5};
    printf("%d\n", nth_super_ugly_number(10, primes2, sizeof(primes2) / sizeof(primes2[0])));
    int primes3[] = {2, 5, 7, 11};
    printf("%d\n", nth_super_ugly_number(15, primes3, sizeof(primes3) / sizeof(primes3[0])));
    return 0;
}