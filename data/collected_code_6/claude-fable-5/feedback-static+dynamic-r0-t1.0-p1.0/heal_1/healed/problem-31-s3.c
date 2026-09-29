#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int value;
    int count;
} Entry;

static int cmp_int(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}

static void heap_swap(Entry *a, Entry *b)
{
    Entry tmp = *a;
    *a = *b;
    *b = tmp;
}

static void heap_sift_up(Entry *heap, size_t i)
{
    while (i > 0U) {
        size_t parent = (i - 1U) / 2U;
        if (heap[parent].count <= heap[i].count) {
            break;
        }
        heap_swap(&heap[parent], &heap[i]);
        i = parent;
    }
}

static void heap_sift_down(Entry *heap, size_t size, size_t i)
{
    for (;;) {
        size_t smallest = i;
        size_t left = (2U * i) + 1U;
        size_t right = (2U * i) + 2U;
        if (left < size && heap[left].count < heap[smallest].count) {
            smallest = left;
        }
        if (right < size && heap[right].count < heap[smallest].count) {
            smallest = right;
        }
        if (smallest == i) {
            break;
        }
        heap_swap(&heap[i], &heap[smallest]);
        i = smallest;
    }
}

int *top_k_frequent(const int *const *lists, const size_t *sizes,
                    size_t num_lists, size_t k, size_t *result_count)
{
    size_t total = 0U;
    size_t i;
    size_t j;
    size_t pos;
    size_t distinct;
    size_t limit;
    size_t heap_size;
    size_t s;
    int *all;
    int *result;
    Entry *entries;
    Entry *heap;

    if (result_count == NULL) {
        return NULL;
    }
    *result_count = 0U;
    if (lists == NULL || sizes == NULL || num_lists == 0U || k == 0U) {
        return NULL;
    }

    for (i = 0U; i < num_lists; i++) {
        if (lists[i] == NULL) {
            return NULL;
        }
        if (sizes[i] > SIZE_MAX - total) {
            return NULL;
        }
        total += sizes[i];
    }
    if (total == 0U || total > SIZE_MAX / sizeof(int)) {
        return NULL;
    }

    all = malloc(total * sizeof(int));
    if (all == NULL) {
        return NULL;
    }

    pos = 0U;
    for (i = 0U; i < num_lists; i++) {
        for (j = 0U; j < sizes[i]; j++) {
            all[pos] = lists[i][j];
            pos++;
        }
    }

    qsort(all, total, sizeof(int), cmp_int);

    if (total > SIZE_MAX / sizeof(Entry)) {
        free(all);
        return NULL;
    }
    entries = malloc(total * sizeof(Entry));
    if (entries == NULL) {
        free(all);
        return NULL;
    }

    distinct = 0U;
    i = 0U;
    while (i < total) {
        int current = all[i];
        int count = 0;
        while (i < total && all[i] == current) {
            count++;
            i++;
        }
        entries[distinct].value = current;
        entries[distinct].count = count;
        distinct++;
    }
    free(all);

    limit = (k < distinct) ? k : distinct;
    heap = malloc(limit * sizeof(Entry));
    if (heap == NULL) {
        free(entries);
        return NULL;
    }

    heap_size = 0U;
    for (i = 0U; i < distinct; i++) {
        if (heap_size < limit) {
            heap[heap_size] = entries[i];
            heap_sift_up(heap, heap_size);
            heap_size++;
        } else if (entries[i].count > heap[0].count) {
            heap[0] = entries[i];
            heap_sift_down(heap, heap_size, 0U);
        }
    }
    free(entries);

    result = malloc(heap_size * sizeof(int));
    if (result == NULL) {
        free(heap);
        return NULL;
    }

    for (s = heap_size; s > 0U; s--) {
        result[s - 1U] = heap[0].value;
        heap[0] = heap[s - 1U];
        heap_sift_down(heap, s - 1U, 0U);
    }
    free(heap);

    *result_count = heap_size;
    return result;
}

int main(void)
{
    static const int list1[] = {1, 2, 6, 8};
    static const int list2[] = {2, 3, 6, 7};
    static const int list3[] = {1, 2, 4, 6, 9};
    const int *lists[] = {list1, list2, list3};
    static const size_t sizes[] = {
        sizeof(list1) / sizeof(list1[0]),
        sizeof(list2) / sizeof(list2[0]),
        sizeof(list3) / sizeof(list3[0])
    };
    size_t num_lists = sizeof(lists) / sizeof(lists[0]);
    size_t k = 3U;
    size_t result_count = 0U;
    size_t i;
    int *result;

    result = top_k_frequent(lists, sizes, num_lists, k, &result_count);
    if (result == NULL) {
        fprintf(stderr, "Failed to compute top k frequent integers\n");
        return EXIT_FAILURE;
    }

    printf("Top %zu frequent integers:", result_count);
    for (i = 0U; i < result_count; i++) {
        printf(" %d", result[i]);
    }
    printf("\n");

    free(result);
    return EXIT_SUCCESS;
}