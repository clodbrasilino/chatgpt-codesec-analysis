#include <stdio.h>
#include <stdlib.h>

void push(int *heap, int *size, int value) {
    int i = (*size)++;
    heap[i] = value;
    while (i > 0 && heap[(i - 1) / 2] > heap[i]) {
        int temp = heap[i];
        heap[i] = heap[(i - 1) / 2];
        heap[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

int pop(int *heap, int *size) {
    if (*size == 0) {
        return -1;
    }
    int root = heap[0];
    heap[0] = heap[--(*size)];
    int i = 0;
    while (1) {
        int child = 2 * i + 1;
        if (child >= *size) break;
        if (child + 1 < *size && heap[child] > heap[child + 1]) {
            child++;
        }
        if (heap[i] > heap[child]) {
            int temp = heap[i];
            heap[i] = heap[child];
            heap[child] = temp;
            i = child;
        } else {
            break;
        }
    }
    return root;
}

int main() {
    int *heap = (int *)malloc(100 * sizeof(int));
    int size = 0;

    push(heap, &size, 5);
    push(heap, &size, 3);
    push(heap, &size, 8);
    push(heap, &size, 1);
    push(heap, &size, 4);

    while (size > 0) {
        printf("%d\n", pop(heap, &size));
    }

    free(heap);
    return 0;
}