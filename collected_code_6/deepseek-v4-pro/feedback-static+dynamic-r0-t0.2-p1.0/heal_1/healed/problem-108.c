#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int array_index;
    int element_index;
} HeapNode;

typedef struct {
    int **arrays;
    int *sizes;
    int num_arrays;
    HeapNode *heap;
    int heap_size;
} MergeIterator;

static void heap_swap(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

static void heapify_down(MergeIterator *iter, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < iter->heap_size && iter->heap[left].value < iter->heap[smallest].value)
        smallest = left;
    if (right < iter->heap_size && iter->heap[right].value < iter->heap[smallest].value)
        smallest = right;

    if (smallest != idx) {
        heap_swap(&iter->heap[idx], &iter->heap[smallest]);
        heapify_down(iter, smallest);
    }
}

static void heapify_up(MergeIterator *iter, int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (iter->heap[idx].value < iter->heap[parent].value) {
            heap_swap(&iter->heap[idx], &iter->heap[parent]);
            idx = parent;
        } else {
            break;
        }
    }
}

MergeIterator *merge_iterator_create(int **arrays, int *sizes, int num_arrays) {
    if (arrays == NULL || sizes == NULL || num_arrays <= 0)
        return NULL;

    MergeIterator *iter = (MergeIterator *)malloc(sizeof(MergeIterator));
    if (iter == NULL)
        return NULL;

    iter->arrays = arrays;
    iter->sizes = sizes;
    iter->num_arrays = num_arrays;
    iter->heap_size = 0;
    iter->heap = (HeapNode *)malloc(sizeof(HeapNode) * num_arrays);
    if (iter->heap == NULL) {
        free(iter);
        return NULL;
    }

    for (int i = 0; i < num_arrays; i++) {
        if (sizes[i] > 0) {
            iter->heap[iter->heap_size].value = arrays[i][0];
            iter->heap[iter->heap_size].array_index = i;
            iter->heap[iter->heap_size].element_index = 0;
            iter->heap_size++;
            heapify_up(iter, iter->heap_size - 1);
        }
    }

    return iter;
}

int merge_iterator_next(MergeIterator *iter, int *value) {
    if (iter == NULL || value == NULL || iter->heap_size == 0)
        return 0;

    *value = iter->heap[0].value;
    int arr_idx = iter->heap[0].array_index;
    int elem_idx = iter->heap[0].element_index;

    if (elem_idx + 1 < iter->sizes[arr_idx]) {
        iter->heap[0].value = iter->arrays[arr_idx][elem_idx + 1];
        iter->heap[0].element_index = elem_idx + 1;
        heapify_down(iter, 0);
    } else {
        iter->heap[0] = iter->heap[iter->heap_size - 1];
        iter->heap_size--;
        if (iter->heap_size > 0)
            heapify_down(iter, 0);
    }

    return 1;
}

int merge_iterator_has_next(const MergeIterator *iter) {
    return iter != NULL && iter->heap_size > 0;
}

void merge_iterator_destroy(MergeIterator *iter) {
    if (iter == NULL)
        return;
    free(iter->heap);
    free(iter);
}

int main(void) {
    int arr1[] = {1, 4, 7, 10};
    int arr2[] = {2, 5, 8, 11};
    int arr3[] = {3, 6, 9, 12};

    int *arrays[] = {arr1, arr2, arr3};
    int sizes[] = {4, 4, 4};

    MergeIterator *iter = merge_iterator_create(arrays, sizes, 3);
    if (iter == NULL) {
        fprintf(stderr, "Failed to create iterator\n");
        return 1;
    }

    int value;
    while (merge_iterator_has_next(iter)) {
        if (merge_iterator_next(iter, &value)) {
            printf("%d ", value);
        }
    }
    printf("\n");

    merge_iterator_destroy(iter);
    return 0;
}