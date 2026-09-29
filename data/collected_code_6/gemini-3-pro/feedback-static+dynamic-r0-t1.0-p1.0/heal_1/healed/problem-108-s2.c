#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct {
    int* data;
    size_t size;
    size_t index;
} SortedArray;

typedef struct {
    int value;
    size_t array_index;
} HeapNode;

typedef struct {
    HeapNode* nodes;
    size_t size;
    size_t capacity;
} MinHeap;

MinHeap* create_heap(size_t capacity) {
    if (capacity == 0) return NULL;
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    if (!heap) return NULL;
    heap->nodes = (HeapNode*)malloc(sizeof(HeapNode) * capacity);
    if (!heap->nodes) {
        free(heap);
        return NULL;
    }
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void destroy_heap(MinHeap* heap) {
    if (heap) {
        free(heap->nodes);
        free(heap);
    }
}

void swap_nodes(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void min_heapify(MinHeap* heap, size_t idx) {
    size_t smallest = idx;
    size_t left = 2 * idx + 1;
    size_t right = 2 * idx + 2;

    if (left < heap->size && heap->nodes[left].value < heap->nodes[smallest].value)
        smallest = left;

    if (right < heap->size && heap->nodes[right].value < heap->nodes[smallest].value)
        smallest = right;

    if (smallest != idx) {
        swap_nodes(&heap->nodes[idx], &heap->nodes[smallest]);
        min_heapify(heap, smallest);
    }
}

bool insert_heap(MinHeap* heap, HeapNode node) {
    if (heap->size == heap->capacity) return false;
    size_t i = heap->size++;
    heap->nodes[i] = node;
    while (i != 0 && heap->nodes[(i - 1) / 2].value > heap->nodes[i].value) {
        swap_nodes(&heap->nodes[i], &heap->nodes[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
    return true;
}

bool extract_min(MinHeap* heap, HeapNode* min_node) {
    if (heap->size == 0) return false;
    if (heap->size == 1) {
        heap->size--;
        *min_node = heap->nodes[0];
        return true;
    }
    *min_node = heap->nodes[0];
    heap->nodes[0] = heap->nodes[heap->size - 1];
    heap->size--;
    min_heapify(heap, 0);
    return true;
}

void merge_sorted_arrays(SortedArray* arrays, size_t num_arrays) {
    if (!arrays || num_arrays == 0) return;

    MinHeap* heap = create_heap(num_arrays);
    if (!heap) {
        fprintf(stderr, "Failed to create heap\n");
        return;
    }

    for (size_t i = 0; i < num_arrays; i++) {
        if (arrays[i].size > 0 && arrays[i].data != NULL) {
            HeapNode node;
            node.value = arrays[i].data[0];
            node.array_index = i;
            arrays[i].index = 1;
            insert_heap(heap, node);
        }
    }

    HeapNode current_min;
    while (extract_min(heap, &current_min)) {
        printf("%d ", current_min.value);
        
        size_t array_idx = current_min.array_index;
        if (arrays[array_idx].index < arrays[array_idx].size) {
            HeapNode next_node;
            next_node.value = arrays[array_idx].data[arrays[array_idx].index++];
            next_node.array_index = array_idx;
            insert_heap(heap, next_node);
        }
    }
    printf("\n");

    destroy_heap(heap);
}

int main() {
    int arr1[] = {1, 4, 7, 10};
    int arr2[] = {2, 5, 8, 11};
    int arr3[] = {3, 6, 9, 12};

    SortedArray arrays[3];
    arrays[0].data = arr1;
    arrays[0].size = sizeof(arr1) / sizeof(arr1[0]);
    arrays[0].index = 0;

    arrays[1].data = arr2;
    arrays[1].size = sizeof(arr2) / sizeof(arr2[0]);
    arrays[1].index = 0;

    arrays[2].data = arr3;
    arrays[2].size = sizeof(arr3) / sizeof(arr3[0]);
    arrays[2].index = 0;

    merge_sorted_arrays(arrays, 3);

    return 0;
}