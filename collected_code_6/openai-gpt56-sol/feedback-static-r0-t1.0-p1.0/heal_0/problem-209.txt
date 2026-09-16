#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <limits.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} MinHeap;

static bool heap_init(MinHeap *heap, size_t capacity)
{
    if (heap == NULL || capacity == 0 || capacity > SIZE_MAX / sizeof(*heap->data)) {
        return false;
    }

    heap->data = malloc(capacity * sizeof(*heap->data));
    if (heap->data == NULL) {
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
        free(heap->data);
        heap->data = NULL;
        heap->size = 0;
        heap->capacity = 0;
    }
}

static void heapify_down(MinHeap *heap, size_t index)
{
    for (;;) {
        size_t smallest = index;
        size_t left;
        size_t right;

        if (index > (SIZE_MAX - 2) / 2) {
            break;
        }

        left = 2 * index + 1;
        right = left + 1;

        if (left < heap->size && heap->data[left] < heap->data[smallest]) {
            smallest = left;
        }

        if (right < heap->size && heap->data[right] < heap->data[smallest]) {
            smallest = right;
        }

        if (smallest == index) {
            break;
        }

        {
            int temporary = heap->data[index];
            heap->data[index] = heap->data[smallest];
            heap->data[smallest] = temporary;
        }

        index = smallest;
    }
}

static void heapify_up(MinHeap *heap, size_t index)
{
    while (index > 0) {
        size_t parent = (index - 1) / 2;

        if (heap->data[parent] <= heap->data[index]) {
            break;
        }

        {
            int temporary = heap->data[parent];
            heap->data[parent] = heap->data[index];
            heap->data[index] = temporary;
        }

        index = parent;
    }
}

static bool heap_insert(MinHeap *heap, int value)
{
    if (heap == NULL || heap->data == NULL || heap->size >= heap->capacity) {
        return false;
    }

    heap->data[heap->size] = value;
    heapify_up(heap, heap->size);
    heap->size++;
    return true;
}

static bool heap_delete_min_and_insert(MinHeap *heap, int new_item, int *deleted)
{
    if (heap == NULL || heap->data == NULL || deleted == NULL || heap->size == 0) {
        return false;
    }

    *deleted = heap->data[0];
    heap->data[0] = new_item;
    heapify_down(heap, 0);
    return true;
}

static bool read_size(size_t *value)
{
    unsigned long long input;

    if (value == NULL || scanf("%llu", &input) != 1 || input == 0 ||
        input > SIZE_MAX || input > SIZE_MAX / sizeof(int)) {
        return false;
    }

    *value = (size_t)input;
    return true;
}

int main(void)
{
    MinHeap heap = {NULL, 0, 0};
    size_t count;
    int new_item;
    int deleted;

    if (!read_size(&count) || !heap_init(&heap, count)) {
        fputs("Invalid heap size\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        int value;

        if (scanf("%d", &value) != 1 || !heap_insert(&heap, value)) {
            fputs("Invalid heap element\n", stderr);
            heap_destroy(&heap);
            return EXIT_FAILURE;
        }
    }

    if (scanf("%d", &new_item) != 1) {
        fputs("Invalid new item\n", stderr);
        heap_destroy(&heap);
        return EXIT_FAILURE;
    }

    if (!heap_delete_min_and_insert(&heap, new_item, &deleted)) {
        fputs("Heap operation failed\n", stderr);
        heap_destroy(&heap);
        return EXIT_FAILURE;
    }

    printf("%d\n", deleted);

    for (size_t i = 0; i < heap.size; ++i) {
        printf("%d%c", heap.data[i], i + 1 == heap.size ? '\n' : ' ');
    }

    heap_destroy(&heap);
    return EXIT_SUCCESS;
}