#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int list_index;
    int element_index;
} HeapNode;

typedef struct {
    HeapNode *data;
    int capacity;
    int size;
} MinHeap;

MinHeap *create_heap(int capacity) {
    MinHeap *heap = (MinHeap *)malloc(sizeof(MinHeap));
    if (!heap) return NULL;
    heap->data = (HeapNode *)malloc(capacity * sizeof(HeapNode));
    if (!heap->data) {
        free(heap);
        return NULL;
    }
    heap->capacity = capacity;
    heap->size = 0;
    return heap;
}

void destroy_heap(MinHeap *heap) {
    if (heap) {
        free(heap->data);
        free(heap);
    }
}

void swap_nodes(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void heap_push(MinHeap *heap, HeapNode node) {
    if (heap->size >= heap->capacity) return;
    heap->data[heap->size] = node;
    int current = heap->size;
    heap->size++;
    while (current > 0) {
        int parent = (current - 1) / 2;
        if (heap->data[current].value < heap->data[parent].value) {
            swap_nodes(&heap->data[current], &heap->data[parent]);
            current = parent;
        } else {
            break;
        }
    }
}

HeapNode heap_pop(MinHeap *heap) {
    HeapNode empty = {0, -1, -1};
    if (heap->size == 0) return empty;
    HeapNode root = heap->data[0];
    heap->size--;
    if (heap->size > 0) {
        heap->data[0] = heap->data[heap->size];
        int current = 0;
        while (1) {
            int left = 2 * current + 1;
            int right = 2 * current + 2;
            int smallest = current;
            if (left < heap->size && heap->data[left].value < heap->data[smallest].value) {
                smallest = left;
            }
            if (right < heap->size && heap->data[right].value < heap->data[smallest].value) {
                smallest = right;
            }
            if (smallest != current) {
                swap_nodes(&heap->data[current], &heap->data[smallest]);
                current = smallest;
            } else {
                break;
            }
        }
    }
    return root;
}

typedef struct {
    int **lists;
    int *list_sizes;
    int num_lists;
    MinHeap *heap;
} SortedIterator;

SortedIterator *create_iterator(int **lists, int *list_sizes, int num_lists) {
    SortedIterator *it = (SortedIterator *)malloc(sizeof(SortedIterator));
    if (!it) return NULL;
    it->heap = create_heap(num_lists);
    if (!it->heap) {
        free(it);
        return NULL;
    }
    it->lists = lists;
    it->list_sizes = list_sizes;
    it->num_lists = num_lists;
    for (int i = 0; i < num_lists; i++) {
        if (list_sizes[i] > 0) {
            HeapNode node;
            node.value = lists[i][0];
            node.list_index = i;
            node.element_index = 0;
            heap_push(it->heap, node);
        }
    }
    return it;
}

int iterator_has_next(SortedIterator *it) {
    if (!it || !it->heap) return 0;
    return it->heap->size > 0;
}

int iterator_next(SortedIterator *it) {
    if (!iterator_has_next(it)) return -1;
    HeapNode node = heap_pop(it->heap);
    int value = node.value;
    if (node.element_index + 1 < it->list_sizes[node.list_index]) {
        HeapNode next_node;
        next_node.list_index = node.list_index;
        next_node.element_index = node.element_index + 1;
        next_node.value = it->lists[next_node.list_index][next_node.element_index];
        heap_push(it->heap, next_node);
    }
    return value;
}

void destroy_iterator(SortedIterator *it) {
    if (it) {
        destroy_heap(it->heap);
        free(it);
    }
}

int main() {
    int list1[] = {1, 4, 7};
    int list2[] = {2, 5, 8, 11};
    int list3[] = {3, 6, 9, 10, 12};
    int *lists[] = {list1, list2, list3};
    int list_sizes[] = {3, 4, 5};
    int num_lists = 3;
    SortedIterator *it = create_iterator(lists, list_sizes, num_lists);
    if (!it) return 1;
    while (iterator_has_next(it)) {
        printf("%d ", iterator_next(it));
    }
    printf("\n");
    destroy_iterator(it);
    return 0;
}