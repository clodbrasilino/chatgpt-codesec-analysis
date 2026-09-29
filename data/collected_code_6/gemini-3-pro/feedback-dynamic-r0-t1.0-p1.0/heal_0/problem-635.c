#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* array;
    size_t size;
    size_t capacity;
} MinHeap;

MinHeap* create_heap(size_t capacity) {
    if (capacity == 0) {
        return NULL;
    }
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    if (!heap) {
        return NULL;
    }
    heap->array = (int*)malloc(capacity * sizeof(int));
    if (!heap->array) {
        free(heap);
        return NULL;
    }
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void destroy_heap(MinHeap* heap) {
    if (heap) {
        free(heap->array);
        free(heap);
    }
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up(MinHeap* heap, size_t index) {
    while (index != 0 && heap->array[(index - 1) / 2] > heap->array[index]) {
        swap(&heap->array[index], &heap->array[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

void heapify_down(MinHeap* heap, size_t index) {
    size_t smallest = index;
    size_t left = 2 * index + 1;
    size_t right = 2 * index + 2;

    if (left < heap->size && heap->array[left] < heap->array[smallest]) {
        smallest = left;
    }
    if (right < heap->size && heap->array[right] < heap->array[smallest]) {
        smallest = right;
    }
    if (smallest != index) {
        swap(&heap->array[index], &heap->array[smallest]);
        heapify_down(heap, smallest);
    }
}

int push(MinHeap* heap, int value) {
    if (!heap || heap->size == heap->capacity) {
        return -1;
    }
    heap->array[heap->size] = value;
    heap->size++;
    heapify_up(heap, heap->size - 1);
    return 0;
}

int pop(MinHeap* heap, int* out_value) {
    if (!heap || heap->size == 0 || !out_value) {
        return -1;
    }
    if (heap->size == 1) {
        heap->size--;
        *out_value = heap->array[0];
        return 0;
    }
    *out_value = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;
    heapify_down(heap, 0);
    return 0;
}

int main(void) {
    int values[] = {5, 3, 8, 1, 9, 2};
    size_t num_values = sizeof(values) / sizeof(values[0]);

    MinHeap* heap = create_heap(num_values);
    if (!heap) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < num_values; i++) {
        if (push(heap, values[i]) != 0) {
            destroy_heap(heap);
            return EXIT_FAILURE;
        }
    }

    int popped_value;
    while (pop(heap, &popped_value) == 0) {
        printf("%d\n", popped_value);
    }

    destroy_heap(heap);
    return EXIT_SUCCESS;
}