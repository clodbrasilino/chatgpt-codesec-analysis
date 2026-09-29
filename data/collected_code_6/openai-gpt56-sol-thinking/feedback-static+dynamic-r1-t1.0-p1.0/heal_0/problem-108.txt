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
    SortedInput *inputs;
    size_t input_count;
    HeapNode *heap;
    size_t heap_size;
} MergeIterator;

typedef enum {
    MERGE_RESULT_ERROR = -1,
    MERGE_RESULT_END = 0,
    MERGE_RESULT_VALUE = 1
} MergeResult;

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

static void heap_sift_up(HeapNode *heap, size_t index)
{
    while (index > 0) {
        size_t parent = (index - 1U) / 2U;

        if (!heap_node_less(&heap[index], &heap[parent])) {
            break;
        }

        heap_swap(&heap[index], &heap[parent]);
        index = parent;
    }
}

static void heap_sift_down(HeapNode *heap, size_t heap_size, size_t index)
{
    for (;;) {
        size_t left;
        size_t right;
        size_t smallest;

        if (index > (SIZE_MAX - 1U) / 2U) {
            break;
        }

        left = index * 2U + 1U;
        if (left >= heap_size) {
            break;
        }

        right = left + 1U;
        smallest = left;

        if (right < heap_size && heap_node_less(&heap[right], &heap[left])) {
            smallest = right;
        }

        if (!heap_node_less(&heap[smallest], &heap[index])) {
            break;
        }

        heap_swap(&heap[index], &heap[smallest]);
        index = smallest;
    }
}

static bool sorted_input_is_valid(const SortedInput *input)
{
    size_t index;

    if (input == NULL) {
        return false;
    }

    if (input->length > 0U && input->values == NULL) {
        return false;
    }

    for (index = 1U; index < input->length; ++index) {
        if (input->values[index] < input->values[index - 1U]) {
            return false;
        }
    }

    return true;
}

static void merge_iterator_destroy(MergeIterator *iterator)
{
    if (iterator == NULL) {
        return;
    }

    free(iterator->heap);
    free(iterator->inputs);
    free(iterator);
}

static MergeIterator *merge_iterator_create(const SortedInput *inputs,
                                            size_t input_count)
{
    MergeIterator *iterator;
    size_t index;

    if (input_count > 0U && inputs == NULL) {
        return NULL;
    }

    if (input_count > SIZE_MAX / sizeof(*inputs) ||
        input_count > SIZE_MAX / sizeof(HeapNode)) {
        return NULL;
    }

    for (index = 0U; index < input_count; ++index) {
        if (!sorted_input_is_valid(&inputs[index])) {
            return NULL;
        }
    }

    iterator = calloc(1U, sizeof(*iterator));
    if (iterator == NULL) {
        return NULL;
    }

    iterator->input_count = input_count;

    if (input_count == 0U) {
        return iterator;
    }

    iterator->inputs = malloc(input_count * sizeof(*iterator->inputs));
    if (iterator->inputs == NULL) {
        merge_iterator_destroy(iterator);
        return NULL;
    }

    iterator->heap = malloc(input_count * sizeof(*iterator->heap));
    if (iterator->heap == NULL) {
        merge_iterator_destroy(iterator);
        return NULL;
    }

    for (index = 0U; index < input_count; ++index) {
        iterator->inputs[index] = inputs[index];

        if (inputs[index].length > 0U) {
            size_t heap_index = iterator->heap_size++;

            iterator->heap[heap_index].value = inputs[index].values[0];
            iterator->heap[heap_index].input_index = index;
            iterator->heap[heap_index].element_index = 0U;
            heap_sift_up(iterator->heap, heap_index);
        }
    }

    return iterator;
}

static MergeResult merge_iterator_next(MergeIterator *iterator, int *value)
{
    HeapNode root;
    const SortedInput *input;
    size_t next_index;

    if (iterator == NULL || value == NULL) {
        return MERGE_RESULT_ERROR;
    }

    if (iterator->heap_size == 0U) {
        return MERGE_RESULT_END;
    }

    root = iterator->heap[0];
    *value = root.value;
    input = &iterator->inputs[root.input_index];
    next_index = root.element_index + 1U;

    if (next_index < input->length) {
        iterator->heap[0].value = input->values[next_index];
        iterator->heap[0].element_index = next_index;
    } else {
        --iterator->heap_size;

        if (iterator->heap_size > 0U) {
            iterator->heap[0] = iterator->heap[iterator->heap_size];
        }
    }

    if (iterator->heap_size > 0U) {
        heap_sift_down(iterator->heap, iterator->heap_size, 0U);
    }

    return MERGE_RESULT_VALUE;
}

int main(void)
{
    static const int first[] = {1, 4, 7, 12};
    static const int second[] = {2, 2, 8, 15};
    static const int third[] = {-3, 5, 9, 10, 20};
    static const int fourth[] = {0, 6, 11};
    const SortedInput inputs[] = {
        {first, sizeof(first) / sizeof(first[0])},
        {second, sizeof(second) / sizeof(second[0])},
        {third, sizeof(third) / sizeof(third[0])},
        {fourth, sizeof(fourth) / sizeof(fourth[0])}
    };
    MergeIterator *iterator;
    MergeResult result;
    bool first_output = true;
    int value;

    iterator = merge_iterator_create(inputs, sizeof(inputs) / sizeof(inputs[0]));
    if (iterator == NULL) {
        fputs("Failed to create merge iterator\n", stderr);
        return EXIT_FAILURE;
    }

    while ((result = merge_iterator_next(iterator, &value)) ==
           MERGE_RESULT_VALUE) {
        if (!first_output && putchar(' ') == EOF) {
            merge_iterator_destroy(iterator);
            return EXIT_FAILURE;
        }

        if (printf("%d", value) < 0) {
            merge_iterator_destroy(iterator);
            return EXIT_FAILURE;
        }

        first_output = false;
    }

    if (result == MERGE_RESULT_ERROR || putchar('\n') == EOF) {
        merge_iterator_destroy(iterator);
        return EXIT_FAILURE;
    }

    merge_iterator_destroy(iterator);
    return EXIT_SUCCESS;
}