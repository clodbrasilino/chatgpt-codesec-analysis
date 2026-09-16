#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    long long sum;
    size_t i;
    size_t j;
} HeapNode;

typedef struct {
    HeapNode *data;
    size_t size;
    size_t capacity;
} MinHeap;

static MinHeap *heap_create(size_t capacity)
{
    MinHeap *h;

    if (capacity == 0U || capacity > (SIZE_MAX / sizeof(HeapNode))) {
        return NULL;
    }
    h = malloc(sizeof(*h));
    if (h == NULL) {
        return NULL;
    }
    h->data = malloc(capacity * sizeof(*h->data));
    if (h->data == NULL) {
        free(h);
        return NULL;
    }
    h->size = 0U;
    h->capacity = capacity;
    return h;
}

static void heap_destroy(MinHeap *h)
{
    if (h != NULL) {
        free(h->data);
        free(h);
    }
}

static void heap_swap(HeapNode *a, HeapNode *b)
{
    HeapNode tmp = *a;
    *a = *b;
    *b = tmp;
}

static int heap_push(MinHeap *h, HeapNode node)
{
    size_t idx;

    if (h == NULL || h->size >= h->capacity) {
        return -1;
    }
    idx = h->size;
    h->data[idx] = node;
    h->size++;
    while (idx > 0U) {
        size_t parent = (idx - 1U) / 2U;
        if (h->data[parent].sum <= h->data[idx].sum) {
            break;
        }
        heap_swap(&h->data[parent], &h->data[idx]);
        idx = parent;
    }
    return 0;
}

static int heap_pop(MinHeap *h, HeapNode *out)
{
    size_t idx = 0U;

    if (h == NULL || out == NULL || h->size == 0U) {
        return -1;
    }
    *out = h->data[0];
    h->size--;
    h->data[0] = h->data[h->size];
    for (;;) {
        size_t left = (2U * idx) + 1U;
        size_t right = (2U * idx) + 2U;
        size_t smallest = idx;

        if (left < h->size && h->data[left].sum < h->data[smallest].sum) {
            smallest = left;
        }
        if (right < h->size && h->data[right].sum < h->data[smallest].sum) {
            smallest = right;
        }
        if (smallest == idx) {
            break;
        }
        heap_swap(&h->data[idx], &h->data[smallest]);
        idx = smallest;
    }
    return 0;
}

int find_k_smallest_pairs(const int *nums1, size_t len1,
                          const int *nums2, size_t len2,
                          size_t k, int (**result)[2],
                          size_t *result_count)
{
    MinHeap *heap;
    int (*pairs)[2];
    size_t max_pairs;
    size_t heap_init;
    size_t count = 0U;
    size_t idx;

    if (nums1 == NULL || nums2 == NULL || result == NULL ||
        result_count == NULL || len1 == 0U || len2 == 0U || k == 0U) {
        return -1;
    }

    *result = NULL;
    *result_count = 0U;

    if (len1 > (SIZE_MAX / len2)) {
        max_pairs = k;
    } else {
        max_pairs = (k < (len1 * len2)) ? k : (len1 * len2);
    }

    if (max_pairs > (SIZE_MAX / sizeof(*pairs))) {
        return -1;
    }

    pairs = malloc(max_pairs * sizeof(*pairs));
    if (pairs == NULL) {
        return -1;
    }

    heap_init = (k < len1) ? k : len1;
    heap = heap_create(heap_init);
    if (heap == NULL) {
        free(pairs);
        return -1;
    }

    for (idx = 0U; idx < heap_init; idx++) {
        HeapNode node;
        node.sum = (long long)nums1[idx] + (long long)nums2[0];
        node.i = idx;
        node.j = 0U;
        if (heap_push(heap, node) != 0) {
            heap_destroy(heap);
            free(pairs);
            return -1;
        }
    }

    while (count < max_pairs) {
        HeapNode top;

        if (heap_pop(heap, &top) != 0) {
            break;
        }
        pairs[count][0] = nums1[top.i];
        pairs[count][1] = nums2[top.j];
        count++;

        if ((top.j + 1U) < len2) {
            HeapNode next;
            next.sum = (long long)nums1[top.i] + (long long)nums2[top.j + 1U];
            next.i = top.i;
            next.j = top.j + 1U;
            if (heap_push(heap, next) != 0) {
                heap_destroy(heap);
                free(pairs);
                return -1;
            }
        }
    }

    heap_destroy(heap);
    *result = pairs;
    *result_count = count;
    return 0;
}

int main(void)
{
    int nums1[] = {1, 7, 11};
    int nums2[] = {2, 4, 6};
    size_t len1 = sizeof(nums1) / sizeof(nums1[0]);
    size_t len2 = sizeof(nums2) / sizeof(nums2[0]);
    size_t k = 5U;
    int (*result)[2] = NULL;
    size_t result_count = 0U;
    size_t idx;

    if (find_k_smallest_pairs(nums1, len1, nums2, len2, k,
                              &result, &result_count) != 0) {
        if (fprintf(stderr, "Failed to compute k smallest pairs\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    for (idx = 0U; idx < result_count; idx++) {
        if (printf("(%d, %d)\n", result[idx][0], result[idx][1]) < 0) {
            free(result);
            return EXIT_FAILURE;
        }
    }

    free(result);
    return EXIT_SUCCESS;
}