#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} MinHeap;

bool init_heap(MinHeap *heap, size_t initial_capacity) {
    if (!heap) {
        return false;
    }
    heap->data = (int *)malloc(initial_capacity * sizeof(int));
    if (!heap->data) {
        heap->size = 0;
        heap->capacity = 0;
        return false;
    }
    heap->size = 0;
    heap->capacity = initial_capacity;
    return true;
}

void free_heap(MinHeap *heap) {
    if (heap) {
        free(heap->data);
        heap->data = NULL;
        heap->size = 0;
        heap->capacity = 0;
    }
}

static void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void heapify_up(MinHeap *heap, size_t index) {
    while (index > 0) {
        size_t parent = (index - 1) / 2;
        if (heap->data[parent] > heap->data[index]) {
            swap(&heap->data[parent], &heap->data[index]);
            index = parent;
        } else {
            break;
        }
    }
}

static void heapify_down(MinHeap *heap, size_t index) {
    size_t smallest = index;
    size_t left = 2 * index + 1;
    size_t right = 2 * index + 2;

    if (left < heap->size && heap->data[left] < heap->data[smallest]) {
        smallest = left;
    }
    if (right < heap->size && heap->data[right] < heap->data[smallest]) {
        smallest = right;
    }
    if (smallest != index) {
        swap(&heap->data[index], &heap->data[smallest]);
        heapify_down(heap, smallest);
    }
}

bool push(MinHeap *heap, int value) {
    if (!heap || !heap->data) {
        return false;
    }
    if (heap->size >= heap->capacity) {
        size_t new_capacity = heap->capacity == 0 ? 4 : heap->capacity * 2;
        int *new_data = (int *)realloc(heap->data, new_capacity * sizeof(int));
        if (!new_data) {
            return false;
        }
        heap->data = new_data;
        heap->capacity = new_capacity;
    }
    heap->data[heap->size] = value;
    heapify_up(heap, heap->size);
    heap->size++;
    return true;
}

bool pop(MinHeap *heap, int *out_value) {
    if (!heap || !heap->data || heap->size == 0 || !out_value) {
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
    MinHeap heap;
    if (!init_heap(&heap, 4)) {
        fprintf(stderr, "Failed to initialize heap\n");
        return EXIT_FAILURE;
    }

    int values_to_push[] = {42, 17, 8, 99, 23, 4, 15, 12, 1};
    size_t num_values = sizeof(values_to_push) / sizeof(values_to_push[0]);

    for (size_t i = 0; i < num_values; i++) {
        if (!push(&heap, values_to_push[i])) {
            fprintf(stderr, "Failed to push value %d\n", values_to_push[i]);
            free_heap(&heap);
            return EXIT_FAILURE;
        }
    }

    int popped_value;
    while (pop(&heap, &popped_value)) {
        printf("%d\n", popped_value);
    }

    free_heap(&heap);
    return EXIT_SUCCESS;
}