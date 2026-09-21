#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
    size_t index;
} SortedInput;

typedef struct {
    int value;
    size_t input_index;
} HeapNode;

typedef struct {
    HeapNode *nodes;
    size_t size;
    size_t capacity;
} MinHeap;

MinHeap* create_min_heap(size_t capacity) {
    MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
    if (!heap) return NULL;
    heap->nodes = (HeapNode*)malloc(capacity * sizeof(HeapNode));
    if (!heap->nodes) {
        free(heap);
        return NULL;
    }
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void destroy_min_heap(MinHeap *heap) {
    if (heap) {
        free(heap->nodes);
        free(heap);
    }
}

void swap_nodes(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void min_heapify(MinHeap *heap, size_t idx) {
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

int insert_min_heap(MinHeap *heap, HeapNode node) {
    if (heap->size == heap->capacity) return -1;

    size_t i = heap->size++;
    heap->nodes[i] = node;

    while (i != 0 && heap->nodes[(i - 1) / 2].value > heap->nodes[i].value) {
        swap_nodes(&heap->nodes[i], &heap->nodes[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
    return 0;
}

int extract_min(MinHeap *heap, HeapNode *min_node) {
    if (heap->size == 0) return -1;
    if (heap->size == 1) {
        heap->size--;
        *min_node = heap->nodes[0];
        return 0;
    }

    *min_node = heap->nodes[0];
    heap->nodes[0] = heap->nodes[heap->size - 1];
    heap->size--;
    min_heapify(heap, 0);

    return 0;
}

typedef struct {
    SortedInput *inputs;
    size_t num_inputs;
    MinHeap *heap;
} SortedIterator;

SortedIterator* create_sorted_iterator(SortedInput *inputs, size_t num_inputs) {
    SortedIterator *iter = (SortedIterator*)malloc(sizeof(SortedIterator));
    if (!iter) return NULL;

    iter->inputs = inputs;
    iter->num_inputs = num_inputs;
    iter->heap = create_min_heap(num_inputs);

    if (!iter->heap) {
        free(iter);
        return NULL;
    }

    for (size_t i = 0; i < num_inputs; i++) {
        if (inputs[i].size > 0) {
            HeapNode node = {inputs[i].data[0], i};
            inputs[i].index = 1;
            insert_min_heap(iter->heap, node);
        }
    }

    return iter;
}

void destroy_sorted_iterator(SortedIterator *iter) {
    if (iter) {
        destroy_min_heap(iter->heap);
        free(iter);
    }
}

int next_sorted_element(SortedIterator *iter, int *value) {
    HeapNode min_node;
    if (extract_min(iter->heap, &min_node) != 0) {
        return 0;
    }

    *value = min_node.value;
    size_t input_idx = min_node.input_index;

    if (iter->inputs[input_idx].index < iter->inputs[input_idx].size) {
        HeapNode next_node = {
            iter->inputs[input_idx].data[iter->inputs[input_idx].index],
            input_idx
        };
        iter->inputs[input_idx].index++;
        insert_min_heap(iter->heap, next_node);
    }

    return 1;
}

int main(void) {
    int arr1[] = {1, 4, 7};
    int arr2[] = {2, 5, 8};
    int arr3[] = {3, 6, 9};

    SortedInput inputs[3] = {
        {arr1, 3, 0},
        {arr2, 3, 0},
        {arr3, 3, 0}
    };

    SortedIterator *iter = create_sorted_iterator(inputs, 3);
    if (!iter) {
        fprintf(stderr, "Failed to create iterator\n");
        return EXIT_FAILURE;
    }

    int value;
    while (next_sorted_element(iter, &value)) {
        printf("%d ", value);
    }
    printf("\n");

    destroy_sorted_iterator(iter);
    return EXIT_SUCCESS;
}