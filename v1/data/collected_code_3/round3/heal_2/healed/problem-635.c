#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int* harr;
    int capacity;
    int heap_size;
} MinHeap;

MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*) malloc(sizeof(MinHeap));
    if (minHeap == NULL) {
        return NULL;
    }

    minHeap->heap_size = 0;
    minHeap->capacity = capacity;
    minHeap->harr = (int*) malloc(minHeap->capacity * sizeof(int));
    if (minHeap->harr == NULL) {
        free(minHeap);
        return NULL;
    }

    return minHeap;
}

void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void minHeapify(MinHeap* minHeap, int idx) {
    int smallest, left, right;

    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < minHeap->heap_size && minHeap->harr[left] < minHeap->harr[smallest]) {
        smallest = left;
    }

    if (right < minHeap->heap_size && minHeap->harr[right] < minHeap->harr[smallest]) {
        smallest = right;
    }

    if (smallest != idx) {
        swap(&minHeap->harr[smallest], &minHeap->harr[idx]);
        minHeapify(minHeap, smallest);
    }
}

int extractMin(MinHeap* minHeap) {
    if (minHeap->heap_size <= 0)
        return INT_MAX;

    if (minHeap->heap_size == 1) {
        minHeap->heap_size--;
        return minHeap->harr[0];
    }

    int root = minHeap->harr[0];
    minHeap->harr[0] = minHeap->harr[minHeap->heap_size-1];
    minHeap->heap_size--;
    minHeapify(minHeap, 0);

    return root;
}

void insertKey(MinHeap* minHeap, int k) {
    if (minHeap->heap_size == minHeap->capacity) {
        printf("\nOverflow: Could not insertKey\n");
        return;
    }

    minHeap->heap_size++;
    int i = minHeap->heap_size - 1;
    minHeap->harr[i] = k;

    while (i != 0 && minHeap->harr[(i - 1) / 2] > minHeap->harr[i]) {
        swap(&minHeap->harr[i], &minHeap->harr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int main() {
    MinHeap* minHeap = createMinHeap(11);
    if (minHeap == NULL) {
        printf("\nFailure: Could not create MinHeap\n");
        return 1;
    }

    insertKey(minHeap, 3);
    insertKey(minHeap, 2);
    insertKey(minHeap, 15);
    insertKey(minHeap, 5);
    insertKey(minHeap, 4);
    insertKey(minHeap, 45);

    printf("%d ", extractMin(minHeap));
    printf("%d ", extractMin(minHeap));
    printf("%d ", extractMin(minHeap));
    printf("%d ", extractMin(minHeap));
    printf("%d ", extractMin(minHeap));

    free(minHeap->harr);
    free(minHeap);

    return 0;
}