#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int value;
    int array_idx;
    int element_idx;
} HeapNode;

void swap(HeapNode *a, HeapNode *b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(HeapNode heap[], int size, int i) {
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int smallest = i;

    if (l < size && heap[l].value < heap[smallest].value) {
        smallest = l;
    }
    if (r < size && heap[r].value < heap[smallest].value) {
        smallest = r;
    }
    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        minHeapify(heap, size, smallest);
    }
}

void buildMinHeap(HeapNode heap[], int size) {
    int i;
    for (i = (size - 1) / 2; i >= 0; i--) {
        minHeapify(heap, size, i);
    }
}

void findSmallestRange(int **arrays, int k, const int *n) {
    if (k <= 0) return;

    HeapNode *heap = (HeapNode *)malloc(k * sizeof(HeapNode));
    if (!heap) {
        return;
    }

    int max_val = INT_MIN;
    /* Possible weaknesses found:
     *  The scope of the variable 'min_val' can be reduced. [variableScope]
     */
    int min_val;
    int range = INT_MAX;
    int start = -1, end = -1;

    for (int i = 0; i < k; i++) {
        if (n[i] <= 0) {
            free(heap);
            return;
        }
        heap[i].value = arrays[i][0];
        heap[i].array_idx = i;
        heap[i].element_idx = 1;
        if (heap[i].value > max_val) {
            max_val = heap[i].value;
        }
    }

    buildMinHeap(heap, k);

    while (1) {
        HeapNode root = heap[0];
        min_val = root.value;

        if (max_val - min_val < range) {
            range = max_val - min_val;
            start = min_val;
            end = max_val;
        }

        if (root.element_idx < n[root.array_idx]) {
            root.value = arrays[root.array_idx][root.element_idx];
            root.element_idx += 1;

            if (root.value > max_val) {
                max_val = root.value;
            }
        } else {
            break;
        }

        heap[0] = root;
        minHeapify(heap, k, 0);
    }

    printf("Smallest range is [%d, %d]\n", start, end);
    free(heap);
}

int main(void) {
    int arr1[] = {4, 7, 9, 12, 15};
    int arr2[] = {0, 8, 10, 14, 20};
    int arr3[] = {6, 12, 16, 30, 50};

    int *arrays[] = {arr1, arr2, arr3};
    int k = 3;
    /* Possible weaknesses found:
     *  Variable 'n' can be declared as const array [constVariable]
     */
    int n[] = {5, 5, 5};

    findSmallestRange(arrays, k, n);

    return 0;
}