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

static bool heap_init(MinHeap *heap, size_t capacity)
{
    if (heap == NULL || capacity > SIZE_MAX / sizeof(*heap->data)) {
        return false;
    }

    heap->data = NULL;
    heap->size = 0;
    heap->capacity = capacity;

    if (capacity > 0) {
        heap->data = malloc(capacity * sizeof(*heap->data));
        if (heap->data == NULL) {
            heap->capacity = 0;
            return false;
        }
    }

    return true;
}

static void heap_destroy(MinHeap *heap)
{
    if (heap != NULL) {
        free(heap->data);
        heap->data = NULL;
        heap->size = 0;
        heap->capacity = 0;
    }
}

static bool heap_push(MinHeap *heap, int value)
{
    size_t index;

    if (heap == NULL || heap->size >= heap->capacity) {
        return false;
    }

    index = heap->size++;
    heap->data[index] = value;

    while (index > 0) {
        size_t parent = (index - 1) / 2;
        int temporary;

        if (heap->data[parent] <= heap->data[index]) {
            break;
        }

        temporary = heap->data[parent];
        heap->data[parent] = heap->data[index];
        heap->data[index] = temporary;
        index = parent;
    }

    return true;
}

static bool heap_pop_min(MinHeap *heap, int *value)
{
    size_t index = 0;

    if (heap == NULL || value == NULL || heap->size == 0) {
        return false;
    }

    *value = heap->data[0];
    --heap->size;

    if (heap->size == 0) {
        return true;
    }

    heap->data[0] = heap->data[heap->size];

    for (;;) {
        size_t left = index * 2 + 1;
        size_t right;
        size_t smallest;
        int temporary;

        if (left >= heap->size) {
            break;
        }

        right = left + 1;
        smallest = left;

        if (right < heap->size && heap->data[right] < heap->data[left]) {
            smallest = right;
        }

        if (heap->data[index] <= heap->data[smallest]) {
            break;
        }

        temporary = heap->data[index];
        heap->data[index] = heap->data[smallest];
        heap->data[smallest] = temporary;
        index = smallest;
    }

    return true;
}

static bool heap_sort_values(const int *values, size_t count, int *sorted_values)
{
    MinHeap heap;
    size_t index;
    bool success = false;

    if (count > 0 && (values == NULL || sorted_values == NULL)) {
        return false;
    }

    if (!heap_init(&heap, count)) {
        return false;
    }

    for (index = 0; index < count; ++index) {
        if (!heap_push(&heap, values[index])) {
            goto cleanup;
        }
    }

    for (index = 0; index < count; ++index) {
        if (!heap_pop_min(&heap, &sorted_values[index])) {
            goto cleanup;
        }
    }

    success = true;

cleanup:
    heap_destroy(&heap);
    return success;
}

int main(void)
{
    const int values[] = {42, 7, 19, -3, 25, 7, 1, 100, 0};
    const size_t count = sizeof(values) / sizeof(values[0]);
    int *sorted_values;
    size_t index;
    int result = EXIT_FAILURE;

    if (count > SIZE_MAX / sizeof(*sorted_values)) {
        return EXIT_FAILURE;
    }

    sorted_values = malloc(count * sizeof(*sorted_values));
    if (sorted_values == NULL) {
        return EXIT_FAILURE;
    }

    if (!heap_sort_values(values, count, sorted_values)) {
        goto cleanup;
    }

    for (index = 0; index < count; ++index) {
        if (printf("%d%s", sorted_values[index],
                   index + 1 == count ? "\n" : " ") < 0) {
            goto cleanup;
        }
    }

    result = EXIT_SUCCESS;

cleanup:
    free(sorted_values);
    return result;
}