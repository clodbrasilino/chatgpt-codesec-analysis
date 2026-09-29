#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int list_index;
} HeapNode;

typedef struct {
    HeapNode *data;
    int capacity;
    int size;
} MinHeap;

typedef struct {
    int **lists;
    int *list_sizes;
    int num_lists;
    MinHeap *heap;
    int *current_indices;
} SortedIterator;

MinHeap* create_heap(int capacity) {
    MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
    if (!heap) return NULL;
    heap->data = (HeapNode*)malloc(capacity * sizeof(HeapNode));
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

void swap(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_up(MinHeap *heap, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap->data[index].value >= heap->data[parent].value) break;
        swap(&heap->data[index], &heap->data[parent]);
        index = parent;
    }
}

void heapify_down(MinHeap *heap, int index) {
    while (1) {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        if (left < heap->size && heap->data[left].value < heap->data[smallest].value) {
            smallest = left;
        }
        if (right < heap->size && heap->data[right].value < heap->data[smallest].value) {
            smallest = right;
        }
        if (smallest == index) break;
        swap(&heap->data[index], &heap->data[smallest]);
        index = smallest;
    }
}

int push_heap(MinHeap *heap, HeapNode node) {
    if (!heap || heap->size >= heap->capacity) return -1;
    heap->data[heap->size] = node;
    heapify_up(heap, heap->size);
    heap->size++;
    return 0;
}

int pop_heap(MinHeap *heap, HeapNode *out) {
    if (!heap || heap->size == 0) return -1;
    *out = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    heapify_down(heap, 0);
    return 0;
}

SortedIterator* create_iterator(int **lists, int *list_sizes, int num_lists) {
    if (!lists || !list_sizes || num_lists <= 0) return NULL;
    
    SortedIterator *it = (SortedIterator*)malloc(sizeof(SortedIterator));
    if (!it) return NULL;
    
    it->lists = lists;
    it->list_sizes = list_sizes;
    it->num_lists = num_lists;
    it->current_indices = (int*)calloc(num_lists, sizeof(int));
    if (!it->current_indices) {
        free(it);
        return NULL;
    }
    
    it->heap = create_heap(num_lists);
    if (!it->heap) {
        free(it->current_indices);
        free(it);
        return NULL;
    }
    
    for (int i = 0; i < num_lists; i++) {
        if (list_sizes[i] > 0) {
            HeapNode node;
            node.value = lists[i][0];
            node.list_index = i;
            push_heap(it->heap, node);
            it->current_indices[i] = 1;
        }
    }
    
    return it;
}

int has_next(SortedIterator *it) {
    if (!it || !it->heap) return 0;
    return it->heap->size > 0;
}

int next(SortedIterator *it, int *value) {
    if (!it || !it->heap) return -1;
    
    HeapNode current;
    if (pop_heap(it->heap, &current) != 0) return -1;
    
    *value = current.value;
    
    int list_idx = current.list_index;
    if (it->current_indices[list_idx] < it->list_sizes[list_idx]) {
        HeapNode next_node;
        next_node.value = it->lists[list_idx][it->current_indices[list_idx]];
        next_node.list_index = list_idx;
        push_heap(it->heap, next_node);
        it->current_indices[list_idx]++;
    }
    
    return 0;
}

void destroy_iterator(SortedIterator *it) {
    if (it) {
        destroy_heap(it->heap);
        free(it->current_indices);
        free(it);
    }
}

int main() {
    int list1[] = {1, 4, 7, 10};
    int list2[] = {2, 5, 8};
    int list3[] = {3, 6, 9, 11, 12};
    
    int *lists[] = {list1, list2, list3};
    int list_sizes[] = {4, 3, 5};
    int num_lists = 3;
    
    SortedIterator *it = create_iterator(lists, list_sizes, num_lists);
    if (!it) {
        return 1;
    }
    
    while (has_next(it)) {
        int val;
        if (next(it, &val) == 0) {
            printf("%d ", val);
        }
    }
    printf("\n");
    
    destroy_iterator(it);
    
    return 0;
}