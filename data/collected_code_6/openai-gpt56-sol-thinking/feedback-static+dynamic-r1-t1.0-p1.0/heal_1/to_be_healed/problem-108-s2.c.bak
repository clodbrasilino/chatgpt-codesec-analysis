#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const int *data;
    size_t length;
} SortedInput;

typedef enum {
    MERGE_STATUS_OK,
    MERGE_STATUS_END,
    MERGE_STATUS_INVALID_ARGUMENT,
    MERGE_STATUS_UNSORTED_INPUT,
    MERGE_STATUS_OUT_OF_MEMORY
} MergeStatus;

typedef struct {
    int *data;
    size_t length;
} OwnedInput;

typedef struct {
    int value;
    size_t input_index;
    size_t element_index;
} HeapNode;

typedef struct {
    OwnedInput *inputs;
    size_t input_count;
    HeapNode *heap;
    size_t heap_size;
    size_t heap_capacity;
} MergeIterator;

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

static bool heap_push(MergeIterator *iterator, HeapNode node)
{
    size_t index;

    if (iterator == NULL || iterator->heap_size >= iterator->heap_capacity) {
        return false;
    }

    index = iterator->heap_size;
    iterator->heap[index] = node;
    iterator->heap_size++;

    while (index > 0U) {
        size_t parent = (index - 1U) / 2U;

        if (!heap_node_less(&iterator->heap[index], &iterator->heap[parent])) {
            break;
        }

        heap_swap(&iterator->heap[index], &iterator->heap[parent]);
        index = parent;
    }

    return true;
}

static void heap_sift_down(MergeIterator *iterator, size_t index)
{
    for (;;) {
        size_t smallest = index;
        size_t left;
        size_t right;

        if (index > (SIZE_MAX - 1U) / 2U) {
            return;
        }

        left = index * 2U + 1U;
        right = left + 1U;

        if (left < iterator->heap_size &&
            heap_node_less(&iterator->heap[left],
                           &iterator->heap[smallest])) {
            smallest = left;
        }

        if (right < iterator->heap_size &&
            heap_node_less(&iterator->heap[right],
                           &iterator->heap[smallest])) {
            smallest = right;
        }

        if (smallest == index) {
            return;
        }

        heap_swap(&iterator->heap[index], &iterator->heap[smallest]);
        index = smallest;
    }
}

void merge_iterator_destroy(MergeIterator *iterator)
{
    /* Possible weaknesses found:
     *  The scope of the variable 'index' can be reduced. [variableScope]
     */
    size_t index;

    if (iterator == NULL) {
        return;
    }

    if (iterator->inputs != NULL) {
        for (index = 0U; index < iterator->input_count; ++index) {
            free(iterator->inputs[index].data);
            iterator->inputs[index].data = NULL;
            iterator->inputs[index].length = 0U;
        }
    }

    free(iterator->inputs);
    free(iterator->heap);

    iterator->inputs = NULL;
    iterator->heap = NULL;
    iterator->input_count = 0U;
    iterator->heap_size = 0U;
    iterator->heap_capacity = 0U;

    free(iterator);
}

MergeStatus merge_iterator_create(const SortedInput *inputs,
                                  size_t input_count,
                                  MergeIterator **result)
{
    MergeIterator *iterator;
    size_t input_index;

    if (result == NULL) {
        return MERGE_STATUS_INVALID_ARGUMENT;
    }

    *result = NULL;

    if (input_count > 0U && inputs == NULL) {
        return MERGE_STATUS_INVALID_ARGUMENT;
    }

    if (input_count > SIZE_MAX / sizeof(OwnedInput) ||
        input_count > SIZE_MAX / sizeof(HeapNode)) {
        return MERGE_STATUS_OUT_OF_MEMORY;
    }

    for (input_index = 0U; input_index < input_count; ++input_index) {
        size_t element_index;

        if (inputs[input_index].length > 0U &&
            inputs[input_index].data == NULL) {
            return MERGE_STATUS_INVALID_ARGUMENT;
        }

        if (inputs[input_index].length > SIZE_MAX / sizeof(int)) {
            return MERGE_STATUS_OUT_OF_MEMORY;
        }

        for (element_index = 1U;
             element_index < inputs[input_index].length;
             ++element_index) {
            if (inputs[input_index].data[element_index] <
                inputs[input_index].data[element_index - 1U]) {
                return MERGE_STATUS_UNSORTED_INPUT;
            }
        }
    }

    iterator = calloc(1U, sizeof(*iterator));
    if (iterator == NULL) {
        return MERGE_STATUS_OUT_OF_MEMORY;
    }

    iterator->input_count = input_count;
    iterator->heap_capacity = input_count;

    if (input_count > 0U) {
        iterator->inputs = calloc(input_count, sizeof(*iterator->inputs));
        iterator->heap = malloc(input_count * sizeof(*iterator->heap));

        if (iterator->inputs == NULL || iterator->heap == NULL) {
            merge_iterator_destroy(iterator);
            return MERGE_STATUS_OUT_OF_MEMORY;
        }
    }

    for (input_index = 0U; input_index < input_count; ++input_index) {
        size_t length = inputs[input_index].length;

        iterator->inputs[input_index].length = length;

        if (length > 0U) {
            HeapNode node;

            iterator->inputs[input_index].data =
                malloc(length * sizeof(*iterator->inputs[input_index].data));

            if (iterator->inputs[input_index].data == NULL) {
                merge_iterator_destroy(iterator);
                return MERGE_STATUS_OUT_OF_MEMORY;
            }

            memcpy(iterator->inputs[input_index].data,
                   inputs[input_index].data,
                   length * sizeof(*iterator->inputs[input_index].data));

            node.value = iterator->inputs[input_index].data[0];
            node.input_index = input_index;
            node.element_index = 0U;

            if (!heap_push(iterator, node)) {
                merge_iterator_destroy(iterator);
                return MERGE_STATUS_INVALID_ARGUMENT;
            }
        }
    }

    *result = iterator;
    return MERGE_STATUS_OK;
}

MergeStatus merge_iterator_next(MergeIterator *iterator, int *value)
{
    HeapNode root;
    OwnedInput *input;
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
        iterator->heap[0].element_index = next_index;
        iterator->heap[0].value = input->data[next_index];
    } else {
        iterator->heap_size--;

        if (iterator->heap_size > 0U) {
            iterator->heap[0] = iterator->heap[iterator->heap_size];
        }
    }

    if (iterator->heap_size > 0U) {
        heap_sift_down(iterator, 0U);
    }

    return MERGE_STATUS_OK;
}

int main(void)
{
    const int first[] = {1, 4, 7, 10};
    const int second[] = {2, 2, 5, 8, 11};
    const int third[] = {0, 3, 6, 9, 12};
    const SortedInput inputs[] = {
        {first, sizeof(first) / sizeof(first[0])},
        {second, sizeof(second) / sizeof(second[0])},
        {third, sizeof(third) / sizeof(third[0])}
    };
    MergeIterator *iterator = NULL;
    MergeStatus status;
    bool first_value = true;
    int value;

    status = merge_iterator_create(
        inputs,
        sizeof(inputs) / sizeof(inputs[0]),
        &iterator
    );

    if (status != MERGE_STATUS_OK) {
        fprintf(stderr, "Unable to create merge iterator: %d\n", (int)status);
        return EXIT_FAILURE;
    }

    while ((status = merge_iterator_next(iterator, &value)) ==
           MERGE_STATUS_OK) {
        if (!first_value && fputc(' ', stdout) == EOF) {
            merge_iterator_destroy(iterator);
            return EXIT_FAILURE;
        }

        if (printf("%d", value) < 0) {
            merge_iterator_destroy(iterator);
            return EXIT_FAILURE;
        }

        first_value = false;
    }

    if (status != MERGE_STATUS_END) {
        fprintf(stderr, "Merge iteration failed: %d\n", (int)status);
        merge_iterator_destroy(iterator);
        return EXIT_FAILURE;
    }

    if (fputc('\n', stdout) == EOF) {
        merge_iterator_destroy(iterator);
        return EXIT_FAILURE;
    }

    merge_iterator_destroy(iterator);
    return EXIT_SUCCESS;
}