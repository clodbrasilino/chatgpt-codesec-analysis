#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

typedef struct {
    long long *data;
    size_t size;
    size_t capacity;
} MinHeap;

static int heap_init(MinHeap *heap, size_t capacity)
{
    if (heap == NULL || capacity == 0) {
        return 0;
    }
    heap->data = (long long *)malloc(capacity * sizeof(long long));
    if (heap->data == NULL) {
        heap->size = 0;
        heap->capacity = 0;
        return 0;
    }
    heap->size = 0;
    heap->capacity = capacity;
    return 1;
}

static void heap_destroy(MinHeap *heap)
{
    if (heap == NULL) {
        return;
    }
    free(heap->data);
    heap->data = NULL;
    heap->size = 0;
    heap->capacity = 0;
}

static void heap_swap(long long *a, long long *b)
{
    long long temp = *a;
    *a = *b;
    *b = temp;
}

static int heap_push(MinHeap *heap, long long value)
{
    size_t i;

    if (heap == NULL) {
        return 0;
    }
    if (heap->size == heap->capacity) {
        size_t new_capacity = heap->capacity * 2;
        long long *new_data;

        if (new_capacity < heap->capacity ||
            new_capacity > SIZE_MAX / sizeof(long long)) {
            return 0;
        }
        new_data = (long long *)realloc(heap->data,
                                        new_capacity * sizeof(long long));
        if (new_data == NULL) {
            return 0;
        }
        heap->data = new_data;
        heap->capacity = new_capacity;
    }
    i = heap->size;
    heap->size++;
    heap->data[i] = value;
    while (i > 0) {
        size_t parent = (i - 1) / 2;

        if (heap->data[parent] <= heap->data[i]) {
            break;
        }
        heap_swap(&heap->data[parent], &heap->data[i]);
        i = parent;
    }
    return 1;
}

static int heap_pop(MinHeap *heap, long long *out)
{
    if (heap == NULL || out == NULL || heap->size == 0) {
        return 0;
    }
    *out = heap->data[0];
    heap->size--;
    if (heap->size > 0) {
        size_t i = 0;

        heap->data[0] = heap->data[heap->size];
        for (;;) {
            size_t left = 2 * i + 1;
            size_t right = 2 * i + 2;
            size_t smallest = i;

            if (left < heap->size &&
                heap->data[left] < heap->data[smallest]) {
                smallest = left;
            }
            if (right < heap->size &&
                heap->data[right] < heap->data[smallest]) {
                smallest = right;
            }
            if (smallest == i) {
                break;
            }
            heap_swap(&heap->data[i], &heap->data[smallest]);
            i = smallest;
        }
    }
    return 1;
}

long long nth_super_ugly_number(int n, const int *primes, int k)
{
    MinHeap heap;
    long long current = 0;
    long long last = 0;
    int count = 0;
    int status = 1;
    int i;

    if (n <= 0 || primes == NULL || k <= 0) {
        return -1;
    }
    for (i = 0; i < k; i++) {
        if (primes[i] < 2) {
            return -1;
        }
    }
    if (!heap_init(&heap, 16)) {
        return -1;
    }
    if (!heap_push(&heap, 1)) {
        heap_destroy(&heap);
        return -1;
    }
    while (count < n) {
        if (!heap_pop(&heap, &current)) {
            status = 0;
            break;
        }
        if (current == last) {
            continue;
        }
        last = current;
        count++;
        for (i = 0; i < k; i++) {
            if (current > LLONG_MAX / (long long)primes[i]) {
                continue;
            }
            if (!heap_push(&heap, current * (long long)primes[i])) {
                status = 0;
                break;
            }
        }
        if (!status) {
            break;
        }
    }
    heap_destroy(&heap);
    if (!status) {
        return -1;
    }
    return current;
}

int main(void)
{
    int primes[] = {2, 7, 13, 19};
    int k = (int)(sizeof(primes) / sizeof(primes[0]));
    int n = 12;
    long long result;

    result = nth_super_ugly_number(n, primes, k);
    if (result < 0) {
        fprintf(stderr, "Error: unable to compute the %dth super ugly number.\n", n);
        return EXIT_FAILURE;
    }
    printf("The %dth super ugly number is %lld\n", n, result);
    return EXIT_SUCCESS;
}