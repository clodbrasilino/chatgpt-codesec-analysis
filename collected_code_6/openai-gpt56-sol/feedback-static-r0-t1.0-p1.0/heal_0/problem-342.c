#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <limits.h>

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
    size_t index;

    if (heap == NULL || heap->nodes == NULL || heap->size >= heap->capacity) {
        return false;
    }

    index = heap->size++;
    while (index > 0) {
        size_t parent = (index - 1U) / 2U;

        if (heap->nodes[parent].value <= node.value) {
            break;
        }

        heap->nodes[index] = heap->nodes[parent];
        index = parent;
    }

    heap->nodes[index] = node;
    return true;
}

static bool heap_pop(MinHeap *heap, HeapNode *result)
{
    HeapNode last;
    size_t index = 0;

    if (heap == NULL || heap->nodes == NULL || result == NULL || heap->size == 0) {
        return false;
    }

    *result = heap->nodes[0];
    --heap->size;

    if (heap->size == 0) {
        return true;
    }

    last = heap->nodes[heap->size];

    while (true) {
        size_t left = index * 2U + 1U;
        size_t right;
        size_t smallest;

        if (left >= heap->size) {
            break;
        }

        right = left + 1U;
        smallest = left;

        if (right < heap->size &&
            heap->nodes[right].value < heap->nodes[left].value) {
            smallest = right;
        }

        if (last.value <= heap->nodes[smallest].value) {
            break;
        }

        heap->nodes[index] = heap->nodes[smallest];
        index = smallest;
    }

    heap->nodes[index] = last;
    return true;
}

static bool find_smallest_range(
    const int *const arrays[],
    const size_t lengths[],
    size_t array_count,
    int *range_start,
    int *range_end)
{
    MinHeap heap = {0};
    int current_max = INT_MIN;
    int best_start = 0;
    int best_end = 0;
    long long best_width = LLONG_MAX;
    bool success = false;

    if (arrays == NULL || lengths == NULL || range_start == NULL ||
        range_end == NULL || array_count == 0) {
        return false;
    }

    if (!heap_init(&heap, array_count)) {
        return false;
    }

    for (size_t i = 0; i < array_count; ++i) {
        HeapNode node;

        if (arrays[i] == NULL || lengths[i] == 0) {
            goto cleanup;
        }

        node.value = arrays[i][0];
        node.array_index = i;
        node.element_index = 0;

        if (!heap_push(&heap, node)) {
            goto cleanup;
        }

        if (node.value > current_max) {
            current_max = node.value;
        }
    }

    while (heap.size == array_count) {
        HeapNode minimum;
        long long width;

        if (!heap_pop(&heap, &minimum)) {
            goto cleanup;
        }

        width = (long long)current_max - (long long)minimum.value;
        if (width < best_width ||
            (width == best_width && minimum.value < best_start)) {
            best_width = width;
            best_start = minimum.value;
            best_end = current_max;
        }

        if (minimum.element_index + 1U >= lengths[minimum.array_index]) {
            break;
        }

        ++minimum.element_index;
        minimum.value =
            arrays[minimum.array_index][minimum.element_index];

        if (minimum.value > current_max) {
            current_max = minimum.value;
        }

        if (!heap_push(&heap, minimum)) {
            goto cleanup;
        }
    }

    if (best_width != LLONG_MAX) {
        *range_start = best_start;
        *range_end = best_end;
        success = true;
    }

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

    if (!find_smallest_range(
            arrays,
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