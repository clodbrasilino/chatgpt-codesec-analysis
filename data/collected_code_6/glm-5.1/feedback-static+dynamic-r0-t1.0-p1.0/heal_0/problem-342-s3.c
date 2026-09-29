#include <stdio.h>
#include <stdlib.h>

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

void min_heapify(HeapNode *heap, int i, int size) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < size && heap[left].val < heap[smallest].val) smallest = left;
    if (right < size && heap[right].val < heap[smallest].val) smallest = right;
    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        min_heapify(heap, smallest, size);
    }
}

void find_smallest_range(int **arrs, int *sizes, int k, int *res) {
    HeapNode *heap = (HeapNode *)malloc(k * sizeof(HeapNode));
    if (!heap) return;
    int max_val = -2147483647 - 1;
    for (int i = 0; i < k; i++) {
        heap[i].val = arrs[i][0];
        heap[i].arr_idx = i;
        heap[i].elem_idx = 0;
        if (arrs[i][0] > max_val) max_val = arrs[i][0];
    }
    for (int i = (k - 1) / 2; i >= 0; i--) min_heapify(heap, i, k);
    res[0] = heap[0].val;
    res[1] = max_val;
    int range = max_val - heap[0].val;
    while (1) {
        HeapNode root = heap[0];
        int curr_range = max_val - root.val;
        if (curr_range < range) {
            range = curr_range;
            res[0] = root.val;
            res[1] = max_val;
        }
        if (root.elem_idx + 1 < sizes[root.arr_idx]) {
            heap[0].val = arrs[root.arr_idx][root.elem_idx + 1];
            heap[0].elem_idx = root.elem_idx + 1;
            if (heap[0].val > max_val) max_val = heap[0].val;
            min_heapify(heap, 0, k);
        } else {
            break;
        }
    }
    free(heap);
}

int main() {
    int k = 3;
    int sizes[] = {3, 3, 3};
    int a0[] = {4, 10, 15};
    int a1[] = {0, 9, 12};
    int a2[] = {5, 18, 22};
    int *arrs[] = {a0, a1, a2};
    int res[2];
    find_smallest_range(arrs, sizes, k, res);
    printf("[%d, %d]\n", res[0], res[1]);
    return 0;
}