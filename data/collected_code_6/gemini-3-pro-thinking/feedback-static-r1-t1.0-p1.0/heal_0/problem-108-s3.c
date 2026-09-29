#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int value;
    size_t array_idx;
    size_t element_idx;
} HeapNode;

typedef struct {
    HeapNode *data;
    size_t size;
    size_t capacity;
} MinHeap;

typedef struct {
    const int **arrays;
    const size_t *sizes;
    size_t num_arrays;
    MinHeap *heap;
} SortedIterator;

static void swap_nodes(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

static void min_heapify(MinHeap *heap, size_t idx) {
    size_t smallest = idx;
    size_t left = 2 * idx + 1;
    size_t right = 2 * idx + 2;

    if (left < heap->size && heap->data[left].value < heap->data[smallest].value) {
        smallest = left;
    }
    if (right < heap->size && heap->data[right].value < heap->data[smallest].value) {
        smallest = right;
    }
    if (smallest != idx) {
        swap_nodes(&heap->data[idx], &heap->data[smallest]);
        min_heapify(heap, smallest);
    }
}

static bool push_heap(MinHeap *heap, HeapNode node) {
    if (heap->size == heap->capacity) {
        return false;
    }
    
    size_t i = heap->size;
    heap->size++;
    heap->data[i] = node;

    while (i != 0 && heap->data[(i - 1) / 2].value > heap->data[i].value) {
        swap_nodes(&heap->data[i], &heap->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
    return true;
}

static bool pop_heap(MinHeap *heap, HeapNode *out_node) {
    if (heap->size == 0) {
        return false;
    }
    if (out_node) {
        *out_node = heap->data[0];
    }
    heap->size--;
    if (heap->size > 0) {
        heap->data[0] = heap->data[heap->size];
        min_heapify(heap, 0);
    }
    return true;
}

static MinHeap* create_heap(size_t capacity) {
    MinHeap *heap = malloc(sizeof(MinHeap));
    if (!heap) {
        return NULL;
    }
    
    heap->data = malloc(capacity * sizeof(HeapNode));
    if (!heap->data) {
        free(heap);
        return NULL;
    }
    
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

static void destroy_heap(MinHeap *heap) {
    if (heap) {
        free(heap->data);
        free(heap);
    }
}

SortedIterator* create_iterator(const int **arrays, const size_t *sizes, size_t num_arrays) {
    if (!arrays || !sizes || num_arrays == 0) {
        return NULL;
    }

    SortedIterator *iter = malloc(sizeof(SortedIterator));
    if (!iter) {
        return NULL;
    }

    iter->arrays = arrays;
    iter->sizes = sizes;
    iter->num_arrays = num_arrays;
    iter->heap = create_heap(num_arrays);

    if (!iter->heap) {
        free(iter);
        return NULL;
    }

    for (size_t i = 0; i < num_arrays; ++i) {
        if (sizes[i] > 0) {
            HeapNode node = {arrays[i][0], i, 0};
            if (!push_heap(iter->heap, node)) {
                destroy_heap(iter->heap);
                free(iter);
                return NULL;
            }
        }
    }

    return iter;
}

bool has_next(const SortedIterator *iter) {
    return iter != NULL && iter->heap->size > 0;
}

bool get_next(SortedIterator *iter, int *out_value) {
    if (!has_next(iter) || !out_value) {
        return false;
    }

    HeapNode min_node;
    if (!pop_heap(iter->heap, &min_node)) {
        return false;
    }
    
    *out_value = min_node.value;

    size_t next_element_idx = min_node.element_idx + 1;
    if (next_element_idx < iter->sizes[min_node.array_idx]) {
        HeapNode next_node = {
            iter->arrays[min_node.array_idx][next_element_idx],
            min_node.array_idx,
            next_element_idx
        };
        if (!push_heap(iter->heap, next_node)) {
            return false;
        }
    }

    return true;
}

void destroy_iterator(SortedIterator *iter) {
    if (iter) {
        destroy_heap(iter->heap);
        free(iter);
    }
}

int main(void) {
    const int arr1[] = {1, 4, 7, 10};
    const int arr2[] = {2, 5, 8};
    const int arr3[] = {3, 6, 9, 11, 12};
    const int arr4[] = {0, 15};

    const int *arrays[] = {arr1, arr2, arr3, arr4};
    const size_t sizes[] = {
        sizeof(arr1) / sizeof(arr1[0]),
        sizeof(arr2) / sizeof(arr2[0]),
        sizeof(arr3) / sizeof(arr3[0]),
        sizeof(arr4) / sizeof(arr4[0])
    };

    size_t num_arrays = sizeof(arrays) / sizeof(arrays[0]);

    SortedIterator *iter = create_iterator(arrays, sizes, num_arrays);
    if (!iter) {
        fprintf(stderr, "Failed to initialize sorted iterator\n");
        return EXIT_FAILURE;
    }

    int value = 0;
    while (has_next(iter)) {
        if (get_next(iter, &value)) {
            printf("%d ", value);
        } else {
            fprintf(stderr, "\nError retrieving next value\n");
            destroy_iterator(iter);
            return EXIT_FAILURE;
        }
    }
    printf("\n");

    destroy_iterator(iter);
    return EXIT_SUCCESS;
}