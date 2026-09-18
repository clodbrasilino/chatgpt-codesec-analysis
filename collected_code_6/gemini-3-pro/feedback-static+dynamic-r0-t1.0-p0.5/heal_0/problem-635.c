#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} MinHeap;

MinHeap* create_heap(size_t initial_capacity) {
    if (initial_capacity == 0) {
        initial_capacity = 16;
    }
    MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
    if (!heap) {
        return NULL;
    }
    heap->data = (int*)malloc(initial_capacity * sizeof(int));
    if (!heap->data) {
        free(heap);
        return NULL;
    }
    heap->size = 0;
    heap->capacity = initial_capacity;
    return heap;
}

void destroy_heap(MinHeap *heap) {
    if (heap) {
        free(heap->data);
        free(heap);
    }
}

static void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void bubble_up(MinHeap *heap, size_t index) {
    while (index > 0) {
        size_t parent = (index - 1) / 2;
        if (heap->data[index] >= heap->data[parent]) {
            break;
        }
        swap(&heap->data[index], &heap->data[parent]);
        index = parent;
    }
}

static void bubble_down(MinHeap *heap, size_t index) {
    while (true) {
        size_t left = 2 * index + 1;
        size_t right = 2 * index + 2;
        size_t smallest = index;

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

bool push(MinHeap *heap, int value) {
    if (!heap) {
        return false;
    }
    if (heap->size == heap->capacity) {
        size_t new_capacity = heap->capacity * 2;
        int *new_data = (int*)realloc(heap->data, new_capacity * sizeof(int));
        if (!new_data) {
            return false;
        }
        heap->data = new_data;
        heap->capacity = new_capacity;
    }
    heap->data[heap->size] = value;
    bubble_up(heap, heap->size);
    heap->size++;
    return true;
}

bool pop(MinHeap *heap, int *out_value) {
    if (!heap || heap->size == 0 || !out_value) {
        return false;
    }
    *out_value = heap->data[0];
    heap->size--;
    if (heap->size > 0) {
        heap->data[0] = heap->data[heap->size];
        bubble_down(heap, 0);
    }
    return true;
}

int main(void) {
    MinHeap *heap = create_heap(4);
    if (!heap) {
        fprintf(stderr, "Failed to create heap\n");
        return EXIT_FAILURE;
    }

    int values_to_push[] = {45, 20, 14, 12, 31, 7, 11, 13, 9};
    size_t num_values = sizeof(values_to_push) / sizeof(values_to_push[0]);

    for (size_t i = 0; i < num_values; i++) {
        if (!push(heap, values_to_push[i])) {
            fprintf(stderr, "Failed to push value %d\n", values_to_push[i]);
            destroy_heap(heap);
            return EXIT_FAILURE;
        }
    }

    int popped_value;
    while (pop(heap, &popped_value)) {
        printf("%d\n", popped_value);
    }

    destroy_heap(heap);
    return EXIT_SUCCESS;
}