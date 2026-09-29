#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

typedef long long i64;

typedef struct {
    i64 *data;
    size_t size;
    size_t capacity;
} MinHeap;

static int min_heap_init(MinHeap *heap, size_t capacity)
{
    if (heap == NULL || capacity == 0U || capacity > SIZE_MAX / sizeof(i64)) {
        return -1;
    }
    heap->data = (i64 *)malloc(capacity * sizeof(heap->data[0]));
    if (heap->data == NULL) {
        return -1;
    }
    heap->size = 0U;
    heap->capacity = capacity;
    return 0;
}

static void min_heap_destroy(MinHeap *heap)
{
    if (heap != NULL) {
        free(heap->data);
        heap->data = NULL;
        heap->size = 0U;
        heap->capacity = 0U;
    }
}

static int min_heap_grow(MinHeap *heap)
{
    size_t new_capacity;
    i64 *new_data;

    if (heap->size < heap->capacity) {
        return 0;
    }
    if (heap->capacity > SIZE_MAX / 2U) {
        return -1;
    }
    new_capacity = heap->capacity * 2U;
    if (new_capacity > SIZE_MAX / sizeof(heap->data[0])) {
        return -1;
    }
    new_data = (i64 *)realloc(heap->data, new_capacity * sizeof(heap->data[0]));
    if (new_data == NULL) {
        return -1;
    }
    heap->data = new_data;
    heap->capacity = new_capacity;
    return 0;
}

static int min_heap_push(MinHeap *heap, i64 value)
{
    size_t index;

    if (heap == NULL || min_heap_grow(heap) != 0) {
        return -1;
    }
    index = heap->size;
    heap->data[index] = value;
    heap->size++;
    while (index > 0U) {
        size_t parent = (index - 1U) / 2U;
        if (heap->data[parent] <= heap->data[index]) {
            break;
        }
        {
            i64 tmp = heap->data[parent];
            heap->data[parent] = heap->data[index];
            heap->data[index] = tmp;
        }
        index = parent;
    }
    return 0;
}

static i64 min_heap_top(const MinHeap *heap)
{
    return heap->data[0];
}

static void min_heap_pop(MinHeap *heap)
{
    size_t index = 0U;

    if (heap == NULL || heap->size == 0U) {
        return;
    }
    heap->size--;
    heap->data[0] = heap->data[heap->size];
    while (index < heap->size) {
        size_t left = 2U * index + 1U;
        size_t right = 2U * index + 2U;
        size_t smallest = index;

        if (left < heap->size && heap->data[left] < heap->data[smallest]) {
            smallest = left;
        }
        if (right < heap->size && heap->data[right] < heap->data[smallest]) {
            smallest = right;
        }
        if (smallest == index) {
            break;
        }
        {
            i64 tmp = heap->data[index];
            heap->data[index] = heap->data[smallest];
            heap->data[smallest] = tmp;
        }
        index = smallest;
    }
}

int nth_super_ugly_number(int n, const int *primes, int k, i64 *result)
{
    MinHeap heap;
    i64 current = 1;
    int i;
    int j;

    if (result == NULL || n <= 0 || primes == NULL || k <= 0) {
        return -1;
    }
    for (j = 0; j < k; j++) {
        if (primes[j] < 2) {
            return -1;
        }
    }
    if (min_heap_init(&heap, (size_t)k + 1U) != 0) {
        return -1;
    }
    if (min_heap_push(&heap, 1) != 0) {
        min_heap_destroy(&heap);
        return -1;
    }
    for (i = 0; i < n; i++) {
        if (heap.size == 0U) {
            min_heap_destroy(&heap);
            return -1;
        }
        current = min_heap_top(&heap);
        min_heap_pop(&heap);
        while (heap.size > 0U && min_heap_top(&heap) == current) {
            min_heap_pop(&heap);
        }
        for (j = 0; j < k; j++) {
            i64 next;

            if (current > LLONG_MAX / (i64)primes[j]) {
                continue;
            }
            next = current * (i64)primes[j];
            if (min_heap_push(&heap, next) != 0) {
                min_heap_destroy(&heap);
                return -1;
            }
        }
    }
    min_heap_destroy(&heap);
    *result = current;
    return 0;
}

int main(void)
{
    int primes[] = {2, 7, 13, 19};
    int k = (int)(sizeof(primes) / sizeof(primes[0]));
    int n = 12;
    i64 result = 0;

    if (nth_super_ugly_number(n, primes, k, &result) != 0) {
        fprintf(stderr, "error: unable to compute the %d-th super ugly number\n", n);
        return EXIT_FAILURE;
    }
    printf("The %d-th super ugly number is %lld\n", n, result);
    return EXIT_SUCCESS;
}