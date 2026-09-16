#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} MinHeap;

static void swap_ints(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

static int heap_init(MinHeap *heap, size_t capacity)
{
    if (heap == NULL || capacity == 0 || capacity > SIZE_MAX / sizeof(*heap->data)) {
        return -1;
    }

    heap->data = malloc(capacity * sizeof(*heap->data));
    if (heap->data == NULL) {
        heap->size = 0;
        heap->capacity = 0;
        return -1;
    }

    heap->size = 0;
    heap->capacity = capacity;
    return 0;
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

static int heap_push(MinHeap *heap, int value)
{
    size_t index;

    if (heap == NULL || heap->data == NULL || heap->size >= heap->capacity) {
        return -1;
    }

    index = heap->size++;
    heap->data[index] = value;

    while (index > 0) {
        size_t parent = (index - 1) / 2;

        if (heap->data[parent] <= heap->data[index]) {
            break;
        }

        swap_ints(&heap->data[parent], &heap->data[index]);
        index = parent;
    }

    return 0;
}

static void sift_down(MinHeap *heap, size_t index)
{
    for (;;) {
        size_t smallest = index;
        size_t left = index * 2 + 1;
        size_t right = left + 1;

        if (left < heap->size && heap->data[left] < heap->data[smallest]) {
            smallest = left;
        }

        if (right < heap->size && heap->data[right] < heap->data[smallest]) {
            smallest = right;
        }

        if (smallest == index) {
            break;
        }

        swap_ints(&heap->data[index], &heap->data[smallest]);
        index = smallest;
    }
}

static int heap_delete_min_and_insert(MinHeap *heap, int new_item, int *deleted)
{
    if (heap == NULL || heap->data == NULL || deleted == NULL || heap->size == 0) {
        return -1;
    }

    *deleted = heap->data[0];
    heap->data[0] = new_item;

    if (heap->size > 1) {
        sift_down(heap, 0);
    }

    return 0;
}

static void heap_print(const MinHeap *heap)
{
    size_t i;

    if (heap == NULL || heap->data == NULL) {
        return;
    }

    for (i = 0; i < heap->size; ++i) {
        printf("%d%s", heap->data[i], i + 1 == heap->size ? "\n" : " ");
    }
}

int main(void)
{
    const int values[] = {4, 10, 3, 5, 1, 8};
    const size_t count = sizeof(values) / sizeof(values[0]);
    MinHeap heap = {NULL, 0, 0};
    int deleted;
    size_t i;

    if (heap_init(&heap, count) != 0) {
        fprintf(stderr, "Failed to initialize heap\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; ++i) {
        if (heap_push(&heap, values[i]) != 0) {
            fprintf(stderr, "Failed to insert heap element\n");
            heap_destroy(&heap);
            return EXIT_FAILURE;
        }
    }

    if (heap_delete_min_and_insert(&heap, 7, &deleted) != 0) {
        fprintf(stderr, "Failed to replace the smallest element\n");
        heap_destroy(&heap);
        return EXIT_FAILURE;
    }

    printf("Deleted: %d\n", deleted);
    heap_print(&heap);

    heap_destroy(&heap);
    return EXIT_SUCCESS;
}