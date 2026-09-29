#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    long sum;
    int idx1;
    int idx2;
} HeapNode;

typedef struct {
    HeapNode *nodes;
    size_t size;
    size_t capacity;
} MinHeap;

static MinHeap *heap_create(size_t capacity)
{
    MinHeap *heap;

    if (capacity == 0 || capacity > (SIZE_MAX / sizeof(HeapNode))) {
        return NULL;
    }

    heap = malloc(sizeof(MinHeap));
    if (heap == NULL) {
        return NULL;
    }

    heap->nodes = malloc(capacity * sizeof(HeapNode));
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

static int heap_push(MinHeap *heap, HeapNode node)
{
    size_t i;
    size_t parent;

    if (heap == NULL || heap->size >= heap->capacity) {
        return -1;
    }

    i = heap->size;
    heap->nodes[i] = node;
    heap->size++;

    while (i > 0) {
        parent = (i - 1) / 2;
        if (heap->nodes[parent].sum <= heap->nodes[i].sum) {
            break;
        }
        HeapNode tmp = heap->nodes[parent];
        heap->nodes[parent] = heap->nodes[i];
        heap->nodes[i] = tmp;
        i = parent;
    }

    return 0;
}

static int heap_pop(MinHeap *heap, HeapNode *out)
{
    size_t i;
    size_t left;
    size_t right;
    size_t smallest;

    if (heap == NULL || out == NULL || heap->size == 0) {
        return -1;
    }

    *out = heap->nodes[0];
    heap->size--;
    heap->nodes[0] = heap->nodes[heap->size];

    i = 0;
    for (;;) {
        left = 2 * i + 1;
        right = 2 * i + 2;
        smallest = i;

        if (left < heap->size &&
            heap->nodes[left].sum < heap->nodes[smallest].sum) {
            smallest = left;
        }
        if (right < heap->size &&
            heap->nodes[right].sum < heap->nodes[smallest].sum) {
            smallest = right;
        }
        if (smallest == i) {
            break;
        }

        HeapNode tmp = heap->nodes[i];
        heap->nodes[i] = heap->nodes[smallest];
        heap->nodes[smallest] = tmp;
        i = smallest;
    }

    return 0;
}

static int find_k_pairs(const int *nums1, size_t len1,
                        const int *nums2, size_t len2,
                        size_t k, int (*result)[2], size_t *result_count)
{
    MinHeap *heap;
    HeapNode node;
    size_t i;
    size_t count;
    size_t initial;

    if (nums1 == NULL || nums2 == NULL || result == NULL ||
        result_count == NULL || len1 == 0 || len2 == 0 || k == 0) {
        return -1;
    }

    if (k > len1 * len2) {
        k = len1 * len2;
    }

    initial = (len1 < k) ? len1 : k;

    heap = heap_create(initial + k);
    if (heap == NULL) {
        return -1;
    }

    for (i = 0; i < initial; i++) {
        node.sum = (long)nums1[i] + (long)nums2[0];
        node.idx1 = (int)i;
        node.idx2 = 0;
        if (heap_push(heap, node) != 0) {
            heap_destroy(heap);
            return -1;
        }
    }

    count = 0;
    while (count < k && heap->size > 0) {
        if (heap_pop(heap, &node) != 0) {
            heap_destroy(heap);
            return -1;
        }

        result[count][0] = nums1[node.idx1];
        result[count][1] = nums2[node.idx2];
        count++;

        if ((size_t)node.idx2 + 1 < len2) {
            HeapNode next;
            next.sum = (long)nums1[node.idx1] +
                       (long)nums2[node.idx2 + 1];
            next.idx1 = node.idx1;
            next.idx2 = node.idx2 + 1;
            if (heap_push(heap, next) != 0) {
                heap_destroy(heap);
                return -1;
            }
        }
    }

    *result_count = count;
    heap_destroy(heap);
    return 0;
}

int main(void)
{
    int nums1[] = {1, 7, 11};
    int nums2[] = {2, 4, 6};
    size_t len1 = sizeof(nums1) / sizeof(nums1[0]);
    size_t len2 = sizeof(nums2) / sizeof(nums2[0]);
    size_t k = 3;
    size_t count = 0;
    size_t i;
    int (*result)[2];

    result = malloc(k * sizeof(*result));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (find_k_pairs(nums1, len1, nums2, len2, k, result, &count) != 0) {
        fprintf(stderr, "Failed to find k pairs\n");
        free(result);
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        printf("(%d, %d)\n", result[i][0], result[i][1]);
    }

    free(result);
    return EXIT_SUCCESS;
}