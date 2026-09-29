#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    unsigned long long *data;
    int capacity;
    int size;
} min_heap_t;

void swap_ull(unsigned long long *a, unsigned long long *b) {
    unsigned long long temp = *a;
    *a = *b;
    *b = temp;
}

min_heap_t *create_heap(int capacity) {
    min_heap_t *heap = (min_heap_t *)malloc(sizeof(min_heap_t));
    if (heap == NULL) {
        return NULL;
    }
    heap->data = (unsigned long long *)malloc(sizeof(unsigned long long) * capacity);
    if (heap->data == NULL) {
        free(heap);
        return NULL;
    }
    heap->capacity = capacity;
    heap->size = 0;
    return heap;
}

void destroy_heap(min_heap_t *heap) {
    if (heap != NULL) {
        if (heap->data != NULL) {
            free(heap->data);
        }
        free(heap);
    }
}

void heapify_up(min_heap_t *heap, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap->data[index] >= heap->data[parent]) {
            break;
        }
        swap_ull(&heap->data[index], &heap->data[parent]);
        index = parent;
    }
}

void heapify_down(min_heap_t *heap, int index) {
    while (1) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;
        if (left < heap->size && heap->data[left] < heap->data[smallest]) {
            smallest = left;
        }
        if (right < heap->size && heap->data[right] < heap->data[smallest]) {
            smallest = right;
        }
        if (smallest == index) {
            break;
        }
        swap_ull(&heap->data[index], &heap->data[smallest]);
        index = smallest;
    }
}

int heap_push(min_heap_t *heap, unsigned long long value) {
    if (heap == NULL || heap->size >= heap->capacity) {
        return 0;
    }
    heap->data[heap->size] = value;
    heapify_up(heap, heap->size);
    heap->size++;
    return 1;
}

unsigned long long heap_pop(min_heap_t *heap) {
    unsigned long long min_val = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    if (heap->size > 0) {
        heapify_down(heap, 0);
    }
    return min_val;
}

unsigned long long nth_super_ugly_number(int n, int *primes, int k) {
    if (n <= 0 || primes == NULL || k <= 0) {
        return 0;
    }
    int capacity = n * k + 2;
    min_heap_t *heap = create_heap(capacity);
    if (heap == NULL) {
        return 0;
    }
    if (!heap_push(heap, 1)) {
        destroy_heap(heap);
        return 0;
    }
    unsigned long long ugly = 0;
    unsigned long long last_ugly = 0;
    int count = 0;
    while (count < n) {
        ugly = heap_pop(heap);
        if (ugly == last_ugly) {
            continue;
        }
        last_ugly = ugly;
        count++;
        if (count == n) {
            break;
        }
        for (int i = 0; i < k; i++) {
            if (ugly <= ULLONG_MAX / primes[i]) {
                unsigned long long next_ugly = ugly * primes[i];
                if (!heap_push(heap, next_ugly)) {
                    destroy_heap(heap);
                    return 0;
                }
            }
        }
    }
    destroy_heap(heap);
    return ugly;
}

int main() {
    int primes[] = {2, 7, 13, 19};
    int k = sizeof(primes) / sizeof(primes[0]);
    int n = 12;
    unsigned long long result = nth_super_ugly_number(n, primes, k);
    printf("%llu\n", result);
    return 0;
}