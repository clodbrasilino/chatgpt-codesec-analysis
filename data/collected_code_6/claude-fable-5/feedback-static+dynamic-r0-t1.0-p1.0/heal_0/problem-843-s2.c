#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    unsigned long long value;
    size_t prime_index;
    size_t ugly_index;
} HeapNode;

typedef struct {
    HeapNode *nodes;
    size_t size;
    size_t capacity;
} MinHeap;

static int heap_init(MinHeap *heap, size_t capacity)
{
    if (heap == NULL || capacity == 0U) {
        return -1;
    }
    heap->nodes = malloc(capacity * sizeof(HeapNode));
    if (heap->nodes == NULL) {
        return -1;
    }
    heap->size = 0U;
    heap->capacity = capacity;
    return 0;
}

static void heap_destroy(MinHeap *heap)
{
    if (heap != NULL) {
        free(heap->nodes);
        heap->nodes = NULL;
        heap->size = 0U;
        heap->capacity = 0U;
    }
}

static void heap_swap(HeapNode *a, HeapNode *b)
{
    HeapNode tmp = *a;
    *a = *b;
    *b = tmp;
}

static int heap_push(MinHeap *heap, HeapNode node)
{
    size_t i;

    if (heap == NULL || heap->size >= heap->capacity) {
        return -1;
    }
    heap->nodes[heap->size] = node;
    i = heap->size;
    heap->size++;
    while (i > 0U) {
        size_t parent = (i - 1U) / 2U;
        if (heap->nodes[i].value < heap->nodes[parent].value) {
            heap_swap(&heap->nodes[i], &heap->nodes[parent]);
            i = parent;
        } else {
            break;
        }
    }
    return 0;
}

static int heap_pop(MinHeap *heap, HeapNode *out)
{
    size_t i;

    if (heap == NULL || out == NULL || heap->size == 0U) {
        return -1;
    }
    *out = heap->nodes[0];
    heap->size--;
    heap->nodes[0] = heap->nodes[heap->size];
    i = 0U;
    for (;;) {
        size_t left = (2U * i) + 1U;
        size_t right = (2U * i) + 2U;
        size_t smallest = i;

        if (left < heap->size &&
            heap->nodes[left].value < heap->nodes[smallest].value) {
            smallest = left;
        }
        if (right < heap->size &&
            heap->nodes[right].value < heap->nodes[smallest].value) {
            smallest = right;
        }
        if (smallest == i) {
            break;
        }
        heap_swap(&heap->nodes[i], &heap->nodes[smallest]);
        i = smallest;
    }
    return 0;
}

static int nth_super_ugly_number(size_t n, const unsigned int *primes,
                                 size_t k, unsigned long long *result)
{
    unsigned long long *ugly = NULL;
    MinHeap heap;
    size_t i;
    int status = -1;

    if (n == 0U || primes == NULL || k == 0U || result == NULL) {
        return -1;
    }
    for (i = 0U; i < k; i++) {
        if (primes[i] < 2U) {
            return -1;
        }
    }

    ugly = malloc(n * sizeof(unsigned long long));
    if (ugly == NULL) {
        return -1;
    }
    if (heap_init(&heap, k) != 0) {
        free(ugly);
        return -1;
    }

    ugly[0] = 1ULL;
    for (i = 0U; i < k; i++) {
        HeapNode node;
        node.value = (unsigned long long)primes[i];
        node.prime_index = i;
        node.ugly_index = 0U;
        if (heap_push(&heap, node) != 0) {
            goto cleanup;
        }
    }

    for (i = 1U; i < n; i++) {
        HeapNode top;

        do {
            if (heap_pop(&heap, &top) != 0) {
                goto cleanup;
            }
            if (top.value != ugly[i - 1U]) {
                break;
            }
            top.ugly_index++;
            if (top.ugly_index >= i) {
                goto cleanup;
            }
            if (ugly[top.ugly_index] >
                ULLONG_MAX / (unsigned long long)primes[top.prime_index]) {
                goto cleanup;
            }
            top.value = ugly[top.ugly_index] *
                        (unsigned long long)primes[top.prime_index];
            if (heap_push(&heap, top) != 0) {
                goto cleanup;
            }
        } while (heap.size > 0U);

        if (top.value == ugly[i - 1U]) {
            goto cleanup;
        }

        ugly[i] = top.value;
        top.ugly_index++;
        if (top.ugly_index <= i) {
            if (ugly[top.ugly_index] >
                ULLONG_MAX / (unsigned long long)primes[top.prime_index]) {
                goto cleanup;
            }
            top.value = ugly[top.ugly_index] *
                        (unsigned long long)primes[top.prime_index];
            if (heap_push(&heap, top) != 0) {
                goto cleanup;
            }
        }
    }

    *result = ugly[n - 1U];
    status = 0;

cleanup:
    heap_destroy(&heap);
    free(ugly);
    return status;
}

int main(void)
{
    unsigned int primes[] = {2U, 7U, 13U, 19U};
    size_t k = sizeof(primes) / sizeof(primes[0]);
    size_t n = 12U;
    unsigned long long result = 0ULL;

    if (nth_super_ugly_number(n, primes, k, &result) != 0) {
        fprintf(stderr, "Failed to compute super ugly number\n");
        return EXIT_FAILURE;
    }

    printf("The %zu-th super ugly number is %llu\n", n, result);

    if (nth_super_ugly_number(1U, primes, k, &result) != 0) {
        fprintf(stderr, "Failed to compute super ugly number\n");
        return EXIT_FAILURE;
    }

    printf("The 1st super ugly number is %llu\n", result);

    return EXIT_SUCCESS;
}