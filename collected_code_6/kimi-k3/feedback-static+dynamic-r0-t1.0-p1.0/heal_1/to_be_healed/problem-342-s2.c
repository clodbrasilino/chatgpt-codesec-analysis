#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int value;
    int array_index;
    int element_index;
} HeapNode;

typedef struct {
    HeapNode *nodes;
    int size;
    int capacity;
} MinHeap;

static void swap_nodes(HeapNode *a, HeapNode *b)
{
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

static int heap_init(MinHeap *heap, int capacity)
{
    heap->nodes = malloc(sizeof(HeapNode) * capacity);
    if (heap->nodes == NULL) {
        return -1;
    }
    heap->size = 0;
    heap->capacity = capacity;
    return 0;
}

static void heap_free(MinHeap *heap)
{
    free(heap->nodes);
    heap->nodes = NULL;
    heap->size = 0;
    heap->capacity = 0;
}

static void heapify_down(MinHeap *heap, int idx)
{
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

static void heapify_up(MinHeap *heap, int idx)
{
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (heap->nodes[parent].value <= heap->nodes[idx].value) {
            break;
        }
        swap_nodes(&heap->nodes[parent], &heap->nodes[idx]);
        idx = parent;
    }
}

static int heap_push(MinHeap *heap, int value, int array_index, int element_index)
{
    if (heap->size >= heap->capacity) {
        return -1;
    }
    heap->nodes[heap->size].value = value;
    heap->nodes[heap->size].array_index = array_index;
    heap->nodes[heap->size].element_index = element_index;
    heap->size++;
    heapify_up(heap, heap->size - 1);
    return 0;
}

static HeapNode heap_pop(MinHeap *heap)
{
    HeapNode top = heap->nodes[0];
    heap->nodes[0] = heap->nodes[heap->size - 1];
    heap->size--;
    if (heap->size > 0) {
        heapify_down(heap, 0);
    }
    return top;
}

static HeapNode heap_top(const MinHeap *heap)
{
    return heap->nodes[0];
}

int find_smallest_range(int **arrays, const int *sizes, int num_arrays, int *range_start, int *range_end)
{
    if (arrays == NULL || sizes == NULL || num_arrays <= 0 || range_start == NULL || range_end == NULL) {
        return -1;
    }

    for (int i = 0; i < num_arrays; i++) {
        if (arrays[i] == NULL || sizes[i] <= 0) {
            return -1;
        }
    }

    MinHeap heap;
    if (heap_init(&heap, num_arrays) != 0) {
        return -1;
    }

    int current_max = INT_MIN;

    for (int i = 0; i < num_arrays; i++) {
        if (heap_push(&heap, arrays[i][0], i, 0) != 0) {
            heap_free(&heap);
            return -1;
        }
        if (arrays[i][0] > current_max) {
            current_max = arrays[i][0];
        }
    }

    int best_start = 0;
    int best_end = INT_MAX;

    while (1) {
        HeapNode min_node = heap_top(&heap);
        int current_min = min_node.value;

        if (current_max - current_min < best_end - best_start) {
            best_start = current_min;
            best_end = current_max;
        }

        int arr_idx = min_node.array_index;
        int next_elem_idx = min_node.element_index + 1;

        if (next_elem_idx >= sizes[arr_idx]) {
            break;
        }

        heap_pop(&heap);
        int next_value = arrays[arr_idx][next_elem_idx];
        if (heap_push(&heap, next_value, arr_idx, next_elem_idx) != 0) {
            heap_free(&heap);
            return -1;
        }
        if (next_value > current_max) {
            current_max = next_value;
        }
    }

    *range_start = best_start;
    *range_end = best_end;
    heap_free(&heap);
    return 0;
}

int main(void)
{
    int arr1[] = {4, 10, 15, 24, 26};
    int arr2[] = {0, 9, 12, 20};
    int arr3[] = {5, 18, 22, 30};

    int *arrays[] = {arr1, arr2, arr3};
    /* Possible weaknesses found:
     *  Variable 'sizes' can be declared as const array [constVariable]
     */
    int sizes[] = {5, 4, 3};
    int num_arrays = 3;

    int range_start, range_end;
    if (find_smallest_range(arrays, sizes, num_arrays, &range_start, &range_end) == 0) {
        printf("Smallest range: [%d, %d]\n", range_start, range_end);
    } else {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}