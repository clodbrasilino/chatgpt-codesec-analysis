#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    int arrayNum;
    int indexInArray;
    struct Node* next;
} Node;

typedef struct Queue {
    struct Node* start;
} Queue;

Node* newNode(int val, int arrayNum, int indexInArray) {
    Node* temp = (Node*)malloc(sizeof(Node));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'temp' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    temp->val = val;
    temp->arrayNum = arrayNum;
    temp->indexInArray = indexInArray;
    temp->next = NULL;
    return temp;
}

Node* pop(Queue* queue) {
    Node* temp = queue->start;
    queue->start = queue->start->next;
    return temp;
}

void push(Queue* queue, int val, int arrayNum, int indexInArray) {
    Node *start = queue->start;
    Node *temp = newNode(val, arrayNum, indexInArray);
    if (queue->start == NULL) {
        queue->start = temp;
        return;
    }
    if (queue->start->val > val) {
        temp->next = queue->start;
        queue->start = temp;
        return;
    }
    while (start->next != NULL && start->next->val < val) {
        start = start->next;
    }
    temp->next = start->next;
    start->next = temp;
}

void mergeArrays(int arr[][10], int arrayCount, int arrayLength) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'queue' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    queue->start = NULL;

    for (int i = 0; i < arrayCount; i++) {
        push(queue, arr[i][0], i, 0);
    }
    while (queue->start != NULL) {
        /* Possible weaknesses found:
         *  leak of 'top' [CWE-401] [-Wanalyzer-malloc-leak]
         */
        Node* top = pop(queue);
        printf("%d ", top->val);

        if (top->indexInArray + 1 < arrayLength) {
            push(queue, arr[top->arrayNum][top->indexInArray + 1], top->arrayNum, top->indexInArray + 1);
        }
    }
}
int main() {
    int arr[][10] = {
    {2, 6, 12, 34, 54, 88},
    {1, 9, 13, 17, 56},
    {14, 35, 78, 89, 99},
    {5, 8, 15, 18, 25}};
    int arrayCount = sizeof(arr) / sizeof(arr[0]);
    int arrayLength = sizeof(arr[0]) / sizeof(int);
    mergeArrays(arr, arrayCount, arrayLength);
    return 0;
}