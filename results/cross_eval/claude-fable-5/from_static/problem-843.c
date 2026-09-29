#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned long long value;
    int prime_index;
    int ugly_index;
} HeapNode;

typedef struct {
    HeapNode *nodes;
    int size;
    int capacity;
} MinHeap;

static MinHeap *heap_create(int capacity)
{
    MinHeap *heap;

    if (capacity <= 0) {
        return NULL;
    }
    heap = malloc(sizeof(MinHeap));
    if (heap == NULL) {
        return NULL;
    }
    heap->nodes = malloc((size_t)capacity * sizeof(HeapNode));
    if (heap->nodes == NULL) {
        free(heap);
        return NULL;
    }
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

static void heap_destroy(MinHeap *heap)
{
    if (heap != NULL) {
        free(heap->nodes);
        free(heap);
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
    int i;

    if (heap == NULL || heap->size >= heap->capacity) {
        return -1;
    }
    heap->nodes[heap->size] = node;
    i = heap->size;
    heap->size++;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap->nodes[parent].value <= heap->nodes[i].value) {
            break;
        }
        heap_swap(&heap->nodes[parent], &heap->nodes[i]);
        i = parent;
    }
    return 0;
}

static int heap_pop(MinHeap *heap, HeapNode *out)
{
    int i;

    if (heap == NULL || heap->size == 0 || out == NULL) {
        return -1;
    }
    *out = heap->nodes[0];
    heap->size--;
    heap->nodes[0] = heap->nodes[heap->size];
    i = 0;
    for (;;) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

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

static int nth_super_ugly_number(int n, const int *primes, int k,
                                 unsigned long long *result)
{
    unsigned long long *ugly;
    MinHeap *heap;
    int count;
    int i;
    int status = -1;

    if (n <= 0 || k <= 0 || primes == NULL || result == NULL) {
        return -1;
    }
    for (i = 0; i < k; i++) {
        if (primes[i] <= 1) {
            return -1;
        }
    }
    ugly = malloc((size_t)n * sizeof(unsigned long long));
    if (ugly == NULL) {
        return -1;
    }
    heap = heap_create(k);
    if (heap == NULL) {
        free(ugly);
        return -1;
    }

    ugly[0] = 1ULL;
    for (i = 0; i < k; i++) {
        HeapNode node;
        node.value = (unsigned long long)primes[i];
        node.prime_index = i;
        node.ugly_index = 0;
        if (heap_push(heap, node) != 0) {
            goto cleanup;
        }
    }

    count = 1;
    while (count < n) {
        HeapNode top;
        if (heap_pop(heap, &top) != 0) {
            goto cleanup;
        }
        if (top.value != ugly[count - 1]) {
            ugly[count] = top.value;
            count++;
        }
        top.ugly_index++;
        if (top.ugly_index < n) {
            unsigned long long p = (unsigned long long)primes[top.prime_index];
            unsigned long long base = ugly[top.ugly_index];
            if (base > 0 && p > (unsigned long long)-1 / base) {
                goto cleanup;
            }
            top.value = p * base;
            if (heap_push(heap, top) != 0) {
                goto cleanup;
            }
        }
    }

    *result = ugly[n - 1];
    status = 0;

cleanup:
    heap_destroy(heap);
    free(ugly);
    return status;
}

int main(void)
{
    int primes[] = {2, 7, 13, 19};
    int k = (int)(sizeof(primes) / sizeof(primes[0]));
    int n = 12;
    unsigned long long result;

    if (nth_super_ugly_number(n, primes, k, &result) != 0) {
        fprintf(stderr, "Failed to compute the %dth super ugly number\n", n);
        return EXIT_FAILURE;
    }
    printf("The %dth super ugly number is %llu\n", n, result);
    return EXIT_SUCCESS;
}