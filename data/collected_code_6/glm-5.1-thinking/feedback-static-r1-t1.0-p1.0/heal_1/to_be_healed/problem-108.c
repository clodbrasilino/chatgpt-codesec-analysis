#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int value;
    int array_idx;
    int element_idx;
} HeapNode;

typedef struct {
    HeapNode *data;
    int capacity;
    int size;
} MinHeap;

typedef struct {
    int **arrays;
    int *sizes;
    int num_arrays;
    MinHeap *heap;
} SortedIterator;

void swap_nodes(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up(MinHeap *heap, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap->data[parent].value > heap->data[index].value) {
            swap_nodes(&heap->data[parent], &heap->data[index]);
            index = parent;
        } else {
            break;
        }
    }
}

void heapify_down(MinHeap *heap, int index) {
    /* Possible weaknesses found:
     *  The scope of the variable 'smallest' can be reduced. [variableScope]
     *  The scope of the variable 'left' can be reduced. [variableScope]
     *  The scope of the variable 'right' can be reduced. [variableScope]
     */
    int left, right, smallest;
    while (1) {
        left = 2 * index + 1;
        right = 2 * index + 2;
        smallest = index;
        if (left < heap->size && heap->data[left].value < heap->data[smallest].value) {
            smallest = left;
        }
        if (right < heap->size && heap->data[right].value < heap->data[smallest].value) {
            smallest = right;
        }
        if (smallest != index) {
            swap_nodes(&heap->data[index], &heap->data[smallest]);
            index = smallest;
        } else {
            break;
        }
    }
}

MinHeap *min_heap_create(int capacity) {
    MinHeap *heap = (MinHeap *)malloc(sizeof(MinHeap));
    if (!heap) return NULL;
    heap->data = (HeapNode *)malloc(sizeof(HeapNode) * capacity);
    if (!heap->data) {
        free(heap);
        return NULL;
    }
    heap->capacity = capacity;
    heap->size = 0;
    return heap;
}

void min_heap_destroy(MinHeap *heap) {
    if (heap) {
        free(heap->data);
        free(heap);
    }
}

bool min_heap_push(MinHeap *heap, HeapNode node) {
    if (!heap || heap->size >= heap->capacity) return false;
    heap->data[heap->size] = node;
    heapify_up(heap, heap->size);
    heap->size++;
    return true;
}

bool min_heap_pop(MinHeap *heap, HeapNode *out_node) {
    if (!heap || heap->size == 0) return false;
    *out_node = heap->data[0];
    heap->size--;
    heap->data[0] = heap->data[heap->size];
    heapify_down(heap, 0);
    return true;
}

SortedIterator *sorted_iterator_create(int **arrays, int *sizes, int num_arrays) {
    if (!arrays || !sizes || num_arrays <= 0) return NULL;
    MinHeap *heap = min_heap_create(num_arrays);
    if (!heap) return NULL;
    for (int i = 0; i < num_arrays; i++) {
        if (sizes[i] > 0 && arrays[i]) {
            HeapNode node;
            node.value = arrays[i][0];
            node.array_idx = i;
            node.element_idx = 0;
            if (!min_heap_push(heap, node)) {
                min_heap_destroy(heap);
                return NULL;
            }
        }
    }
    SortedIterator *it = (SortedIterator *)malloc(sizeof(SortedIterator));
    if (!it) {
        min_heap_destroy(heap);
        return NULL;
    }
    it->arrays = arrays;
    it->sizes = sizes;
    it->num_arrays = num_arrays;
    it->heap = heap;
    return it;
}

void sorted_iterator_destroy(SortedIterator *it) {
    if (it) {
        min_heap_destroy(it->heap);
        free(it);
    }
}

bool sorted_iterator_has_next(SortedIterator *it) {
    return it && it->heap && it->heap->size > 0;
}

bool sorted_iterator_next(SortedIterator *it, int *value) {
    if (!it || !it->heap || !value) return false;
    HeapNode current;
    if (!min_heap_pop(it->heap, &current)) return false;
    *value = current.value;
    int next_element_idx = current.element_idx + 1;
    if (next_element_idx < it->sizes[current.array_idx]) {
        HeapNode next_node;
        next_node.value = it->arrays[current.array_idx][next_element_idx];
        next_node.array_idx = current.array_idx;
        next_node.element_idx = next_element_idx;
        min_heap_push(it->heap, next_node);
    }
    return true;
}

int main() {
    int arr1[] = {1, 4, 7, 10};
    int arr2[] = {2, 5, 8};
    int arr3[] = {0, 3, 6, 9, 11};
    int *arrays[] = {arr1, arr2, arr3};
    int sizes[] = {4, 3, 5};
    int num_arrays = 3;
    SortedIterator *it = sorted_iterator_create(arrays, sizes, num_arrays);
    if (!it) {
        return EXIT_FAILURE;
    }
    int val;
    while (sorted_iterator_has_next(it)) {
        if (sorted_iterator_next(it, &val)) {
            printf("%d ", val);
        }
    }
    printf("\n");
    sorted_iterator_destroy(it);
    return EXIT_SUCCESS;
}