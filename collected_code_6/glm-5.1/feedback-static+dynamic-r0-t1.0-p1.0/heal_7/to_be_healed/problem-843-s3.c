#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long value;
    int prime_index;
    int ugly_index;
} HeapNode;

typedef struct {
    HeapNode *data;
    int capacity;
    int size;
} MinHeap;

MinHeap* create_heap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (HeapNode*)malloc(capacity * sizeof(HeapNode));
    heap->capacity = capacity;
    heap->size = 0;
    return heap;
}

void swap_nodes(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void push_heap(MinHeap* heap, HeapNode node) {
    if (heap->size >= heap->capacity) return;
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

HeapNode pop_heap(MinHeap* heap) {
    HeapNode empty = {0, 0, 0};
    if (heap->size == 0) return empty;
    HeapNode root = heap->data[0];
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
                swap_nodes(&heap->data[current], &heap->data[smallest]);
                current = smallest;
            } else {
                break;
            }
        }
    }
    return root;
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected 32, got 0
  *  test case 1 failed: expected 26, got 0
  *  test case 2 failed: expected 5408, got 0
  */

int nth_super_ugly_number(int n, int* primes, int k) {
    if (n <= 0 || k <= 0 || primes == NULL) return 0;
    if (n == 1) return 1;
    
    long long *ugly = (long long*)malloc(n * sizeof(long long));
    ugly[0] = 1;
    
    MinHeap* heap = create_heap(n * k + 1);
    for (int i = 0; i < k; i++) {
        HeapNode node;
        node.value = (long long)primes[i];
        node.prime_index = i;
        node.ugly_index = 1;
        push_heap(heap, node);
    }
    
    for (int i = 1; i < n; i++) {
        HeapNode top = pop_heap(heap);
        ugly[i] = top.value;
        
        while (heap->size > 0 && heap->data[0].value == top.value) {
            HeapNode dup = pop_heap(heap);
            if (dup.ugly_index + 1 < n) {
                push_heap(heap, (HeapNode){ugly[dup.ugly_index + 1] * (long long)primes[dup.prime_index], dup.prime_index, dup.ugly_index + 1});
            }
        }
        
        if (top.ugly_index + 1 < n) {
            push_heap(heap, (HeapNode){ugly[top.ugly_index + 1] * (long long)primes[top.prime_index], top.prime_index, top.ugly_index + 1});
        }
    }
    
    long long result = ugly[n - 1];
    free(ugly);
    free(heap->data);
    free(heap);
    return (int)result;
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