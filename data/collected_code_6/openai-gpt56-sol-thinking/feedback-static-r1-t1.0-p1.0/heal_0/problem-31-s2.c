#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

typedef struct {
    int value;
    size_t frequency;
} Frequency;

typedef struct {
    int value;
    size_t list_index;
    size_t element_index;
} MergeNode;

enum {
    TOP_K_SUCCESS = 0,
    TOP_K_INVALID_ARGUMENT = 1,
    TOP_K_ALLOCATION_FAILURE = 2,
    TOP_K_SIZE_OVERFLOW = 3
};

static void swap_merge_nodes(MergeNode *a, MergeNode *b)
{
    MergeNode temporary = *a;
    *a = *b;
    *b = temporary;
}

static void merge_heap_push(MergeNode *heap, size_t *heap_size, MergeNode node)
{
    size_t index = (*heap_size)++;

    heap[index] = node;

    while (index > 0) {
        size_t parent = (index - 1U) / 2U;

        if (heap[parent].value <= heap[index].value) {
            break;
        }

        swap_merge_nodes(&heap[parent], &heap[index]);
        index = parent;
    }
}

static MergeNode merge_heap_pop(MergeNode *heap, size_t *heap_size)
{
    MergeNode result = heap[0];
    size_t size = --(*heap_size);
    size_t index = 0;

    if (size == 0) {
        return result;
    }

    heap[0] = heap[size];

    for (;;) {
        size_t left = index * 2U + 1U;
        size_t right = left + 1U;
        size_t smallest = index;

        if (left < size && heap[left].value < heap[smallest].value) {
            smallest = left;
        }

        if (right < size && heap[right].value < heap[smallest].value) {
            smallest = right;
        }

        if (smallest == index) {
            break;
        }

        swap_merge_nodes(&heap[index], &heap[smallest]);
        index = smallest;
    }

    return result;
}

static int frequency_is_worse(Frequency a, Frequency b)
{
    return a.frequency < b.frequency ||
           (a.frequency == b.frequency && a.value > b.value);
}

static int frequency_is_better(Frequency a, Frequency b)
{
    return a.frequency > b.frequency ||
           (a.frequency == b.frequency && a.value < b.value);
}

static void swap_frequencies(Frequency *a, Frequency *b)
{
    Frequency temporary = *a;
    *a = *b;
    *b = temporary;
}

static void frequency_heap_push(Frequency *heap, size_t *heap_size,
                                Frequency item)
{
    size_t index = (*heap_size)++;

    heap[index] = item;

    while (index > 0) {
        size_t parent = (index - 1U) / 2U;

        if (!frequency_is_worse(heap[index], heap[parent])) {
            break;
        }

        swap_frequencies(&heap[index], &heap[parent]);
        index = parent;
    }
}

static void frequency_heap_sift_down(Frequency *heap, size_t heap_size)
{
    size_t index = 0;

    for (;;) {
        size_t left = index * 2U + 1U;
        size_t right = left + 1U;
        size_t worst = index;

        if (left < heap_size &&
            frequency_is_worse(heap[left], heap[worst])) {
            worst = left;
        }

        if (right < heap_size &&
            frequency_is_worse(heap[right], heap[worst])) {
            worst = right;
        }

        if (worst == index) {
            break;
        }

        swap_frequencies(&heap[index], &heap[worst]);
        index = worst;
    }
}

static int compare_frequencies(const void *left, const void *right)
{
    const Frequency *a = left;
    const Frequency *b = right;

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

int top_k_frequent(const int *const *lists, const size_t *lengths,
                   size_t list_count, size_t k, Frequency **results,
                   size_t *result_count)
{
    MergeNode *merge_heap = NULL;
    Frequency *frequency_heap = NULL;
    size_t merge_size = 0;
    size_t frequency_size = 0;
    size_t total_elements = 0;
    size_t effective_k;
    size_t i;

    if (results == NULL || result_count == NULL) {
        return TOP_K_INVALID_ARGUMENT;
    }

    *results = NULL;
    *result_count = 0;

    if (list_count > 0 && (lists == NULL || lengths == NULL)) {
        return TOP_K_INVALID_ARGUMENT;
    }

    for (i = 0; i < list_count; ++i) {
        size_t j;

        if (lengths[i] > 0 && lists[i] == NULL) {
            return TOP_K_INVALID_ARGUMENT;
        }

        for (j = 1; j < lengths[i]; ++j) {
            if (lists[i][j - 1U] >= lists[i][j]) {
                return TOP_K_INVALID_ARGUMENT;
            }
        }

        if (SIZE_MAX - total_elements < lengths[i]) {
            total_elements = SIZE_MAX;
        } else {
            total_elements += lengths[i];
        }
    }

    if (k == 0 || total_elements == 0) {
        return TOP_K_SUCCESS;
    }

    effective_k = k < total_elements ? k : total_elements;

    if (list_count > SIZE_MAX / sizeof(*merge_heap) ||
        effective_k > SIZE_MAX / sizeof(*frequency_heap)) {
        return TOP_K_SIZE_OVERFLOW;
    }

    merge_heap = malloc(list_count * sizeof(*merge_heap));
    if (merge_heap == NULL) {
        return TOP_K_ALLOCATION_FAILURE;
    }

    frequency_heap = malloc(effective_k * sizeof(*frequency_heap));
    if (frequency_heap == NULL) {
        free(merge_heap);
        return TOP_K_ALLOCATION_FAILURE;
    }

    for (i = 0; i < list_count; ++i) {
        if (lengths[i] > 0) {
            MergeNode node = { lists[i][0], i, 0 };
            merge_heap_push(merge_heap, &merge_size, node);
        }
    }

    while (merge_size > 0) {
        int current_value = merge_heap[0].value;
        size_t frequency = 0;
        Frequency item;

        while (merge_size > 0 && merge_heap[0].value == current_value) {
            MergeNode node = merge_heap_pop(merge_heap, &merge_size);

            ++frequency;
            ++node.element_index;

            if (node.element_index < lengths[node.list_index]) {
                node.value = lists[node.list_index][node.element_index];
                merge_heap_push(merge_heap, &merge_size, node);
            }
        }

        item.value = current_value;
        item.frequency = frequency;

        if (frequency_size < effective_k) {
            frequency_heap_push(frequency_heap, &frequency_size, item);
        } else if (frequency_is_better(item, frequency_heap[0])) {
            frequency_heap[0] = item;
            frequency_heap_sift_down(frequency_heap, frequency_size);
        }
    }

    free(merge_heap);

    qsort(frequency_heap, frequency_size, sizeof(*frequency_heap),
          compare_frequencies);

    *results = frequency_heap;
    *result_count = frequency_size;

    return TOP_K_SUCCESS;
}

int main(void)
{
    const int list1[] = { 1, 2, 6, 7 };
    const int list2[] = { 1, 3, 4, 7 };
    const int list3[] = { 1, 2, 4, 7 };
    const int list4[] = { 2, 4, 5, 7 };
    const int *lists[] = { list1, list2, list3, list4 };
    const size_t lengths[] = {
        sizeof(list1) / sizeof(list1[0]),
        sizeof(list2) / sizeof(list2[0]),
        sizeof(list3) / sizeof(list3[0]),
        sizeof(list4) / sizeof(list4[0])
    };
    Frequency *results = NULL;
    size_t result_count = 0;
    size_t i;
    int status;

    status = top_k_frequent(
        lists,
        lengths,
        sizeof(lists) / sizeof(lists[0]),
        3,
        &results,
        &result_count
    );

    if (status != TOP_K_SUCCESS) {
        if (fprintf(stderr, "Unable to find the top integers\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    for (i = 0; i < result_count; ++i) {
        if (printf("%d %zu\n", results[i].value,
                   results[i].frequency) < 0) {
            free(results);
            return EXIT_FAILURE;
        }
    }

    free(results);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}