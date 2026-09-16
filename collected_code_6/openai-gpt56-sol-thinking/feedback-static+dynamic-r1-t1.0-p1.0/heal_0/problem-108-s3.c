#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const int *values;
    size_t length;
} SortedInput;

typedef struct {
    int value;
    size_t input_index;
    size_t element_index;
} HeapNode;

typedef struct {
    const SortedInput *inputs;
    size_t input_count;
    HeapNode *heap;
    size_t heap_size;
} MergeIterator;

typedef enum {
    MERGE_STATUS_OK,
    MERGE_STATUS_END,
    MERGE_STATUS_INVALID_ARGUMENT,
    MERGE_STATUS_UNSORTED_INPUT,
    MERGE_STATUS_OUT_OF_MEMORY
} MergeStatus;

static bool heap_node_less(const HeapNode *left, const HeapNode *right)
{
    if (left->value != right->value) {
        return left->value < right->value;
    }

    if (left->input_index != right->input_index) {
        return left->input_index < right->input_index;
    }

    return left->element_index < right->element_index;
}

static void heap_swap(HeapNode *left, HeapNode *right)
{
    HeapNode temporary = *left;
    *left = *right;
    *right = temporary;
}

static void heap_push(MergeIterator *iterator, HeapNode node)
{
    size_t index = iterator->heap_size++;

    iterator->heap[index] = node;

    while (index > 0) {
        size_t parent = (index - 1U) / 2U;

        if (!heap_node_less(&iterator->heap[index], &iterator->heap[parent])) {
            break;
        }

        heap_swap(&iterator->heap[index], &iterator->heap[parent]);
        index = parent;
    }
}

static void heap_sift_down(MergeIterator *iterator, size_t index)
{
    for (;;) {
        size_t smallest = index;
        size_t left;
        size_t right;

        if (index > (SIZE_MAX - 1U) / 2U) {
            break;
        }

        left = index * 2U + 1U;
        right = left + 1U;

        if (left < iterator->heap_size &&
            heap_node_less(&iterator->heap[left], &iterator->heap[smallest])) {
            smallest = left;
        }

        if (right < iterator->heap_size &&
            heap_node_less(&iterator->heap[right], &iterator->heap[smallest])) {
            smallest = right;
        }

        if (smallest == index) {
            break;
        }

        heap_swap(&iterator->heap[index], &iterator->heap[smallest]);
        index = smallest;
    }
}

static void merge_iterator_destroy(MergeIterator *iterator)
{
    if (iterator == NULL) {
        return;
    }

    free(iterator->heap);
    iterator->inputs = NULL;
    iterator->input_count = 0;
    iterator->heap = NULL;
    iterator->heap_size = 0;
}

static MergeStatus merge_iterator_init(
    MergeIterator *iterator,
    const SortedInput *inputs,
    size_t input_count)
{
    size_t i;

    if (iterator == NULL || (inputs == NULL && input_count != 0U)) {
        return MERGE_STATUS_INVALID_ARGUMENT;
    }

    iterator->inputs = NULL;
    iterator->input_count = 0;
    iterator->heap = NULL;
    iterator->heap_size = 0;

    for (i = 0; i < input_count; ++i) {
        size_t j;

        if (inputs[i].length != 0U && inputs[i].values == NULL) {
            return MERGE_STATUS_INVALID_ARGUMENT;
        }

        for (j = 1; j < inputs[i].length; ++j) {
            if (inputs[i].values[j] < inputs[i].values[j - 1U]) {
                return MERGE_STATUS_UNSORTED_INPUT;
            }
        }
    }

    if (input_count > SIZE_MAX / sizeof(*iterator->heap)) {
        return MERGE_STATUS_OUT_OF_MEMORY;
    }

    if (input_count != 0U) {
        iterator->heap = malloc(input_count * sizeof(*iterator->heap));
        if (iterator->heap == NULL) {
            return MERGE_STATUS_OUT_OF_MEMORY;
        }
    }

    iterator->inputs = inputs;
    iterator->input_count = input_count;

    for (i = 0; i < input_count; ++i) {
        if (inputs[i].length != 0U) {
            HeapNode node;

            node.value = inputs[i].values[0];
            node.input_index = i;
            node.element_index = 0;
            heap_push(iterator, node);
        }
    }

    return MERGE_STATUS_OK;
}

static MergeStatus merge_iterator_next(MergeIterator *iterator, int *value)
{
    HeapNode root;
    const SortedInput *input;
    size_t next_index;

    if (iterator == NULL || value == NULL) {
        return MERGE_STATUS_INVALID_ARGUMENT;
    }

    if (iterator->heap_size == 0U) {
        return MERGE_STATUS_END;
    }

    root = iterator->heap[0];
    *value = root.value;
    input = &iterator->inputs[root.input_index];
    next_index = root.element_index + 1U;

    if (next_index < input->length) {
        iterator->heap[0].value = input->values[next_index];
        iterator->heap[0].input_index = root.input_index;
        iterator->heap[0].element_index = next_index;
    } else {
        --iterator->heap_size;

        if (iterator->heap_size != 0U) {
            iterator->heap[0] = iterator->heap[iterator->heap_size];
        }
    }

    if (iterator->heap_size != 0U) {
        heap_sift_down(iterator, 0);
    }

    return MERGE_STATUS_OK;
}

int main(void)
{
    static const int values1[] = {1, 4, 7, 10};
    static const int values2[] = {2, 5, 8, 11};
    static const int values3[] = {0, 3, 6, 9, 12};
    static const int values4[] = {2, 2, 13};
    static const SortedInput inputs[] = {
        {values1, sizeof(values1) / sizeof(values1[0])},
        {values2, sizeof(values2) / sizeof(values2[0])},
        {values3, sizeof(values3) / sizeof(values3[0])},
        {values4, sizeof(values4) / sizeof(values4[0])}
    };

    MergeIterator iterator;
    MergeStatus status;
    bool first = true;
    int value;

    status = merge_iterator_init(
        &iterator,
        inputs,
        sizeof(inputs) / sizeof(inputs[0]));

    if (status != MERGE_STATUS_OK) {
        return EXIT_FAILURE;
    }

    for (;;) {
        status = merge_iterator_next(&iterator, &value);

        if (status == MERGE_STATUS_END) {
            break;
        }

        if (status != MERGE_STATUS_OK) {
            merge_iterator_destroy(&iterator);
            return EXIT_FAILURE;
        }

        if (!first && putchar(' ') == EOF) {
            merge_iterator_destroy(&iterator);
            return EXIT_FAILURE;
        }

        if (printf("%d", value) < 0) {
            merge_iterator_destroy(&iterator);
            return EXIT_FAILURE;
        }

        first = false;
    }

    if (putchar('\n') == EOF) {
        merge_iterator_destroy(&iterator);
        return EXIT_FAILURE;
    }

    merge_iterator_destroy(&iterator);
    return EXIT_SUCCESS;
}