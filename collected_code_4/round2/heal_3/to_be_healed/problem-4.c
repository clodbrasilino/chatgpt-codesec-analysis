#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MIN' is defined in header '<limits.h>'; did you forget to '#include <limits.h>'?
  */

typedef struct {
    int* arr;
    int size;
    int capacity;
} PriorityQueue;

PriorityQueue* createQueue(int capacity) {
    PriorityQueue* queue = (PriorityQueue*)malloc(sizeof(PriorityQueue));

    if(queue == NULL) {
        return NULL;
    }

    queue->arr = (int*)malloc(capacity * sizeof(int));

    if(queue->arr == NULL) {
        free(queue);
        return NULL;
    }

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
    if (queue == NULL || queue->arr == NULL || queue->size >= queue->capacity) {
        return;
    }

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
    if (queue == NULL || queue->arr == NULL || queue->size <= 0) {
        /* Possible weaknesses found:
         *  each undeclared identifier is reported only once for each function it appears in
         *  'INT_MIN' undeclared (first use in this function)
         */
        return INT_MIN;
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
    for (int i = 0; i < count && queue && queue->arr && queue->size > 0; i++) {
        printf("%d\n", removeMax(queue));
    }
}

int main() {
    int values[] = {5, 3, 8, 4, 1, 9, 2, 6, 7, 10};
    int n = sizeof(values) / sizeof(values[0]);

    PriorityQueue* queue = createQueue(n);

    if (queue == NULL) {
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n; i++) {
        insert(queue, values[i]);
    }

    printMaxValues(queue, n);

    free(queue->arr);
    free(queue);

    return EXIT_SUCCESS;
}