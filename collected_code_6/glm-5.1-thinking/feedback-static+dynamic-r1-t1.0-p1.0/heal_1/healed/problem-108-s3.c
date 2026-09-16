#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

typedef struct {
    int value;
    int array_idx;
    int element_idx;
} HeapNode;

typedef struct {
    HeapNode *heap;
    int heap_size;
    int **arrays;
    int *array_sizes;
    int k;
} MergeIterator;

void swap(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void heapify_down(HeapNode *heap, int size, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && heap[left].value < heap[smallest].value) {
        smallest = left;
    }

    if (right < size && heap[right].value < heap[smallest].value) {
        smallest = right;
    }

    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        heapify_down(heap, size, smallest);
    }
}

void heapify_up(HeapNode *heap, int i) {
    int parent = (i - 1) / 2;
    if (i > 0 && heap[i].value < heap[parent].value) {
        swap(&heap[i], &heap[parent]);
        heapify_up(heap, parent);
    }
}

MergeIterator* create_iterator(int **arrays, int *array_sizes, int k) {
    MergeIterator *it = malloc(sizeof(MergeIterator));
    if (!it) {
        return NULL;
    }

    it->k = k;
    it->heap_size = 0;
    it->arrays = arrays;
    it->array_sizes = array_sizes;

    if (k > 0) {
        it->heap = malloc(k * sizeof(HeapNode));
        if (!it->heap) {
            free(it);
            return NULL;
        }
    } else {
        it->heap = NULL;
    }

    for (int i = 0; i < k; i++) {
        if (array_sizes[i] > 0 && arrays[i] != NULL) {
            it->heap[it->heap_size].value = arrays[i][0];
            it->heap[it->heap_size].array_idx = i;
            it->heap[it->heap_size].element_idx = 0;
            it->heap_size++;
            heapify_up(it->heap, it->heap_size - 1);
        }
    }

    return it;
}

bool has_next(const MergeIterator *it) {
    if (it == NULL) {
        return false;
    }
    return it->heap_size > 0;
}

int next(MergeIterator *it) {
    if (!it || it->heap_size == 0) {
        return INT_MIN;
    }

    HeapNode root = it->heap[0];
    it->heap[0] = it->heap[it->heap_size - 1];
    it->heap_size--;

    if (it->heap_size > 0) {
        heapify_down(it->heap, it->heap_size, 0);
    }

    if (root.element_idx + 1 < it->array_sizes[root.array_idx] && it->arrays[root.array_idx] != NULL) {
        HeapNode new_node;
        new_node.value = it->arrays[root.array_idx][root.element_idx + 1];
        new_node.array_idx = root.array_idx;
        new_node.element_idx = root.element_idx + 1;
        
        it->heap[it->heap_size] = new_node;
        it->heap_size++;
        heapify_up(it->heap, it->heap_size - 1);
    }

    return root.value;
}

void destroy_iterator(MergeIterator *it) {
    if (it) {
        free(it->heap);
        free(it);
    }
}

int main() {
    int arr1[] = {1, 4, 7, 10};
    int arr2[] = {2, 5, 8};
    int arr3[] = {0, 3, 6, 9, 11};

    int *arrays[] = {arr1, arr2, arr3};
    int sizes[] = {4, 3, 5};
    int k = 3;

    MergeIterator *it = create_iterator(arrays, sizes, k);
    if (!it) {
        return EXIT_FAILURE;
    }

    while (has_next(it)) {
        printf("%d ", next(it));
    }
    printf("\n");

    destroy_iterator(it);

    return EXIT_SUCCESS;
}