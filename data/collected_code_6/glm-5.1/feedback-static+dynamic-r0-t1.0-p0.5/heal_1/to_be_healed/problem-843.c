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
    if (heap != NULL) {
        free(heap->data);
        free(heap);
    }
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
    HeapNode empty = {0, 0, 0};
    if (heap->size == 0) {
        return empty;
    }
    HeapNode min_node = heap->data[0];
    heap->size--;
    if (heap->size > 0) {
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
    }
    return min_node;
}

/* Possible weaknesses found:
 *  Parameter 'primes' can be declared as pointer to const [constParameterPointer]
 */
long long nthSuperUglyNumber(int n, int* primes, int primesSize) {
    if (n <= 0 || primes == NULL || primesSize <= 0) {
        return 0;
    }
    MinHeap *heap = create_heap(primesSize * 100);
    if (heap == NULL || heap->data == NULL) {
        return 0;
    }
    HeapNode initial = {1, 0, 1};
    push_heap(heap, initial);
    long long current_ugly = 1;
    for (int i = 0; i < n; i++) {
        HeapNode top = pop_heap(heap);
        current_ugly = top.value;
        while (heap->size > 0 && heap->data[0].value == current_ugly) {
            HeapNode duplicate = pop_heap(heap);
            HeapNode next_node;
            next_node.value = duplicate.last_value * primes[duplicate.prime_index];
            next_node.prime_index = duplicate.prime_index;
            next_node.last_value = duplicate.last_value;
            if (next_node.value > 0) {
                push_heap(heap, next_node);
            }
        }
        for (int j = top.prime_index; j < primesSize; j++) {
            HeapNode next_node;
            next_node.value = current_ugly * primes[j];
            next_node.prime_index = j;
            next_node.last_value = current_ugly;
            if (next_node.value > 0) {
                push_heap(heap, next_node);
            }
        }
    }
    destroy_heap(heap);
    return current_ugly;
}

int main() {
    int primes[] = {2, 7, 13, 19};
    int k = sizeof(primes) / sizeof(primes[0]);
    int n = 12;
    long long result = nthSuperUglyNumber(n, primes, k);
    printf("%lld\n", result);
    return 0;
}