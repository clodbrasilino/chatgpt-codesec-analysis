#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int value;
    int array_idx;
    int element_idx;
} HeapNode;

typedef struct {
    HeapNode* data;
    int size;
    int capacity;
} MinHeap;

typedef struct {
    int** arrays;
    int* sizes;
    int num_arrays;
    MinHeap* heap;
} SortedIterator;

MinHeap* create_min_heap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    if (!heap) return NULL;
    heap->data = (HeapNode*)malloc(capacity * sizeof(HeapNode));
    if (!heap->data) {
        free(heap);
        return NULL;
    }
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void destroy_min_heap(MinHeap* heap) {
    if (heap) {
        free(heap->data);
        free(heap);
    }
}

void swap(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void min_heapify(MinHeap* heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->data[left].value < heap->data[smallest].value)
        smallest = left;

    if (right < heap->size && heap->data[right].value < heap->data[smallest].value)
        smallest = right;

    if (smallest != idx) {
        swap(&heap->data[idx], &heap->data[smallest]);
        min_heapify(heap, smallest);
    }
}

bool insert_min_heap(MinHeap* heap, HeapNode node) {
    if (heap->size == heap->capacity) return false;

    int i = heap->size++;
    heap->data[i] = node;

    while (i != 0 && heap->data[(i - 1) / 2].value > heap->data[i].value) {
        swap(&heap->data[i], &heap->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
    return true;
}

bool extract_min(MinHeap* heap, HeapNode* min_node) {
    if (heap->size <= 0) return false;
    if (heap->size == 1) {
        heap->size--;
        *min_node = heap->data[0];
        return true;
    }

    *min_node = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    min_heapify(heap, 0);
    return true;
}

SortedIterator* create_sorted_iterator(int** arrays, int* sizes, int num_arrays) {
    SortedIterator* iter = (SortedIterator*)malloc(sizeof(SortedIterator));
    if (!iter) return NULL;

    iter->arrays = arrays;
    iter->sizes = sizes;
    iter->num_arrays = num_arrays;
    iter->heap = create_min_heap(num_arrays);

    if (!iter->heap) {
        free(iter);
        return NULL;
    }

    for (int i = 0; i < num_arrays; i++) {
        if (sizes[i] > 0) {
            HeapNode node = {arrays[i][0], i, 0};
            insert_min_heap(iter->heap, node);
        }
    }
    return iter;
}

void destroy_sorted_iterator(SortedIterator* iter) {
    if (iter) {
        destroy_min_heap(iter->heap);
        free(iter);
    }
}

bool has_next(SortedIterator* iter) {
    return iter && iter->heap && iter->heap->size > 0;
}

bool get_next(SortedIterator* iter, int* value) {
    if (!has_next(iter)) return false;

    HeapNode min_node;
    if (!extract_min(iter->heap, &min_node)) return false;

    *value = min_node.value;

    int arr_idx = min_node.array_idx;
    int elem_idx = min_node.element_idx + 1;

    if (elem_idx < iter->sizes[arr_idx]) {
        HeapNode next_node = {iter->arrays[arr_idx][elem_idx], arr_idx, elem_idx};
        insert_min_heap(iter->heap, next_node);
    }

    return true;
}

int main() {
    int arr1[] = {1, 4, 7};
    int arr2[] = {2, 5, 8};
    int arr3[] = {3, 6, 9};

    int* arrays[] = {arr1, arr2, arr3};
    int sizes[] = {3, 3, 3};
    int num_arrays = 3;

    SortedIterator* iter = create_sorted_iterator(arrays, sizes, num_arrays);
    if (!iter) {
        fprintf(stderr, "Failed to create iterator\n");
        return 1;
    }

    int value;
    while (get_next(iter, &value)) {
        printf("%d ", value);
    }
    printf("\n");

    destroy_sorted_iterator(iter);
    return 0;
}