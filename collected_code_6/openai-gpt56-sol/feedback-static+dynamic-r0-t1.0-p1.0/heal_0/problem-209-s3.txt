#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    int *items;
    size_t size;
    size_t capacity;
} MinHeap;

static void swap_ints(int *a, int *b)
{
    int temporary = *a;
    *a = *b;
    *b = temporary;
}

static bool heap_init(MinHeap *heap, size_t capacity)
{
    if (heap == NULL || capacity == 0 || capacity > SIZE_MAX / sizeof(*heap->items)) {
        return false;
    }

    heap->items = malloc(capacity * sizeof(*heap->items));
    if (heap->items == NULL) {
        heap->size = 0;
        heap->capacity = 0;
        return false;
    }

    heap->size = 0;
    heap->capacity = capacity;
    return true;
}

static void heap_destroy(MinHeap *heap)
{
    if (heap != NULL) {
        free(heap->items);
        heap->items = NULL;
        heap->size = 0;
        heap->capacity = 0;
    }
}

static bool heap_insert(MinHeap *heap, int value)
{
    if (heap == NULL || heap->items == NULL || heap->size >= heap->capacity) {
        return false;
    }

    size_t index = heap->size;
    heap->items[index] = value;
    ++heap->size;

    while (index > 0) {
        size_t parent = (index - 1) / 2;

        if (heap->items[parent] <= heap->items[index]) {
            break;
        }

        swap_ints(&heap->items[parent], &heap->items[index]);
        index = parent;
    }

    return true;
}

static bool heap_delete_min(MinHeap *heap, int *removed_value)
{
    if (heap == NULL || heap->items == NULL || removed_value == NULL || heap->size == 0) {
        return false;
    }

    *removed_value = heap->items[0];
    --heap->size;

    if (heap->size == 0) {
        return true;
    }

    heap->items[0] = heap->items[heap->size];
    size_t index = 0;

    while (index <= (heap->size - 2) / 2) {
        size_t left = index * 2 + 1;
        size_t right = left + 1;
        size_t smallest = left;

        if (right < heap->size && heap->items[right] < heap->items[left]) {
            smallest = right;
        }

        if (heap->items[index] <= heap->items[smallest]) {
            break;
        }

        swap_ints(&heap->items[index], &heap->items[smallest]);
        index = smallest;
    }

    return true;
}

static bool heap_replace_min(MinHeap *heap, int new_value, int *removed_value)
{
    if (!heap_delete_min(heap, removed_value)) {
        return false;
    }

    if (!heap_insert(heap, new_value)) {
        return false;
    }

    return true;
}

static void heap_print(const MinHeap *heap)
{
    if (heap == NULL || heap->items == NULL) {
        return;
    }

    for (size_t index = 0; index < heap->size; ++index) {
        printf("%d%s", heap->items[index], index + 1 == heap->size ? "\n" : " ");
    }
}

int main(void)
{
    MinHeap heap = {0};
    size_t count;
    int new_value;
    int removed_value;

    if (scanf("%zu", &count) != 1 || count == 0) {
        fprintf(stderr, "Invalid heap size\n");
        return EXIT_FAILURE;
    }

    if (!heap_init(&heap, count)) {
        fprintf(stderr, "Failed to initialize heap\n");
        return EXIT_FAILURE;
    }

    for (size_t index = 0; index < count; ++index) {
        int value;

        if (scanf("%d", &value) != 1 || !heap_insert(&heap, value)) {
            fprintf(stderr, "Failed to read or insert heap item\n");
            heap_destroy(&heap);
            return EXIT_FAILURE;
        }
    }

    if (scanf("%d", &new_value) != 1) {
        fprintf(stderr, "Invalid new item\n");
        heap_destroy(&heap);
        return EXIT_FAILURE;
    }

    if (!heap_replace_min(&heap, new_value, &removed_value)) {
        fprintf(stderr, "Failed to replace the smallest item\n");
        heap_destroy(&heap);
        return EXIT_FAILURE;
    }

    printf("Deleted: %d\n", removed_value);
    heap_print(&heap);

    heap_destroy(&heap);
    return EXIT_SUCCESS;
}