#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node {
    int val;
    int arrNum;
    int nextIdx;
} Node;

void swap(Node **x, Node **y) {
    Node *temp = *x;
    *x = *y;
    *y = temp;
}

void minHeapify(Node **arr, int i, int heapSize) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heapSize && arr[left]->val < arr[smallest]->val)
        smallest = left;

    if (right < heapSize && arr[right] != NULL && arr[right]->val < arr[smallest]->val)
        smallest = right;

    if (smallest != i) {
        swap(&arr[i], &arr[smallest]);
        minHeapify(arr, smallest, heapSize);
    }
}

void buildMinHeap(Node **arr, int n) {
    int i;
    for (i = (n - 2) / 2; i >= 0; --i)
        minHeapify(arr, i, n);
}

void mergeSortedArrays(int **arr, int *size, int n) {
    Node **heapArr = (Node **)malloc(sizeof(Node *) * n);
    if (!heapArr) exit(1);
 
    int i;
    for (i = 0; i < n; ++i) {
        Node *node = (Node *)malloc(sizeof(Node));
        if (!node) exit(1);
 
        node->val = arr[i][0];
        node->arrNum = i;
        node->nextIdx = 1;
        heapArr[i] = node;
    }

    buildMinHeap(heapArr, n);

    while (1) {
        Node *root = heapArr[0];

        printf("%d ", root->val);

        if (root->nextIdx < size[root->arrNum])
            root->val = arr[root->arrNum][root->nextIdx++];
        else
            root->val = INT_MAX;

        minHeapify(heapArr, 0, n);

        if (heapArr[0]->val == INT_MAX)
            break;
    }

    for (i = 0; i < n; ++i)
        free(heapArr[i]);
    free(heapArr);
}

int main() {
    int *arr[] = {
        (int[]) {1, 3, 5, 7},
        (int[]) {2, 4, 6, 8},
        (int[]) {0, 9, 10, 11}
    };

    int size[] = {4, 4, 4};

    int n = sizeof(arr) / sizeof(arr[0]);

    mergeSortedArrays(arr, size, n);

    return 0;
}