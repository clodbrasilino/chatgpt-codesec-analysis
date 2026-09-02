#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
    int capacity;
} MinHeap;

MinHeap* heap_create(int capacity) {
    MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
    if (!heap) return NULL;
    heap->data = (int*)malloc(sizeof(int) * capacity);
    if (!heap->data) {
        free(heap);
        return NULL;
    }
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void heap_destroy(MinHeap *heap) {
    if (heap) {
        free(heap->data);
        free(heap);
    }
}

void heap_swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up(MinHeap *heap, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap->data[index] < heap->data[parent]) {
            heap_swap(&heap->data[index], &heap->data[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

void heapify_down(MinHeap *heap, int index) {
    while (1) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;
        if (left < heap->size && heap->data[left] < heap->data[smallest]) {
            smallest = left;
        }
        if (right < heap->size && heap->data[right] < heap->data[smallest]) {
            smallest = right;
        }
        if (smallest != index) {
            heap_swap(&heap->data[index], &heap->data[smallest]);
            index = smallest;
        } else {
            break;
        }
    }
}

int heap_push(MinHeap *heap, int value) {
    if (!heap || heap->size >= heap->capacity) return -1;
    heap->data[heap->size] = value;
    heapify_up(heap, heap->size);
    heap->size++;
    return 0;
}

int heap_pop(MinHeap *heap, int *value) {
    if (!heap || heap->size == 0) return -1;
    *value = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    heapify_down(heap, 0);
    return 0;
}

int main(void) {
    int values[] = {5, 3, 8, 1, 9, 2, 7, 4, 6};
    int count = sizeof(values) / sizeof(values[0]);
    MinHeap *heap = heap_create(count);
    if (!heap) return 1;

    for (int i = 0; i < count; i++) {
        if (heap_push(heap, values[i]) != 0) {
            heap_destroy(heap);
            return 1;
        }
    }

    int value;
    while (heap_pop(heap, &value) == 0) {
        printf("%d ", value);
    }
    printf("\n");

    heap_destroy(heap);
    return 0;
}