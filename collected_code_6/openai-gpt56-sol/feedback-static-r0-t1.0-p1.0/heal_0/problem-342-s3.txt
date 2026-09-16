#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int value;
    size_t array_index;
    size_t element_index;
} HeapNode;

typedef struct {
    int start;
    int end;
} Range;

static void swap_nodes(HeapNode *a, HeapNode *b)
{
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

static int heap_push(HeapNode *heap, size_t *size, size_t capacity, HeapNode node)
{
    size_t index;

    if (heap == NULL || size == NULL || *size >= capacity) {
        return 0;
    }

    index = (*size)++;
    heap[index] = node;

    while (index > 0U) {
        size_t parent = (index - 1U) / 2U;

        if (heap[parent].value <= heap[index].value) {
            break;
        }

        swap_nodes(&heap[parent], &heap[index]);
        index = parent;
    }

    return 1;
}

static int heap_pop(HeapNode *heap, size_t *size, HeapNode *result)
{
    size_t index = 0U;

    if (heap == NULL || size == NULL || result == NULL || *size == 0U) {
        return 0;
    }

    *result = heap[0];
    --(*size);

    if (*size == 0U) {
        return 1;
    }

    heap[0] = heap[*size];

    for (;;) {
        size_t left = (index * 2U) + 1U;
        size_t right = left + 1U;
        size_t smallest = index;

        if (left < *size && heap[left].value < heap[smallest].value) {
            smallest = left;
        }

        if (right < *size && heap[right].value < heap[smallest].value) {
            smallest = right;
        }

        if (smallest == index) {
            break;
        }

        swap_nodes(&heap[index], &heap[smallest]);
        index = smallest;
    }

    return 1;
}

static uint64_t range_width(int start, int end)
{
    return (uint64_t)((int64_t)end - (int64_t)start);
}

static int find_smallest_range(const int *const arrays[],
                               const size_t lengths[],
                               size_t array_count,
                               Range *result)
{
    HeapNode *heap;
    size_t heap_size = 0U;
    int current_max;

    if (arrays == NULL || lengths == NULL || result == NULL ||
        array_count == 0U || array_count > SIZE_MAX / sizeof(*heap)) {
        return 0;
    }

    heap = malloc(array_count * sizeof(*heap));
    if (heap == NULL) {
        return 0;
    }

    current_max = 0;

    for (size_t i = 0U; i < array_count; ++i) {
        HeapNode node;

        if (arrays[i] == NULL || lengths[i] == 0U) {
            free(heap);
            return 0;
        }

        node.value = arrays[i][0];
        node.array_index = i;
        node.element_index = 0U;

        if (i == 0U || node.value > current_max) {
            current_max = node.value;
        }

        if (!heap_push(heap, &heap_size, array_count, node)) {
            free(heap);
            return 0;
        }
    }

    result->start = heap[0].value;
    result->end = current_max;

    while (heap_size == array_count) {
        HeapNode minimum;
        size_t next_index;

        if (!heap_pop(heap, &heap_size, &minimum)) {
            free(heap);
            return 0;
        }

        if (range_width(minimum.value, current_max) <
                range_width(result->start, result->end) ||
            (range_width(minimum.value, current_max) ==
                 range_width(result->start, result->end) &&
             minimum.value < result->start)) {
            result->start = minimum.value;
            result->end = current_max;
        }

        next_index = minimum.element_index + 1U;
        if (next_index >= lengths[minimum.array_index]) {
            break;
        }

        minimum.element_index = next_index;
        minimum.value = arrays[minimum.array_index][next_index];

        if (minimum.value > current_max) {
            current_max = minimum.value;
        }

        if (!heap_push(heap, &heap_size, array_count, minimum)) {
            free(heap);
            return 0;
        }
    }

    free(heap);
    return 1;
}

int main(void)
{
    static const int array1[] = {4, 10, 15, 24, 26};
    static const int array2[] = {0, 9, 12, 20};
    static const int array3[] = {5, 18, 22, 30};
    const int *arrays[] = {array1, array2, array3};
    const size_t lengths[] = {
        sizeof(array1) / sizeof(array1[0]),
        sizeof(array2) / sizeof(array2[0]),
        sizeof(array3) / sizeof(array3[0])
    };
    Range result;

    if (!find_smallest_range(arrays,
                             lengths,
                             sizeof(arrays) / sizeof(arrays[0]),
                             &result)) {
        fputs("Unable to find a range.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("[%d, %d]\n", result.start, result.end) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}