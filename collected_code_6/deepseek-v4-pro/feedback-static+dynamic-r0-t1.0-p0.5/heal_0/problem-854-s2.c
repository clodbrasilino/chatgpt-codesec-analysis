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

static void heap_sift_up(Heap *heap, size_t index) {
    while (index > 0) {
        size_t parent = (index - 1) / 2;
        if (heap->data[parent] >= heap->data[index]) {
            break;
        }
        heap_swap(&heap->data[parent], &heap->data[index]);
        index = parent;
    }
}

Heap *heap_create(size_t capacity) {
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    if (heap == NULL) {
        return NULL;
    }
    heap->data = (int *)malloc(capacity * sizeof(int));
    if (heap->data == NULL) {
        free(heap);
        return NULL;
    }
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void heap_destroy(Heap *heap) {
    if (heap != NULL) {
        free(heap->data);
        free(heap);
    }
}

int heap_push(Heap *heap, int value) {
    if (heap == NULL || heap->size >= heap->capacity) {
        return -1;
    }
    heap->data[heap->size] = value;
    heap_sift_up(heap, heap->size);
    heap->size++;
    return 0;
}

int heap_pop(Heap *heap, int *value) {
    if (heap == NULL || heap->size == 0 || value == NULL) {
        return -1;
    }
    *value = heap->data[0];
    heap->size--;
    if (heap->size > 0) {
        heap->data[0] = heap->data[heap->size];
        heap_sift_down(heap, 0);
    }
    return 0;
}

void heapify(Heap *heap) {
    if (heap == NULL || heap->size <= 1) {
        return;
    }
    for (size_t i = heap->size / 2; i > 0; i--) {
        heap_sift_down(heap, i - 1);
    }
}

void heap_from_array(Heap *heap, int *array, size_t length) {
    if (heap == NULL || array == NULL || length > heap->capacity) {
        return;
    }
    for (size_t i = 0; i < length; i++) {
        heap->data[i] = array[i];
    }
    heap->size = length;
    heapify(heap);
}

void heap_print(Heap *heap) {
    if (heap == NULL) {
        return;
    }
    for (size_t i = 0; i < heap->size; i++) {
        printf("%d ", heap->data[i]);
    }
    printf("\n");
}

int main(void) {
    int array[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    size_t length = sizeof(array) / sizeof(array[0]);

    Heap *heap = heap_create(length);
    if (heap == NULL) {
        fprintf(stderr, "Failed to allocate heap\n");
        return 1;
    }

    heap_from_array(heap, array, length);
    printf("Heapified array: ");
    heap_print(heap);

    printf("Popped values: ");
    int value;
    while (heap_pop(heap, &value) == 0) {
        printf("%d ", value);
    }
    printf("\n");

    heap_destroy(heap);
    return 0;
}