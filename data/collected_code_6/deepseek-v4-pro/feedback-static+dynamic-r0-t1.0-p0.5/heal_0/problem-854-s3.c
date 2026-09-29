#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
} Heap;

static void heap_swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void heap_sift_down(Heap *heap, size_t index) {
    size_t largest = index;
    size_t left = 2 * index + 1;
    size_t right = 2 * index + 2;

    if (left < heap->size && heap->data[left] > heap->data[largest]) {
        largest = left;
    }
    if (right < heap->size && heap->data[right] > heap->data[largest]) {
        largest = right;
    }
    if (largest != index) {
        heap_swap(&heap->data[index], &heap->data[largest]);
        heap_sift_down(heap, largest);
    }
}

static void heap_build(Heap *heap) {
    if (heap->size <= 1) {
        return;
    }
    for (size_t i = heap->size / 2; i > 0; --i) {
        heap_sift_down(heap, i - 1);
    }
}

Heap *heap_create_from_array(const int *array, size_t length) {
    if (array == NULL && length > 0) {
        return NULL;
    }
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    if (heap == NULL) {
        return NULL;
    }
    heap->data = (int *)malloc(length * sizeof(int));
    if (heap->data == NULL) {
        free(heap);
        return NULL;
    }
    heap->size = length;
    heap->capacity = length;
    for (size_t i = 0; i < length; ++i) {
        heap->data[i] = array[i];
    }
    heap_build(heap);
    return heap;
}

void heap_destroy(Heap *heap) {
    if (heap != NULL) {
        free(heap->data);
        free(heap);
    }
}

void heap_print(const Heap *heap) {
    if (heap == NULL) {
        printf("NULL\n");
        return;
    }
    for (size_t i = 0; i < heap->size; ++i) {
        printf("%d ", heap->data[i]);
    }
    printf("\n");
}

int main(void) {
    int input[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    size_t length = sizeof(input) / sizeof(input[0]);

    Heap *heap = heap_create_from_array(input, length);
    if (heap == NULL) {
        fprintf(stderr, "Failed to create heap\n");
        return EXIT_FAILURE;
    }

    printf("Original array: ");
    for (size_t i = 0; i < length; ++i) {
        printf("%d ", input[i]);
    }
    printf("\n");

    printf("Heap: ");
    heap_print(heap);

    heap_destroy(heap);
    return EXIT_SUCCESS;
}