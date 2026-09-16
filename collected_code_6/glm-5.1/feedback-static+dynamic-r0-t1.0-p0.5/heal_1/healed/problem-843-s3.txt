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
        heap->capacity *= 2;
        heap->data = (HeapNode*)realloc(heap->data, heap->capacity * sizeof(HeapNode));
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

int nth_super_ugly_number(int n, int *primes, int k) {
    if (n <= 0 || k <= 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    MinHeap *heap = create_heap(k);
    long long *ugly = (long long*)malloc(n * sizeof(long long));
    int *indices = (int*)malloc(k * sizeof(int));
    ugly[0] = 1;
    for (int i = 0; i < k; i++) {
        indices[i] = 0;
        HeapNode node;
        node.value = (long long)primes[i];
        node.prime_index = i;
        node.last_value = 1;
        push_heap(heap, node);
    }
    int count = 1;
    while (count < n) {
        HeapNode top = pop_heap(heap);
        if (top.value != ugly[count - 1]) {
            ugly[count] = top.value;
            count++;
        } else {
            indices[top.prime_index]++;
            HeapNode next;
            next.prime_index = top.prime_index;
            next.last_value = ugly[indices[top.prime_index]];
            next.value = next.last_value * primes[top.prime_index];
            push_heap(heap, next);
            continue;
        }
        indices[top.prime_index]++;
        HeapNode next;
        next.prime_index = top.prime_index;
        next.last_value = ugly[indices[top.prime_index]];
        next.value = next.last_value * primes[top.prime_index];
        push_heap(heap, next);
    }
    int result = (int)ugly[n - 1];
    free(indices);
    free(ugly);
    destroy_heap(heap);
    return result;
}

int main() {
    int primes1[] = {2, 7, 13, 19};
    int k1 = sizeof(primes1) / sizeof(primes1[0]);
    int n1 = 12;
    int result1 = nth_super_ugly_number(n1, primes1, k1);
    printf("%d\n", result1);
    
    int primes2[] = {2, 3, 5};
    int k2 = sizeof(primes2) / sizeof(primes2[0]);
    int n2 = 10;
    int result2 = nth_super_ugly_number(n2, primes2, k2);
    printf("%d\n", result2);

    return 0;
}