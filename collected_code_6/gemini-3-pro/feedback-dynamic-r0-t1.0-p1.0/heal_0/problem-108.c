#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    int value;
    size_t array_idx;
    size_t element_idx;
} HeapNode;

typedef struct {
    HeapNode* nodes;
    size_t capacity;
    size_t size;
} MinHeap;

typedef struct {
    int** arrays;
    size_t* sizes;
    size_t num_arrays;
    MinHeap* heap;
} MergedIterator;

static bool heap_init(MinHeap* heap, size_t capacity) {
    heap->nodes = (HeapNode*)malloc(capacity * sizeof(HeapNode));
    if (!heap->nodes) {
        return false;
    }
    heap->capacity = capacity;
    heap->size = 0;
    return true;
}

static void heap_free(MinHeap* heap) {
    if (heap) {
        free(heap->nodes);
        heap->nodes = NULL;
        heap->capacity = 0;
        heap->size = 0;
    }
}

static void heap_swap(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

static void heapify_down(MinHeap* heap, size_t idx) {
    size_t smallest = idx;
    size_t left = 2 * idx + 1;
    size_t right = 2 * idx + 2;

    if (left < heap->size && heap->nodes[left].value < heap->nodes[smallest].value) {
        smallest = left;
    }

    if (right < heap->size && heap->nodes[right].value < heap->nodes[smallest].value) {
        smallest = right;
    }

    if (smallest != idx) {
        heap_swap(&heap->nodes[idx], &heap->nodes[smallest]);
        heapify_down(heap, smallest);
    }
}

static void heapify_up(MinHeap* heap, size_t idx) {
    while (idx > 0) {
        size_t parent = (idx - 1) / 2;
        if (heap->nodes[idx].value >= heap->nodes[parent].value) {
            break;
        }
        heap_swap(&heap->nodes[idx], &heap->nodes[parent]);
        idx = parent;
    }
}

static bool heap_push(MinHeap* heap, HeapNode node) {
    if (heap->size >= heap->capacity) {
        return false;
    }
    heap->nodes[heap->size] = node;
    heapify_up(heap, heap->size);
    heap->size++;
    return true;
}

static bool heap_pop(MinHeap* heap, HeapNode* out_node) {
    if (heap->size == 0) {
        return false;
    }
    *out_node = heap->nodes[0];
    heap->nodes[0] = heap->nodes[heap->size - 1];
    heap->size--;
    heapify_down(heap, 0);
    return true;
}

MergedIterator* iterator_create(int** arrays, size_t* sizes, size_t num_arrays) {
    if (!arrays || !sizes || num_arrays == 0) {
        return NULL;
    }

    MergedIterator* iter = (MergedIterator*)malloc(sizeof(MergedIterator));
    if (!iter) {
        return NULL;
    }

    iter->arrays = arrays;
    iter->sizes = sizes;
    iter->num_arrays = num_arrays;
    
    iter->heap = (MinHeap*)malloc(sizeof(MinHeap));
    if (!iter->heap) {
        free(iter);
        return NULL;
    }

    if (!heap_init(iter->heap, num_arrays)) {
        free(iter->heap);
        free(iter);
        return NULL;
    }

    for (size_t i = 0; i < num_arrays; i++) {
        if (sizes[i] > 0 && arrays[i]) {
            HeapNode node = {arrays[i][0], i, 0};
            heap_push(iter->heap, node);
        }
    }

    return iter;
}

bool iterator_next(MergedIterator* iter, int* out_value) {
    if (!iter || !out_value || iter->heap->size == 0) {
        return false;
    }

    HeapNode min_node;
    if (!heap_pop(iter->heap, &min_node)) {
        return false;
    }

    *out_value = min_node.value;

    size_t arr_idx = min_node.array_idx;
    size_t elem_idx = min_node.element_idx + 1;

    if (elem_idx < iter->sizes[arr_idx]) {
        HeapNode next_node = {iter->arrays[arr_idx][elem_idx], arr_idx, elem_idx};
        heap_push(iter->heap, next_node);
    }

    return true;
}

void iterator_destroy(MergedIterator* iter) {
    if (iter) {
        if (iter->heap) {
            heap_free(iter->heap);
            free(iter->heap);
        }
        free(iter);
    }
}

int main(void) {
    int arr1[] = {1, 4, 7};
    int arr2[] = {2, 5, 8};
    int arr3[] = {3, 6, 9};

    int* arrays[] = {arr1, arr2, arr3};
    size_t sizes[] = {3, 3, 3};
    size_t num_arrays = 3;

    MergedIterator* iter = iterator_create(arrays, sizes, num_arrays);
    if (!iter) {
        return EXIT_FAILURE;
    }

    int value;
    while (iterator_next(iter, &value)) {
        printf("%d ", value);
    }
    printf("\n");

    iterator_destroy(iter);
    return EXIT_SUCCESS;
}