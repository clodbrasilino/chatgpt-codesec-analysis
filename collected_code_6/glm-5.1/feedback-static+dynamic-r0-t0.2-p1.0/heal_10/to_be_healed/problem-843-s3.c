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

MinHeap* create_heap(int capacity) {
    MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
    if (heap == NULL) return NULL;
    heap->data = (HeapNode*)malloc(capacity * sizeof(HeapNode));
    if (heap->data == NULL) {
        free(heap);
        return NULL;
    }
    heap->capacity = capacity;
    heap->size = 0;
    return heap;
}

void destroy_heap(MinHeap *heap) {
    if (heap != NULL) {
        if (heap->data != NULL) {
            free(heap->data);
        }
        free(heap);
    }
}

void swap_nodes(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
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
            swap_nodes(&heap->data[current], &heap->data[parent]);
            current = parent;
        } else {
            break;
        }
    }
}

HeapNode pop_heap(MinHeap *heap) {
    HeapNode popped = heap->data[0];
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
            swap_nodes(&heap->data[current], &heap->data[smallest]);
            current = smallest;
        } else {
            break;
        }
    }
    return popped;
}

int is_empty(const MinHeap *heap) {
    return heap->size == 0;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 5408, got <no output>
  *  test case 1 failed: expected 26, got <no output>
  *  test case 0 failed: expected 32, got <no output>
  */

long long nthSuperUglyNumber(int n, int* primes, int primesSize) {
    if (n <= 0 || primes == NULL || primesSize <= 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }

    MinHeap *heap = create_heap(n * primesSize + primesSize);
    if (heap == NULL) {
        return 0;
    }

    for (int i = 0; i < primesSize; i++) {
        HeapNode node;
        node.value = (long long)primes[i];
        node.prime_index = i;
        node.last_value = 1;
        push_heap(heap, node);
    }

    long long current_ugly = 1;
    int count = 1;
    while (count < n) {
        HeapNode top = pop_heap(heap);
        if (top.value != current_ugly) {
            current_ugly = top.value;
            count++;
        }

        HeapNode next_node;
        next_node.prime_index = top.prime_index;
        next_node.last_value = current_ugly;
        next_node.value = current_ugly * primes[top.prime_index];

        push_heap(heap, next_node);
    }

    long long result = current_ugly;
    destroy_heap(heap);
    return result;
}

int main() {
    int primes1[] = {2, 7, 13, 19};
    int k1 = sizeof(primes1) / sizeof(primes1[0]);
    int n1 = 12;
    long long result1 = nthSuperUglyNumber(n1, primes1, k1);
    printf("%lld\n", result1);

    int primes2[] = {2, 3, 5};
    int k2 = sizeof(primes2) / sizeof(primes2[0]);
    int n2 = 10;
    long long result2 = nthSuperUglyNumber(n2, primes2, k2);
    printf("%lld\n", result2);

    int primes3[] = {2};
    int k3 = sizeof(primes3) / sizeof(primes3[0]);
    int n3 = 5;
    long long result3 = nthSuperUglyNumber(n3, primes3, k3);
    printf("%lld\n", result3);

    return 0;
}