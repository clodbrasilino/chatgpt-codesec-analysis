#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    int value;
    int freq;
} Pair;

typedef struct {
    Pair *data;
    size_t size;
    size_t capacity;
} MinHeap;

static int heap_init(MinHeap *h, size_t capacity)
{
    if (h == NULL || capacity == 0) {
        return -1;
    }
    if (capacity > SIZE_MAX / sizeof(Pair)) {
        return -1;
    }
    h->data = malloc(capacity * sizeof(Pair));
    if (h->data == NULL) {
        return -1;
    }
    h->size = 0;
    h->capacity = capacity;
    return 0;
}

static void heap_destroy(MinHeap *h)
{
    if (h != NULL) {
        free(h->data);
        h->data = NULL;
        h->size = 0;
        h->capacity = 0;
    }
}

static void heap_sift_up(MinHeap *h, size_t idx)
{
    while (idx > 0) {
        size_t parent = (idx - 1) / 2;
        if (h->data[idx].freq < h->data[parent].freq) {
            Pair tmp = h->data[idx];
            h->data[idx] = h->data[parent];
            h->data[parent] = tmp;
            idx = parent;
        } else {
            break;
        }
    }
}

static void heap_sift_down(MinHeap *h, size_t idx)
{
    for (;;) {
        size_t left = 2 * idx + 1;
        size_t right = 2 * idx + 2;
        size_t smallest = idx;

        if (left < h->size && h->data[left].freq < h->data[smallest].freq) {
            smallest = left;
        }
        if (right < h->size && h->data[right].freq < h->data[smallest].freq) {
            smallest = right;
        }
        if (smallest == idx) {
            break;
        }
        {
            Pair tmp = h->data[idx];
            h->data[idx] = h->data[smallest];
            h->data[smallest] = tmp;
        }
        idx = smallest;
    }
}

static void heap_offer(MinHeap *h, Pair p)
{
    if (h == NULL || h->data == NULL) {
        return;
    }
    if (h->size < h->capacity) {
        h->data[h->size] = p;
        h->size++;
        heap_sift_up(h, h->size - 1);
    } else if (h->capacity > 0 && p.freq > h->data[0].freq) {
        h->data[0] = p;
        heap_sift_down(h, 0);
    }
}

static int heap_pop(MinHeap *h, Pair *out)
{
    if (h == NULL || out == NULL || h->size == 0) {
        return -1;
    }
    *out = h->data[0];
    h->size--;
    if (h->size > 0) {
        h->data[0] = h->data[h->size];
        heap_sift_down(h, 0);
    }
    return 0;
}

static int cmp_int(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;
    if (x < y) {
        return -1;
    }
    if (x > y) {
        return 1;
    }
    return 0;
}

static Pair *top_k_frequent(const int *const *lists, const size_t *sizes,
                            size_t nlists, size_t k, size_t *out_n)
{
    size_t total = 0;
    size_t i;
    size_t pos;
    int *all = NULL;
    MinHeap heap;
    Pair *result = NULL;
    size_t result_n;

    if (lists == NULL || sizes == NULL || out_n == NULL || k == 0) {
        return NULL;
    }
    *out_n = 0;

    for (i = 0; i < nlists; i++) {
        if (sizes[i] > 0 && lists[i] == NULL) {
            return NULL;
        }
        if (sizes[i] > SIZE_MAX - total) {
            return NULL;
        }
        total += sizes[i];
    }
    if (total == 0) {
        return NULL;
    }
    if (total > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    all = malloc(total * sizeof(int));
    if (all == NULL) {
        return NULL;
    }

    pos = 0;
    for (i = 0; i < nlists; i++) {
        if (sizes[i] > 0) {
            if (sizes[i] > total - pos) {
                free(all);
                return NULL;
            }
            memcpy(&all[pos], lists[i], sizes[i] * sizeof(int));
            pos += sizes[i];
        }
    }

    qsort(all, total, sizeof(int), cmp_int);

    if (heap_init(&heap, k) != 0) {
        free(all);
        return NULL;
    }

    i = 0;
    while (i < total) {
        size_t j = i;
        Pair p;
        while (j < total && all[j] == all[i]) {
            j++;
        }
        p.value = all[i];
        p.freq = (int)(j - i);
        heap_offer(&heap, p);
        i = j;
    }

    free(all);

    result_n = heap.size;
    if (result_n == 0) {
        heap_destroy(&heap);
        return NULL;
    }

    result = malloc(result_n * sizeof(Pair));
    if (result == NULL) {
        heap_destroy(&heap);
        return NULL;
    }

    for (i = result_n; i > 0; i--) {
        Pair p;
        if (heap_pop(&heap, &p) != 0) {
            free(result);
            heap_destroy(&heap);
            return NULL;
        }
        result[i - 1] = p;
    }

    heap_destroy(&heap);
    *out_n = result_n;
    return result;
}

int main(void)
{
    static const int list1[] = {1, 2, 3, 4, 5};
    static const int list2[] = {2, 3, 4, 5, 6};
    static const int list3[] = {3, 4, 5, 6, 7};
    static const int list4[] = {4, 5, 6, 7, 8};
    const int *lists[] = {list1, list2, list3, list4};
    const size_t sizes[] = {5, 5, 5, 5};
    size_t nlists = sizeof(lists) / sizeof(lists[0]);
    size_t k = 3;
    size_t out_n = 0;
    size_t i;
    Pair *result;

    result = top_k_frequent(lists, sizes, nlists, k, &out_n);
    if (result == NULL) {
        fprintf(stderr, "Failed to compute top k frequent integers\n");
        return EXIT_FAILURE;
    }

    printf("Top %zu most frequent integers:\n", out_n);
    for (i = 0; i < out_n; i++) {
        printf("value = %d, frequency = %d\n", result[i].value, result[i].freq);
    }

    free(result);
    return EXIT_SUCCESS;
}