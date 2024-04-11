#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    int arrNum;
    int idx;
} Node;

void swap(Node *a, Node *b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(Node *heap, int i, int heapSize) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heapSize && heap[left].val < heap[smallest].val)
        smallest = left;

    if (right < heapSize && heap[right].val < heap[smallest].val)
        smallest = right;

    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        heapify(heap, smallest, heapSize);
    }
}

void buildHeap(Node *heap, int heapSize) {
    int i;
    for (i = (heapSize - 2) / 2; i >= 0; --i)
        heapify(heap, i, heapSize);
}

void merge(int **arr, int *size, int arrCount, int *mergedArr) {
    int heapSize = arrCount;
    Node *heap = (Node *)malloc(sizeof(Node) * heapSize);

    if(heap == NULL) {
        exit(-1);
    }   

    int i;
    for (i = 0; i < heapSize; ++i) {
        heap[i].val = arr[i][0];
        heap[i].arrNum = i;
        heap[i].idx = 1;
    }

    buildHeap(heap, heapSize);

    int mergedIdx = 0;
    while (heapSize) {
        mergedArr[mergedIdx++] = heap[0].val;

        if (heap[0].idx < size[heap[0].arrNum])
            heap[0].val = arr[heap[0].arrNum][heap[0].idx++];
        else {
            heap[0] = heap[heapSize - 1];
            --heapSize;
        }

        heapify(heap, 0, heapSize);
    }

    free(heap);
}

int main() {
    int arrCount = 3;
    int size[] = {3, 3, 3};
    int **arr = (int **)malloc(sizeof(int *) * arrCount);

    if(arr == NULL) {
        exit(-1);
    }

    arr[0] = (int *)malloc(sizeof(int) * size[0]);
    arr[0][0] = 1; arr[0][1] = 4; arr[0][2] = 7;

    arr[1] = (int *)malloc(sizeof(int) * size[1]);
    arr[1][0] = 2; arr[1][1] = 5; arr[1][2] = 8;

    arr[2] = (int *)malloc(sizeof(int) * size[2]);
    arr[2][0] = 3; arr[2][1] = 6; arr[2][2] = 9;

    int totalSize = size[0] + size[1] + size[2];
    int *mergedArr = (int *)malloc(sizeof(int) * totalSize);

    if(mergedArr == NULL) {
        exit(-1);
    }

    merge(arr, size, arrCount, mergedArr);

    int i;
    for (i = 0; i < totalSize; ++i)
        printf("%d ", mergedArr[i]);
    printf("\n");

    for (i = 0; i < arrCount; ++i)
        free(arr[i]);
    free(arr);
    free(mergedArr);

    return 0;
}