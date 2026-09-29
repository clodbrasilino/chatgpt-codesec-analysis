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
 /* Possible weaknesses found:
  *  test case 0 failed: expected 32, got <no output>
  *  test case 2 failed: expected 5408, got <no output>
  *  test case 1 failed: expected 26, got <no output>
  */

/* Possible weaknesses found:
 *  Parameter 'primes' can be declared as pointer to const [constParameterPointer]
 */
int nth_super_ugly_number(int n, int *primes, int k) {
    if (n <= 0 || k <= 0) {
        return 0;
    }
    MinHeap *heap = create_heap(n * k + 1);
    HeapNode initial = {1, 0, 1};
    push_heap(heap, initial);
    long long result = 1;
    for (int i = 0; i < n; i++) {
        HeapNode top = pop_heap(heap);
        result = top.value;
        while (heap->size > 0 && heap->data[0].value == top.value) {
            HeapNode dup = pop_heap(heap);
            HeapNode next_dup = {dup.prime_index < k ? dup.last_value * primes[dup.prime_index] : 0, dup.prime_index, dup.last_value};
            if (dup.prime_index < k) {
                push_heap(heap, next_dup);
            }
        }
        if (top.prime_index < k) {
            HeapNode next = {top.value * primes[top.prime_index], top.prime_index, top.value};
            push_heap(heap, next);
            HeapNode next_prime = {top.value * primes[top.prime_index + 1 < k ? top.prime_index + 1 : 0], top.prime_index + 1, top.value};
            if (top.prime_index + 1 < k) {
                push_heap(heap, next_prime);
            }
        }
    }
    destroy_heap(heap);
    return (int)result;
}

int main() {
    int primes[] = {2, 7, 13, 19};
    int k = sizeof(primes) / sizeof(primes[0]);
    int n = 12;
    int result = nth_super_ugly_number(n, primes, k);
    printf("%d\n", result);
    return 0;
}