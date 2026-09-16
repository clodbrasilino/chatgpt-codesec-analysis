#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <stddef.h>

typedef struct {
    int value;
    size_t array_index;
    size_t element_index;
} HeapNode;

typedef struct {
    HeapNode *nodes;
    size_t size;
    size_t capacity;
} MinHeap;

static bool heap_init(MinHeap *heap, size_t capacity)
{
    if (heap == NULL || capacity == 0 || capacity > SIZE_MAX / sizeof(*heap->nodes)) {
        return false;
    }

    heap->nodes = malloc(capacity * sizeof(*heap->nodes));
    if (heap->nodes == NULL) {
        return false;
    }

    heap->size = 0;
    heap->capacity = capacity;
    return true;
}

static void heap_destroy(MinHeap *heap)
{
    if (heap != NULL) {
        free(heap->nodes);
        heap->nodes = NULL;
        heap->size = 0;
        heap->capacity = 0;
    }
}

static bool heap_push(MinHeap *heap, HeapNode node)
{
    if (heap == NULL || heap->nodes == NULL || heap->size >= heap->capacity) {
        return false;
    }

    size_t index = heap->size++;
    heap->nodes[index] = node;

    while (index > 0) {
        size_t parent = (index - 1U) / 2U;

        if (heap->nodes[parent].value <= heap->nodes[index].value) {
            break;
        }

        HeapNode temporary = heap->nodes[parent];
        heap->nodes[parent] = heap->nodes[index];
        heap->nodes[index] = temporary;
        index = parent;
    }

    return true;
}

static bool heap_pop(MinHeap *heap, HeapNode *result)
{
    if (heap == NULL || result == NULL || heap->nodes == NULL || heap->size == 0) {
        return false;
    }

    *result = heap->nodes[0];
    --heap->size;

    if (heap->size == 0) {
        return true;
    }

    heap->nodes[0] = heap->nodes[heap->size];
    size_t index = 0;

    for (;;) {
        size_t left = index * 2U + 1U;
        size_t right = left + 1U;
        size_t smallest = index;

        if (left < heap->size &&
            heap->nodes[left].value < heap->nodes[smallest].value) {
            smallest = left;
        }

        if (right < heap->size &&
            heap->nodes[right].value < heap->nodes[smallest].value) {
            smallest = right;
        }

        if (smallest == index) {
            break;
        }

        HeapNode temporary = heap->nodes[index];
        heap->nodes[index] = heap->nodes[smallest];
        heap->nodes[smallest] = temporary;
        index = smallest;
    }

    return true;
}

static bool find_smallest_range(const int *const arrays[],
                                const size_t lengths[],
                                size_t array_count,
                                int *range_start,
                                int *range_end)
{
    if (arrays == NULL || lengths == NULL || range_start == NULL ||
        range_end == NULL || array_count == 0) {
        return false;
    }

    MinHeap heap = {0};

    if (!heap_init(&heap, array_count)) {
        return false;
    }

    int current_max = INT_MIN;
    bool success = false;

    for (size_t i = 0; i < array_count; ++i) {
        if (arrays[i] == NULL || lengths[i] == 0) {
            goto cleanup;
        }

        HeapNode node = {
            .value = arrays[i][0],
            .array_index = i,
            .element_index = 0
        };

        if (!heap_push(&heap, node)) {
            goto cleanup;
        }

        if (node.value > current_max) {
            current_max = node.value;
        }
    }

    int best_start = heap.nodes[0].value;
    int best_end = current_max;
    long long best_width = (long long)best_end - (long long)best_start;

    while (heap.size == array_count) {
        HeapNode minimum;

        if (!heap_pop(&heap, &minimum)) {
            goto cleanup;
        }

        long long current_width =
            (long long)current_max - (long long)minimum.value;

        if (current_width < best_width ||
            (current_width == best_width && minimum.value < best_start)) {
            best_start = minimum.value;
            best_end = current_max;
            best_width = current_width;
        }

        size_t next_index = minimum.element_index + 1U;

        if (next_index >= lengths[minimum.array_index]) {
            break;
        }

        HeapNode next = {
            .value = arrays[minimum.array_index][next_index],
            .array_index = minimum.array_index,
            .element_index = next_index
        };

        if (!heap_push(&heap, next)) {
            goto cleanup;
        }

        if (next.value > current_max) {
            current_max = next.value;
        }
    }

    *range_start = best_start;
    *range_end = best_end;
    success = true;

cleanup:
    heap_destroy(&heap);
    return success;
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

    int range_start;
    int range_end;

    if (!find_smallest_range(arrays,
                             lengths,
                             sizeof(arrays) / sizeof(arrays[0]),
                             &range_start,
                             &range_end)) {
        fputs("Unable to find a valid range.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("[%d, %d]\n", range_start, range_end) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}