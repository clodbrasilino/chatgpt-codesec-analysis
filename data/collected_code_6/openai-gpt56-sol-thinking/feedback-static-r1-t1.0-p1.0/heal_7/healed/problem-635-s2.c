#include <errno.h>
#include <limits.h>
#include <stdbool.h>
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
    if (heap == NULL) {
        return false;
    }

    heap->data = NULL;
    heap->size = 0;
    heap->capacity = 0;

    if (capacity == 0) {
        return true;
    }

    if (capacity > SIZE_MAX / sizeof(*heap->data)) {
        return false;
    }

    heap->data = malloc(capacity * sizeof(*heap->data));
    if (heap->data == NULL) {
        return false;
    }

    heap->capacity = capacity;
    return true;
}

static void heap_destroy(MinHeap *heap)
{
    if (heap == NULL) {
        return;
    }

    free(heap->data);
    heap->data = NULL;
    heap->size = 0;
    heap->capacity = 0;
}

static bool heap_push(MinHeap *heap, int value)
{
    size_t index;

    if (heap == NULL ||
        heap->data == NULL ||
        heap->size >= heap->capacity) {
        return false;
    }

    index = heap->size;
    ++heap->size;

    while (index > 0) {
        size_t parent = (index - 1U) / 2U;

        if (heap->data[parent] <= value) {
            break;
        }

        heap->data[index] = heap->data[parent];
        index = parent;
    }

    heap->data[index] = value;
    return true;
}

static bool heap_pop_min(MinHeap *heap, int *value)
{
    size_t index;
    int replacement;

    if (heap == NULL ||
        heap->data == NULL ||
        value == NULL ||
        heap->size == 0) {
        return false;
    }

    *value = heap->data[0];
    --heap->size;

    if (heap->size == 0) {
        return true;
    }

    replacement = heap->data[heap->size];
    index = 0;

    while (index < heap->size / 2U) {
        size_t left = index * 2U + 1U;
        size_t right = left + 1U;
        size_t smallest = left;

        if (right < heap->size &&
            heap->data[right] < heap->data[left]) {
            smallest = right;
        }

        if (heap->data[smallest] >= replacement) {
            break;
        }

        heap->data[index] = heap->data[smallest];
        index = smallest;
    }

    heap->data[index] = replacement;
    return true;
}

static bool heap_sort_values(const int *values,
                             size_t count,
                             int *sorted_values)
{
    MinHeap heap;
    size_t i;

    if (count > 0 && (values == NULL || sorted_values == NULL)) {
        return false;
    }

    if (!heap_init(&heap, count)) {
        return false;
    }

    for (i = 0; i < count; ++i) {
        if (!heap_push(&heap, values[i])) {
            heap_destroy(&heap);
            return false;
        }
    }

    for (i = 0; i < count; ++i) {
        if (!heap_pop_min(&heap, &sorted_values[i])) {
            heap_destroy(&heap);
            return false;
        }
    }

    heap_destroy(&heap);
    return true;
}

static bool parse_int(const char *text, int *value)
{
    char *end;
    long parsed;

    if (text == NULL || value == NULL || *text == '\0') {
        return false;
    }

    errno = 0;
    parsed = strtol(text, &end, 10);

    if (errno == ERANGE ||
        end == text ||
        *end != '\0' ||
        parsed < INT_MIN ||
        parsed > INT_MAX) {
        return false;
    }

    *value = (int)parsed;
    return true;
}

static int run(int argc, char *const argv[])
{
    int *values = NULL;
    int *sorted_values = NULL;
    size_t count;
    size_t i;
    int result = EXIT_FAILURE;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s integer [integer ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    count = (size_t)(argc - 1);

    if (count > SIZE_MAX / sizeof(*values)) {
        fprintf(stderr, "Too many values\n");
        return EXIT_FAILURE;
    }

    values = malloc(count * sizeof(*values));
    sorted_values = malloc(count * sizeof(*sorted_values));

    if (values == NULL || sorted_values == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        goto cleanup;
    }

    for (i = 0; i < count; ++i) {
        if (!parse_int(argv[i + 1U], &values[i])) {
            fprintf(stderr, "Invalid integer: %s\n", argv[i + 1U]);
            goto cleanup;
        }
    }

    if (!heap_sort_values(values, count, sorted_values)) {
        fprintf(stderr, "Heap operation failed\n");
        goto cleanup;
    }

    for (i = 0; i < count; ++i) {
        if (printf("%s%d", i == 0 ? "" : " ", sorted_values[i]) < 0) {
            goto cleanup;
        }
    }

    if (putchar('\n') == EOF) {
        goto cleanup;
    }

    result = EXIT_SUCCESS;

cleanup:
    free(sorted_values);
    free(values);
    return result;
}

int main(int argc, char *argv[])
{
    return run(argc, argv);
}