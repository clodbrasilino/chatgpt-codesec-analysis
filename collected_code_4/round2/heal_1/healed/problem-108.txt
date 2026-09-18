#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    int arrNum;
    int index;
} Node;

void swap(Node *x, Node *y) {
    Node z = *x;
    *x = *y;
    *y = z;
}

void heapify(Node harr[], int i, int count) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < count && harr[left].val < harr[smallest].val)
        smallest = left;

    if (right < count && harr[right].val < harr[smallest].val)
        smallest = right;

    if (smallest != i) {
        swap(&harr[i], &harr[smallest]);
        heapify(harr, smallest, count);
    }
}

void merge(int **arrays, int arraysSize, int *arraysSizes, int returnSize) {
    Node *harr = (Node*)malloc(sizeof(Node) * arraysSize);
    if (harr == NULL)
        return;

    for (int i = 0; i < arraysSize; i++) {
        harr[i].val = arrays[i][0];
        harr[i].arrNum = i;
        harr[i].index = 1;
    }

    int heap_size = arraysSize;
    for (int i = (heap_size - 1) / 2; i >= 0; i--)
        heapify(harr, i, heap_size);

    for (int count = 0; count < returnSize; count++) {
        Node root = harr[0];
        printf("%d ", root.val);

        if (root.index < arraysSizes[root.arrNum])
            harr[0].val = arrays[root.arrNum][root.index++];
        else {
            harr[0] = harr[heap_size - 1];
            heap_size--;
        }

        heapify(harr, 0, heap_size);
    }
}

int main() {
    int arraysSize = 3;
    int *arraysSizes = (int*)malloc(sizeof(int) * arraysSize);
    if (arraysSizes == NULL)
        return 1;

    arraysSizes[0] = 3;
    arraysSizes[1] = 3;
    arraysSizes[2] = 3;

    int **arrays = (int**)malloc(sizeof(int*) * arraysSize);
    if (arrays == NULL)
        return 1;

    for (int i = 0; i < arraysSize; i++) {
        arrays[i] = (int*)malloc(sizeof(int) * arraysSizes[i]);
        if (arrays[i] == NULL)
            return 1;
    }

    arrays[0][0] = 1; arrays[0][1] = 3; arrays[0][2] = 5;
    arrays[1][0] = 2; arrays[1][1] = 4; arrays[1][2] = 6;
    arrays[2][0] = 8; arrays[2][1] = 10; arrays[2][2] = 12;

    merge(arrays, arraysSize, arraysSizes, 9);
    return 0;
}