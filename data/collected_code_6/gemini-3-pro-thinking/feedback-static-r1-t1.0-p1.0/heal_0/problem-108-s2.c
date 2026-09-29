#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    int value;
    size_t array_idx;
    size_t element_idx;
} HeapNode;

typedef struct {
    HeapNode *nodes;
    size_t size;
    size_t capacity;
} MinHeap;

typedef struct {
    const int **arrays;
    const size_t *sizes;
    size_t num_arrays;
    MinHeap *heap;
} MergeIterator;

static void swap_nodes(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

static bool heap_push(MinHeap *heap, HeapNode node) {
    if (!heap || !heap->nodes) {
        return false;
    }
    if (heap->size >= heap->capacity) {
        return false;
    }

    size_t i = heap->size;
    heap->nodes[i] = node;
    heap->size++;

    while (i > 0) {
        size_t parent = (i - 1) / 2;
        if (heap->nodes[i].value < heap->nodes[parent].value) {
            swap_nodes(&heap->nodes[i], &heap->nodes[parent]);
            i = parent;
        } else {
            break;
        }
    }
    return true;
}

static bool heap_pop(MinHeap *heap, HeapNode *out_node) {
    if (!heap || !heap->nodes || heap->size == 0 || !out_node) {
        return false;
    }

    *out_node = heap->nodes[0];
    heap->size--;

    if (heap->size > 0) {
        heap->nodes[0] = heap->nodes[heap->size];
        size_t i = 0;
        
        while (true) {
            size_t left = 2 * i + 1;
            size_t right = 2 * i + 2;
            size_t smallest = i;

            if (left < heap->size && heap->nodes[left].value < heap->nodes[smallest].value) {
                smallest = left;
            }
            if (right < heap->size && heap->nodes[right].value < heap->nodes[smallest].value) {
                smallest = right;
            }

            if (smallest != i) {
                swap_nodes(&heap->nodes[i], &heap->nodes[smallest]);
                i = smallest;
            } else {
                break;
            }
        }
    }
    return true;
}

static void free_iterator(MergeIterator *iter) {
    if (iter) {
        if (iter->heap) {
            free(iter->heap->nodes);
            free(iter->heap);
        }
        free(iter);
    }
}

static MergeIterator* create_iterator(const int **arrays, const size_t *sizes, size_t num_arrays) {
    if (!arrays || !sizes || num_arrays == 0) {
        return NULL;
    }

    MergeIterator *iter = malloc(sizeof(MergeIterator));
    if (!iter) {
        return NULL;
    }

    iter->arrays = arrays;
    iter->sizes = sizes;
    iter->num_arrays = num_arrays;

    iter->heap = malloc(sizeof(MinHeap));
    if (!iter->heap) {
        free(iter);
        return NULL;
    }

    iter->heap->capacity = num_arrays;
    iter->heap->size = 0;
    iter->heap->nodes = malloc(sizeof(HeapNode) * num_arrays);

    if (!iter->heap->nodes) {
        free(iter->heap);
        free(iter);
        return NULL;
    }

    for (size_t i = 0; i < num_arrays; i++) {
        if (sizes[i] > 0 && arrays[i]) {
            HeapNode node = { arrays[i][0], i, 0 };
            heap_push(iter->heap, node);
        }
    }

    return iter;
}

static bool iterator_next(MergeIterator *iter, int *out_value) {
    if (!iter || !out_value) {
        return false;
    }

    HeapNode min_node;
    if (!heap_pop(iter->heap, &min_node)) {
        return false;
    }

    *out_value = min_node.value;

    size_t arr_idx = min_node.array_idx;
    size_t next_elem_idx = min_node.element_idx + 1;

    if (next_elem_idx < iter->sizes[arr_idx]) {
        HeapNode new_node = { iter->arrays[arr_idx][next_elem_idx], arr_idx, next_elem_idx };
        heap_push(iter->heap, new_node);
    }

    return true;
}

int main(void) {
    const int arr1[] = {1, 5, 9, 15};
    const int arr2[] = {2, 3, 10};
    const int arr3[] = {4, 6, 7, 8, 12};

    const int *arrays[] = {arr1, arr2, arr3};
    const size_t sizes[] = {
        sizeof(arr1) / sizeof(arr1[0]),
        sizeof(arr2) / sizeof(arr2[0]),
        sizeof(arr3) / sizeof(arr3[0])
    };

    size_t num_arrays = sizeof(arrays) / sizeof(arrays[0]);

    MergeIterator *iter = create_iterator(arrays, sizes, num_arrays);
    if (!iter) {
        return EXIT_FAILURE;
    }

    int val = 0;
    while (iterator_next(iter, &val)) {
        printf("%d ", val);
    }
    printf("\n");

    free_iterator(iter);

    return EXIT_SUCCESS;
}