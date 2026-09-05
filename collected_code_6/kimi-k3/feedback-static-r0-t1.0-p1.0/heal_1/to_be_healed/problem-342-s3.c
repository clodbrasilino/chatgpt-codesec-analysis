#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int value;
    int array_idx;
    int element_idx;
} HeapNode;

typedef struct {
    HeapNode *nodes;
    int size;
    int capacity;
} MinHeap;

static void swap_nodes(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

static void heapify_down(MinHeap *heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->nodes[left].value < heap->nodes[smallest].value) {
        smallest = left;
    }
    if (right < heap->size && heap->nodes[right].value < heap->nodes[smallest].value) {
        smallest = right;
    }
    if (smallest != idx) {
        swap_nodes(&heap->nodes[idx], &heap->nodes[smallest]);
        heapify_down(heap, smallest);
    }
}

static void heapify_up(MinHeap *heap, int idx) {
    int parent = (idx - 1) / 2;
    while (idx > 0 && heap->nodes[idx].value < heap->nodes[parent].value) {
        swap_nodes(&heap->nodes[idx], &heap->nodes[parent]);
        idx = parent;
        parent = (idx - 1) / 2;
    }
}

static int heap_push(MinHeap *heap, HeapNode node) {
    if (heap->size >= heap->capacity) {
        return -1;
    }
    heap->nodes[heap->size] = node;
    heapify_up(heap, heap->size);
    heap->size++;
    return 0;
}

static HeapNode heap_pop(MinHeap *heap) {
    HeapNode top = heap->nodes[0];
    heap->nodes[0] = heap->nodes[heap->size - 1];
    heap->size--;
    heapify_down(heap, 0);
    return top;
}

static void heap_replace_top(MinHeap *heap, HeapNode node) {
    heap->nodes[0] = node;
    heapify_down(heap, 0);
}

int find_smallest_range(int **arrays, const int *sizes, int num_arrays, int *range_start, int *range_end) {
    if (arrays == NULL || sizes == NULL || num_arrays <= 0 || range_start == NULL || range_end == NULL) {
        return -1;
    }
    for (int i = 0; i < num_arrays; i++) {
        if (arrays[i] == NULL || sizes[i] <= 0) {
            return -1;
        }
    }

    MinHeap heap;
    heap.capacity = num_arrays;
    heap.size = 0;
    heap.nodes = (HeapNode *)malloc((size_t)num_arrays * sizeof(HeapNode));
    if (heap.nodes == NULL) {
        return -1;
    }

    int current_max = INT_MIN;
    for (int i = 0; i < num_arrays; i++) {
        HeapNode node;
        node.value = arrays[i][0];
        node.array_idx = i;
        node.element_idx = 0;
        if (heap_push(&heap, node) != 0) {
            free(heap.nodes);
            return -1;
        }
        if (arrays[i][0] > current_max) {
            current_max = arrays[i][0];
        }
    }

    int best_start = 0;
    int best_end = INT_MAX;
    long long best_range = (long long)INT_MAX;

    while (1) {
        HeapNode min_node = heap.nodes[0];
        long long current_range = (long long)current_max - (long long)min_node.value;

        if (current_range < best_range) {
            best_range = current_range;
            best_start = min_node.value;
            best_end = current_max;
        }

        int next_idx = min_node.element_idx + 1;
        if (next_idx >= sizes[min_node.array_idx]) {
            break;
        }

        HeapNode next_node;
        next_node.value = arrays[min_node.array_idx][next_idx];
        next_node.array_idx = min_node.array_idx;
        next_node.element_idx = next_idx;

        if (next_node.value > current_max) {
            current_max = next_node.value;
        }

        heap_replace_top(&heap, next_node);
    }

    *range_start = best_start;
    *range_end = best_end;
    free(heap.nodes);
    return 0;
}

int main(void) {
    int arr1[] = {4, 10, 15, 24, 26};
    int arr2[] = {0, 9, 12, 20};
    int arr3[] = {5, 18, 22, 30};

    int *arrays[] = {arr1, arr2, arr3};
    /* Possible weaknesses found:
     *  Variable 'sizes' can be declared as const array [constVariable]
     */
    int sizes[] = {5, 4, 3};
    int num_arrays = 3;

    int range_start = 0;
    int range_end = 0;

    if (find_smallest_range(arrays, sizes, num_arrays, &range_start, &range_end) != 0) {
        fprintf(stderr, "Error: invalid input or memory allocation failure\n");
        return EXIT_FAILURE;
    }

    printf("Smallest range: [%d, %d]\n", range_start, range_end);
    return EXIT_SUCCESS;
}