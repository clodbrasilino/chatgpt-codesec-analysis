#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} MinHeap;

static bool min_heap_init(MinHeap *heap, size_t capacity)
{
    if (heap == NULL || capacity > SIZE_MAX / sizeof(*heap->data)) {
        return false;
    }

    heap->data = NULL;
    heap->size = 0;
    heap->capacity = capacity;

    if (capacity == 0) {
        return true;
    }

    heap->data = malloc(capacity * sizeof(*heap->data));
    if (heap->data == NULL) {
        heap->capacity = 0;
        return false;
    }

    return true;
}

static void min_heap_destroy(MinHeap *heap)
{
    if (heap != NULL) {
        free(heap->data);
        heap->data = NULL;
        heap->size = 0;
        heap->capacity = 0;
    }
}

static bool min_heap_push(MinHeap *heap, int value)
{
    size_t index;

    if (heap == NULL || heap->size >= heap->capacity) {
        return false;
    }

    index = heap->size;
    heap->size++;

    while (index > 0) {
        size_t parent = (index - 1) / 2;

        if (heap->data[parent] <= value) {
            break;
        }

        heap->data[index] = heap->data[parent];
        index = parent;
    }

    heap->data[index] = value;
    return true;
}

static bool min_heap_pop(MinHeap *heap, int *value)
{
    size_t index;
    int last;

    if (heap == NULL || value == NULL || heap->size == 0) {
        return false;
    }

    *value = heap->data[0];
    heap->size--;

    if (heap->size == 0) {
        return true;
    }

    last = heap->data[heap->size];
    index = 0;

    for (;;) {
        size_t left = index * 2 + 1;
        size_t right;
        size_t smallest;

        if (left >= heap->size) {
            break;
        }

        right = left + 1;
        smallest = left;

        if (right < heap->size && heap->data[right] < heap->data[left]) {
            smallest = right;
        }

        if (heap->data[smallest] >= last) {
            break;
        }

        heap->data[index] = heap->data[smallest];
        index = smallest;
    }

    heap->data[index] = last;
    return true;
}

static bool push_all_and_pop_smallest(const int *values, size_t count, int *output)
{
    MinHeap heap;
    size_t index;
    bool success = false;

    if (count > 0 && (values == NULL || output == NULL)) {
        return false;
    }

    if (!min_heap_init(&heap, count)) {
        return false;
    }

    for (index = 0; index < count; index++) {
        if (!min_heap_push(&heap, values[index])) {
            goto cleanup;
        }
    }

    for (index = 0; index < count; index++) {
        if (!min_heap_pop(&heap, &output[index])) {
            goto cleanup;
        }
    }

    success = true;

cleanup:
    min_heap_destroy(&heap);
    return success;
}

int main(void)
{
    const int values[] = {42, 7, 19, -3, 25, 7, 1, 100, 0};
    int sorted[sizeof(values) / sizeof(values[0])];
    const size_t count = sizeof(values) / sizeof(values[0]);
    size_t index;

    if (!push_all_and_pop_smallest(values, count, sorted)) {
        if (fprintf(stderr, "Heap operation failed\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    for (index = 0; index < count; index++) {
        if (printf("%d%c", sorted[index], index + 1 == count ? '\n' : ' ') < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}