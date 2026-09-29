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

static void swap_nodes(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

static int heap_init(MinHeap *heap, int capacity) {
    if (capacity <= 0) {
        return -1;
    }
    heap->nodes = (HeapNode *)malloc(sizeof(HeapNode) * (size_t)capacity);
    if (heap->nodes == NULL) {
        return -1;
    }
    heap->size = 0;
    heap->capacity = capacity;
    return 0;
}

static void heap_free(MinHeap *heap) {
    if (heap != NULL && heap->nodes != NULL) {
        free(heap->nodes);
        heap->nodes = NULL;
        heap->size = 0;
        heap->capacity = 0;
    }
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
    while (idx > 0 && heap->nodes[parent].value > heap->nodes[idx].value) {
        swap_nodes(&heap->nodes[parent], &heap->nodes[idx]);
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
    if (heap->size > 0) {
        heapify_down(heap, 0);
    }
    return top;
}

static HeapNode heap_top(const MinHeap *heap) {
    return heap->nodes[0];
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
    if (heap_init(&heap, num_arrays) != 0) {
        return -1;
    }

    int current_max = INT_MIN;

    for (int i = 0; i < num_arrays; i++) {
        HeapNode node;
        node.value = arrays[i][0];
        node.array_index = i;
        node.element_index = 0;
        if (heap_push(&heap, node) != 0) {
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

        heap_pop(&heap);

        int next_index = min_node.element_index + 1;
        if (next_index >= sizes[min_node.array_index]) {
            break;
        }

        HeapNode next_node;
        next_node.value = arrays[min_node.array_index][next_index];
        next_node.array_index = min_node.array_index;
        next_node.element_index = next_index;

        if (next_node.value > current_max) {
            current_max = next_node.value;
        }

        if (heap_push(&heap, next_node) != 0) {
            heap_free(&heap);
            return -1;
        }
    }

    heap_free(&heap);

    *range_start = best_start;
    *range_end = best_end;
    return 0;
}

int main(void) {
    int arr1[] = {4, 10, 15, 24, 26};
    int arr2[] = {0, 9, 12, 20};
    int arr3[] = {5, 18, 22, 30};

    int *arrays[] = {arr1, arr2, arr3};
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