#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* arr;
    int size;
    int capacity;
} PriorityQueue;

PriorityQueue* createQueue(int capacity) {
    PriorityQueue* queue = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'queue' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    queue->arr = (int*)malloc(capacity * sizeof(int));
    queue->size = 0;
    queue->capacity = capacity;

    return queue;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insert(PriorityQueue* queue, int value) {
    if (queue->size == queue->capacity) {
        return;
    }

    /* Possible weaknesses found:
     *  dereference of possibly-NULL '*queue.arr + (long unsigned int)*queue.size * 4' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    queue->arr[queue->size] = value;
    int index = queue->size;
    int parentIndex = (index - 1) / 2;

    while (index > 0 && queue->arr[parentIndex] < queue->arr[index]) {
        swap(&queue->arr[parentIndex], &queue->arr[index]);
        index = parentIndex;
        parentIndex = (index - 1) / 2;
    }

    queue->size++;
}

int removeMax(PriorityQueue* queue) {
    if (queue->size == 0) {
        return -1;
    }

    int rootValue = queue->arr[0];
    queue->size--;
    queue->arr[0] = queue->arr[queue->size];

    int index = 0, leftChildIndex = 1, rightChildIndex = 2;

    while (leftChildIndex < queue->size) {
        int swapChildIndex = index;

        if (queue->arr[swapChildIndex] < queue->arr[leftChildIndex]) {
            swapChildIndex = leftChildIndex;
        }
        if (rightChildIndex < queue->size && queue->arr[swapChildIndex] < queue->arr[rightChildIndex]) {
            swapChildIndex = rightChildIndex;
        }
        if (swapChildIndex == index) {
            break;
        }

        swap(&queue->arr[index], &queue->arr[swapChildIndex]);
        index = swapChildIndex;
        leftChildIndex = 2 * index + 1;
        rightChildIndex = 2 * index + 2;
    }

    return rootValue;
}

void printMaxValues(PriorityQueue* queue, int count) {
    for (int i = 0; i < count; i++) {
        if (queue->size == 0) {
            return;
        }
        printf("%d\n", removeMax(queue));
    }
}

int main() {
    int values[] = {5, 3, 8, 4, 1, 9, 2, 6, 7, 10};
    int n = sizeof(values) / sizeof(values[0]);

    PriorityQueue* queue = createQueue(n);
    for (int i = 0; i < n; i++) {
        insert(queue, values[i]);
    }

    printMaxValues(queue, n);

    free(queue->arr);
    free(queue);

    return 0;
}