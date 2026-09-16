#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t i;
    size_t j;
    long long sum;
} HeapNode;

typedef struct {
    HeapNode *nodes;
    size_t size;
    size_t capacity;
} MinHeap;

static MinHeap *heap_create(size_t capacity)
{
    MinHeap *h;
    if (capacity == 0) {
        capacity = 1;
    }
    h = malloc(sizeof(*h));
    if (h == NULL) {
        return NULL;
    }
    h->nodes = malloc(capacity * sizeof(*h->nodes));
    if (h->nodes == NULL) {
        free(h);
        return NULL;
    }
    h->size = 0;
    h->capacity = capacity;
    return h;
}

static void heap_destroy(MinHeap *h)
{
    if (h != NULL) {
        free(h->nodes);
        free(h);
    }
}

static void heap_swap(HeapNode *a, HeapNode *b)
{
    HeapNode t = *a;
    *a = *b;
    *b = t;
}

static int heap_push(MinHeap *h, HeapNode node)
{
    size_t idx;
    if (h->size >= h->capacity) {
        size_t newcap;
        HeapNode *tmp;
        if (h->capacity > ((size_t)-1) / (2u * sizeof(*tmp))) {
            return -1;
        }
        newcap = h->capacity * 2u;
        tmp = realloc(h->nodes, newcap * sizeof(*tmp));
        if (tmp == NULL) {
            return -1;
        }
        h->nodes = tmp;
        h->capacity = newcap;
    }
    idx = h->size;
    h->size++;
    h->nodes[idx] = node;
    while (idx > 0) {
        size_t parent = (idx - 1u) / 2u;
        if (h->nodes[parent].sum <= h->nodes[idx].sum) {
            break;
        }
        heap_swap(&h->nodes[parent], &h->nodes[idx]);
        idx = parent;
    }
    return 0;
}

static int heap_pop(MinHeap *h, HeapNode *out)
{
    size_t idx = 0;
    if (h->size == 0 || out == NULL) {
        return -1;
    }
    *out = h->nodes[0];
    h->size--;
    h->nodes[0] = h->nodes[h->size];
    for (;;) {
        size_t left = 2u * idx + 1u;
        size_t right = 2u * idx + 2u;
        size_t smallest = idx;
        if (left < h->size && h->nodes[left].sum < h->nodes[smallest].sum) {
            smallest = left;
        }
        if (right < h->size && h->nodes[right].sum < h->nodes[smallest].sum) {
            smallest = right;
        }
        if (smallest == idx) {
            break;
        }
        heap_swap(&h->nodes[idx], &h->nodes[smallest]);
        idx = smallest;
    }
    return 0;
}

static int (*find_k_smallest_pairs(const int *nums1, size_t n1,
                                   const int *nums2, size_t n2,
                                   size_t k, size_t *out_count))[2]
{
    MinHeap *heap;
    int (*result)[2];
    size_t total;
    size_t produced = 0;
    size_t i;

    if (out_count == NULL) {
        return NULL;
    }
    *out_count = 0;
    if (nums1 == NULL || nums2 == NULL || n1 == 0 || n2 == 0 || k == 0) {
        return NULL;
    }

    if (n1 > ((size_t)-1) / n2) {
        total = (size_t)-1;
    } else {
        total = n1 * n2;
    }
    if (k > total) {
        k = total;
    }
    if (k > ((size_t)-1) / sizeof(*result)) {
        return NULL;
    }

    result = malloc(k * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    heap = heap_create(n1 < k ? n1 : k);
    if (heap == NULL) {
        free(result);
        return NULL;
    }

    for (i = 0; i < n1 && i < k; i++) {
        HeapNode node;
        node.i = i;
        node.j = 0;
        node.sum = (long long)nums1[i] + (long long)nums2[0];
        if (heap_push(heap, node) != 0) {
            heap_destroy(heap);
            free(result);
            return NULL;
        }
    }

    while (produced < k) {
        HeapNode top;
        if (heap_pop(heap, &top) != 0) {
            break;
        }
        result[produced][0] = nums1[top.i];
        result[produced][1] = nums2[top.j];
        produced++;
        if (top.j + 1u < n2) {
            HeapNode next;
            next.i = top.i;
            next.j = top.j + 1u;
            next.sum = (long long)nums1[top.i] + (long long)nums2[next.j];
            if (heap_push(heap, next) != 0) {
                heap_destroy(heap);
                free(result);
                return NULL;
            }
        }
    }

    heap_destroy(heap);

    if (produced == 0) {
        free(result);
        return NULL;
    }

    *out_count = produced;
    return result;
}

int main(void)
{
    int nums1[] = {1, 7, 11};
    int nums2[] = {2, 4, 6};
    size_t n1 = sizeof(nums1) / sizeof(nums1[0]);
    size_t n2 = sizeof(nums2) / sizeof(nums2[0]);
    size_t k = 3;
    size_t count = 0;
    size_t idx;
    int (*pairs)[2];

    pairs = find_k_smallest_pairs(nums1, n1, nums2, n2, k, &count);
    if (pairs == NULL) {
        fprintf(stderr, "Failed to compute k smallest pairs\n");
        return EXIT_FAILURE;
    }

    for (idx = 0; idx < count; idx++) {
        if (printf("(%d, %d)\n", pairs[idx][0], pairs[idx][1]) < 0) {
            free(pairs);
            return EXIT_FAILURE;
        }
    }

    free(pairs);
    return EXIT_SUCCESS;
}