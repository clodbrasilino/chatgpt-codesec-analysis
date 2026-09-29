#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} MinHeap;

static void swap(int *a, int *b);
static void heapify_up(MinHeap *heap, size_t index);
static void heapify_down(MinHeap *heap, size_t index);
MinHeap* create_heap(size_t capacity);
void destroy_heap(MinHeap *heap);
bool push_heap(MinHeap *heap, int value);
bool pop_heap(MinHeap *heap, int *out_value);

static void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void heapify_up(MinHeap *heap, size_t index) {
    while (index > 0) {
        size_t parent = (index - 1) / 2;
        if (heap->data[parent] <= heap->data[index]) {
            break;
        }
        swap(&heap->data[parent], &heap->data[index]);
        index = parent;
    }
}

static void heapify_down(MinHeap *heap, size_t index) {
    while (true) {
        size_t smallest = index;
        size_t left = 2 * index + 1;
        size_t right = 2 * index + 2;

        if (left < heap->size && heap->data[left] < heap->data[smallest]) {
            smallest = left;
        }
        if (right < heap->size && heap->data[right] < heap->data[smallest]) {
            smallest = right;
        }
        if (smallest == index) {
            break;
        }
        swap(&heap->data[index], &heap->data[smallest]);
        index = smallest;
    }
}

MinHeap* create_heap(size_t capacity) {
    if (capacity == 0) {
        return NULL;
    }

    MinHeap *heap = malloc(sizeof(MinHeap));
    if (!heap) {
        return NULL;
    }

    heap->data = malloc(capacity * sizeof(int));
    if (!heap->data) {
        free(heap);
        return NULL;
    }

    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void destroy_heap(MinHeap *heap) {
    if (heap) {
        free(heap->data);
        free(heap);
    }
}

bool push_heap(MinHeap *heap, int value) {
    if (!heap || heap->size >= heap->capacity) {
        return false;
    }

    heap->data[heap->size] = value;
    heapify_up(heap, heap->size);
    heap->size++;
    return true;
}

bool pop_heap(MinHeap *heap, int *out_value) {
    if (!heap || heap->size == 0 || !out_value) {
        return false;
    }

    *out_value = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;

    if (heap->size > 0) {
        heapify_down(heap, 0);
    }

    return true;
}

int main(void) {
    int values_to_insert[] = {42, 17, -5, 8, 100, 23, -12, 0, 7};
    size_t num_values = sizeof(values_to_insert) / sizeof(values_to_insert[0]);

    MinHeap *heap = create_heap(num_values);
    if (!heap) {
        fprintf(stderr, "Failed to allocate memory for heap.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < num_values; i++) {
        if (!push_heap(heap, values_to_insert[i])) {
            fprintf(stderr, "Failed to push value into heap at index %zu.\n", i);
            destroy_heap(heap);
            return EXIT_FAILURE;
        }
    }

    int popped_value;
    while (pop_heap(heap, &popped_value)) {
        printf("%d\n", popped_value);
    }

    destroy_heap(heap);
    return EXIT_SUCCESS;
}