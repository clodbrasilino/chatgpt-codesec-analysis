#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int val;
    int arr_idx;
    int elem_idx;
} HeapNode;

void swap(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(HeapNode *heap, int i, int heap_size) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap_size && heap[left].val < heap[smallest].val)
        smallest = left;

    if (right < heap_size && heap[right].val < heap[smallest].val)
        smallest = right;

    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        minHeapify(heap, smallest, heap_size);
    }
}

void buildMinHeap(HeapNode *heap, int heap_size) {
    for (int i = (heap_size - 1) / 2; i >= 0; i--)
        minHeapify(heap, i, heap_size);
}

int* findSmallestRange(int **arr, int k, const int *n, int *rangeSize) {
    int *range = (int *)malloc(2 * sizeof(int));
    if (range == NULL) {
        *rangeSize = 0;
        return NULL;
    }

    HeapNode *heap = (HeapNode *)malloc(k * sizeof(HeapNode));
    if (heap == NULL) {
        free(range);
        *rangeSize = 0;
        return NULL;
    }

    int max_val = INT_MIN;

    for (int i = 0; i < k; i++) {
        if (n[i] == 0) {
            free(heap);
            free(range);
            *rangeSize = 0;
            return NULL;
        }
        heap[i].val = arr[i][0];
        heap[i].arr_idx = i;
        heap[i].elem_idx = 0;
        if (arr[i][0] > max_val)
            max_val = arr[i][0];
    }

    buildMinHeap(heap, k);

    int min_range = INT_MAX;

    while (1) {
        HeapNode root = heap[0];
        int min_val = root.val;

        if (max_val - min_val < min_range) {
            min_range = max_val - min_val;
            range[0] = min_val;
            range[1] = max_val;
        }

        if (root.elem_idx + 1 < n[root.arr_idx]) {
            root.elem_idx++;
            root.val = arr[root.arr_idx][root.elem_idx];
            if (root.val > max_val)
                max_val = root.val;
        } else {
            break;
        }

        heap[0] = root;
        minHeapify(heap, 0, k);
    }

    free(heap);
    *rangeSize = 2;
    return range;
}

int main() {
    int k = 3;
    const int n[] = {3, 3, 3};
    
    int arr0[] = {4, 7, 9};
    int arr1[] = {1, 2, 3};
    int arr2[] = {10, 12, 15};
    
    int *arr[] = {arr0, arr1, arr2};
    int rangeSize = 0;

    int *range = findSmallestRange(arr, k, n, &rangeSize);

    if (range != NULL) {
        printf("[%d, %d]\n", range[0], range[1]);
        free(range);
    }

    return 0;
}