#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} Heap;

static void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void heapify_down(Heap *heap, size_t idx) {
    size_t smallest = idx;
    size_t left = 2 * idx + 1;
    size_t right = 2 * idx + 2;

    if (left < heap->size && heap->data[left] < heap->data[smallest])
        smallest = left;
    if (right < heap->size && heap->data[right] < heap->data[smallest])
        smallest = right;

    if (smallest != idx) {
        swap(&heap->data[idx], &heap->data[smallest]);
        heapify_down(heap, smallest);
    }
}

static void heapify_up(Heap *heap, size_t idx) {
    while (idx > 0) {
        size_t parent = (idx - 1) / 2;
        if (heap->data[parent] <= heap->data[idx])
            break;
        swap(&heap->data[parent], &heap->data[idx]);
        idx = parent;
    }
}

int heap_delete_min_and_insert(Heap *heap, int new_item) {
    if (heap == NULL || heap->data == NULL || heap->size == 0)
        return -1;

    heap->data[0] = new_item;
    heapify_down(heap, 0);
    return 0;
}

int heap_init(Heap *heap, size_t capacity) {
    if (heap == NULL || capacity == 0)
        return -1;

    heap->data = malloc(capacity * sizeof(int));
    if (heap->data == NULL)
        return -1;

    heap->size = 0;
    heap->capacity = capacity;
    return 0;
}

void heap_destroy(Heap *heap) {
    if (heap != NULL) {
        free(heap->data);
        heap->data = NULL;
        heap->size = 0;
        heap->capacity = 0;
    }
}

int heap_insert(Heap *heap, int value) {
    if (heap == NULL || heap->size >= heap->capacity)
        return -1;

    heap->data[heap->size] = value;
    heapify_up(heap, heap->size);
    heap->size++;
    return 0;
}

int main(void) {
    Heap heap;
    if (heap_init(&heap, 10) != 0) {
        fprintf(stderr, "Failed to initialize heap\n");
        return EXIT_FAILURE;
    }

    int values[] = {10, 20, 15, 40, 50, 100, 25, 45};
    size_t n = sizeof(values) / sizeof(values[0]);

    for (size_t i = 0; i < n; i++) {
        if (heap_insert(&heap, values[i]) != 0) {
            fprintf(stderr, "Failed to insert value\n");
            heap_destroy(&heap);
            return EXIT_FAILURE;
        }
    }

    printf("Heap before: ");
    for (size_t i = 0; i < heap.size; i++)
        printf("%d ", heap.data[i]);
    printf("\n");

    if (heap_delete_min_and_insert(&heap, 5) != 0) {
        fprintf(stderr, "Failed to delete min and insert\n");
        heap_destroy(&heap);
        return EXIT_FAILURE;
    }

    printf("Heap after:  ");
    for (size_t i = 0; i < heap.size; i++)
        printf("%d ", heap.data[i]);
    printf("\n");

    heap_destroy(&heap);
    return EXIT_SUCCESS;
}