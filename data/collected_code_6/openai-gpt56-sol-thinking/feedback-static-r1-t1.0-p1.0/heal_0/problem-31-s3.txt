#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int value;
    size_t frequency;
} FrequencyEntry;

typedef struct {
    int value;
    size_t list_index;
    size_t element_index;
} MergeNode;

typedef enum {
    TOP_K_OK = 0,
    TOP_K_INVALID_ARGUMENT,
    TOP_K_NO_MEMORY,
    TOP_K_OVERFLOW
} TopKStatus;

static void swap_merge_nodes(MergeNode *a, MergeNode *b)
{
    MergeNode temporary = *a;
    *a = *b;
    *b = temporary;
}

static int merge_node_precedes(const MergeNode *a, const MergeNode *b)
{
    if (a->value != b->value) {
        return a->value < b->value;
    }
    return a->list_index < b->list_index;
}

static int merge_heap_push(
    MergeNode *heap,
    size_t *heap_size,
    size_t capacity,
    MergeNode node)
{
    size_t index;

    if (heap == NULL || heap_size == NULL || *heap_size >= capacity) {
        return 0;
    }

    index = *heap_size;
    heap[index] = node;
    ++(*heap_size);

    while (index > 0) {
        size_t parent = (index - 1U) / 2U;

        if (!merge_node_precedes(&heap[index], &heap[parent])) {
            break;
        }

        swap_merge_nodes(&heap[index], &heap[parent]);
        index = parent;
    }

    return 1;
}

static int merge_heap_pop(
    MergeNode *heap,
    size_t *heap_size,
    MergeNode *result)
{
    size_t index = 0;

    if (heap == NULL || heap_size == NULL || result == NULL ||
        *heap_size == 0) {
        return 0;
    }

    *result = heap[0];
    --(*heap_size);

    if (*heap_size == 0) {
        return 1;
    }

    heap[0] = heap[*heap_size];

    for (;;) {
        size_t left = index * 2U + 1U;
        size_t right;
        size_t smallest;

        if (left >= *heap_size) {
            break;
        }

        right = left + 1U;
        smallest = left;

        if (right < *heap_size &&
            merge_node_precedes(&heap[right], &heap[left])) {
            smallest = right;
        }

        if (!merge_node_precedes(&heap[smallest], &heap[index])) {
            break;
        }

        swap_merge_nodes(&heap[index], &heap[smallest]);
        index = smallest;
    }

    return 1;
}

static void swap_frequency_entries(FrequencyEntry *a, FrequencyEntry *b)
{
    FrequencyEntry temporary = *a;
    *a = *b;
    *b = temporary;
}

static int frequency_entry_is_worse(
    const FrequencyEntry *a,
    const FrequencyEntry *b)
{
    if (a->frequency != b->frequency) {
        return a->frequency < b->frequency;
    }
    return a->value > b->value;
}

static int frequency_entry_is_better(
    const FrequencyEntry *a,
    const FrequencyEntry *b)
{
    if (a->frequency != b->frequency) {
        return a->frequency > b->frequency;
    }
    return a->value < b->value;
}

static int frequency_heap_push(
    FrequencyEntry *heap,
    size_t *heap_size,
    size_t capacity,
    FrequencyEntry entry)
{
    size_t index;

    if (heap == NULL || heap_size == NULL || *heap_size >= capacity) {
        return 0;
    }

    index = *heap_size;
    heap[index] = entry;
    ++(*heap_size);

    while (index > 0) {
        size_t parent = (index - 1U) / 2U;

        if (!frequency_entry_is_worse(&heap[index], &heap[parent])) {
            break;
        }

        swap_frequency_entries(&heap[index], &heap[parent]);
        index = parent;
    }

    return 1;
}

static void frequency_heap_sift_down(
    FrequencyEntry *heap,
    size_t heap_size,
    size_t index)
{
    for (;;) {
        size_t left = index * 2U + 1U;
        size_t right;
        size_t worst;

        if (left >= heap_size) {
            break;
        }

        right = left + 1U;
        worst = left;

        if (right < heap_size &&
            frequency_entry_is_worse(&heap[right], &heap[left])) {
            worst = right;
        }

        if (!frequency_entry_is_worse(&heap[worst], &heap[index])) {
            break;
        }

        swap_frequency_entries(&heap[index], &heap[worst]);
        index = worst;
    }
}

static int compare_frequency_entries(const void *left, const void *right)
{
    const FrequencyEntry *a = left;
    const FrequencyEntry *b = right;

    if (a->frequency > b->frequency) {
        return -1;
    }
    if (a->frequency < b->frequency) {
        return 1;
    }
    if (a->value < b->value) {
        return -1;
    }
    if (a->value > b->value) {
        return 1;
    }
    return 0;
}

TopKStatus top_k_frequent(
    const int *const *lists,
    const size_t *sizes,
    size_t list_count,
    size_t k,
    FrequencyEntry **out_entries,
    size_t *out_count)
{
    MergeNode *merge_heap = NULL;
    FrequencyEntry *frequency_heap = NULL;
    size_t merge_capacity = 0;
    size_t merge_size = 0;
    size_t frequency_capacity;
    size_t frequency_size = 0;
    size_t total_elements = 0;
    size_t i;
    TopKStatus status = TOP_K_OK;

    if (out_entries == NULL || out_count == NULL) {
        return TOP_K_INVALID_ARGUMENT;
    }

    *out_entries = NULL;
    *out_count = 0;

    if (list_count > 0 && (lists == NULL || sizes == NULL)) {
        return TOP_K_INVALID_ARGUMENT;
    }

    for (i = 0; i < list_count; ++i) {
        size_t j;

        if (sizes[i] > 0 && lists[i] == NULL) {
            return TOP_K_INVALID_ARGUMENT;
        }

        if (total_elements > SIZE_MAX - sizes[i]) {
            return TOP_K_OVERFLOW;
        }
        total_elements += sizes[i];

        if (sizes[i] > 0) {
            ++merge_capacity;
        }

        for (j = 1; j < sizes[i]; ++j) {
            if (lists[i][j - 1U] >= lists[i][j]) {
                return TOP_K_INVALID_ARGUMENT;
            }
        }
    }

    if (k == 0 || total_elements == 0) {
        return TOP_K_OK;
    }

    frequency_capacity = k < total_elements ? k : total_elements;

    if (merge_capacity > SIZE_MAX / sizeof(*merge_heap) ||
        frequency_capacity > SIZE_MAX / sizeof(*frequency_heap)) {
        return TOP_K_OVERFLOW;
    }

    merge_heap = malloc(merge_capacity * sizeof(*merge_heap));
    frequency_heap = malloc(frequency_capacity * sizeof(*frequency_heap));

    if (merge_heap == NULL || frequency_heap == NULL) {
        status = TOP_K_NO_MEMORY;
        goto cleanup;
    }

    for (i = 0; i < list_count; ++i) {
        MergeNode node;

        if (sizes[i] == 0) {
            continue;
        }

        node.value = lists[i][0];
        node.list_index = i;
        node.element_index = 0;

        if (!merge_heap_push(
                merge_heap, &merge_size, merge_capacity, node)) {
            status = TOP_K_INVALID_ARGUMENT;
            goto cleanup;
        }
    }

    while (merge_size > 0) {
        MergeNode node;
        FrequencyEntry candidate;
        int current_value;
        size_t frequency = 0;

        if (!merge_heap_pop(merge_heap, &merge_size, &node)) {
            status = TOP_K_INVALID_ARGUMENT;
            goto cleanup;
        }

        current_value = node.value;

        for (;;) {
            size_t next_index;

            if (frequency == SIZE_MAX) {
                status = TOP_K_OVERFLOW;
                goto cleanup;
            }
            ++frequency;

            next_index = node.element_index + 1U;

            if (next_index < sizes[node.list_index]) {
                MergeNode next_node;

                next_node.value = lists[node.list_index][next_index];
                next_node.list_index = node.list_index;
                next_node.element_index = next_index;

                if (!merge_heap_push(
                        merge_heap,
                        &merge_size,
                        merge_capacity,
                        next_node)) {
                    status = TOP_K_INVALID_ARGUMENT;
                    goto cleanup;
                }
            }

            if (merge_size == 0 ||
                merge_heap[0].value != current_value) {
                break;
            }

            if (!merge_heap_pop(merge_heap, &merge_size, &node)) {
                status = TOP_K_INVALID_ARGUMENT;
                goto cleanup;
            }
        }

        candidate.value = current_value;
        candidate.frequency = frequency;

        if (frequency_size < frequency_capacity) {
            if (!frequency_heap_push(
                    frequency_heap,
                    &frequency_size,
                    frequency_capacity,
                    candidate)) {
                status = TOP_K_INVALID_ARGUMENT;
                goto cleanup;
            }
        } else if (frequency_entry_is_better(
                       &candidate, &frequency_heap[0])) {
            frequency_heap[0] = candidate;
            frequency_heap_sift_down(
                frequency_heap, frequency_size, 0);
        }
    }

    qsort(
        frequency_heap,
        frequency_size,
        sizeof(*frequency_heap),
        compare_frequency_entries);

    free(merge_heap);
    *out_entries = frequency_heap;
    *out_count = frequency_size;
    return TOP_K_OK;

cleanup:
    free(merge_heap);
    free(frequency_heap);
    return status;
}

int main(void)
{
    const int list0[] = {1, 3, 5, 7};
    const int list1[] = {1, 2, 3, 7, 9};
    const int list2[] = {1, 3, 4, 7, 8};
    const int list3[] = {2, 3, 6, 7};
    const int *lists[] = {list0, list1, list2, list3};
    const size_t sizes[] = {
        sizeof(list0) / sizeof(list0[0]),
        sizeof(list1) / sizeof(list1[0]),
        sizeof(list2) / sizeof(list2[0]),
        sizeof(list3) / sizeof(list3[0])
    };
    FrequencyEntry *entries = NULL;
    size_t entry_count = 0;
    size_t i;
    TopKStatus status;

    status = top_k_frequent(
        lists,
        sizes,
        sizeof(lists) / sizeof(lists[0]),
        3,
        &entries,
        &entry_count);

    if (status != TOP_K_OK) {
        fprintf(stderr, "top_k_frequent failed with status %d\n", status);
        return EXIT_FAILURE;
    }

    for (i = 0; i < entry_count; ++i) {
        printf("%d %zu\n", entries[i].value, entries[i].frequency);
    }

    free(entries);
    return EXIT_SUCCESS;
}