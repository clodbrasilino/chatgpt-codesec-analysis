#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int capacity;
    int size;
} MinHeap;

MinHeap* create_heap(int capacity) {
    MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
    if (heap == NULL) return NULL;
    heap->data = (int*)malloc(capacity * sizeof(int));
    if (heap->data == NULL) {
        free(heap);
        return NULL;
    }
    heap->capacity = capacity;
    heap->size = 0;
    return heap;
}

void destroy_heap(MinHeap *heap) {
    if (heap != NULL) {
        free(heap->data);
        free(heap);
    }
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up(MinHeap *heap, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap->data[index] < heap->data[parent]) {
            swap(&heap->data[index], &heap->data[parent]);
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
            swap(&heap->data[index], &heap->data[smallest]);
            index = smallest;
        } else {
            break;
        }
    }
}

int replace_min(MinHeap *heap, int new_item) {
    if (heap == NULL || heap->size == 0) {
        return -1;
    }
    int min_item = heap->data[0];
    heap->data[0] = new_item;
    heapify_down(heap, 0);
    return min_item;
}

int insert_heap(MinHeap *heap, int item) {
    if (heap == NULL || heap->size >= heap->capacity) {
        return -1;
    }
    heap->data[heap->size] = item;
    heap->size++;
    heapify_up(heap, heap->size - 1);
    return 0;
}

void delete_min_and_insert(MinHeap *heap, int new_item, int *deleted_item) {
    if (heap == NULL || heap->size <= 0) {
        *deleted_item = -1;
        return;
    }
    *deleted_item = heap->data[0];
    heap->data[0] = new_item;
    heapify_down(heap, 0);
}

int main() {
    int capacity = 10;
    MinHeap *heap = create_heap(capacity);
    if (heap == NULL) {
        return 1;
    }

    insert_heap(heap, 10);
    insert_heap(heap, 20);
    insert_heap(heap, 5);
    insert_heap(heap, 30);

    int deleted;
    delete_min_and_insert(heap, 15, &deleted);
    
    printf("Deleted item: %d\n", deleted);
    printf("Heap size: %d\n", heap->size);
    printf("New root: %d\n", heap->data[0]);

    destroy_heap(heap);
    return 0;
}