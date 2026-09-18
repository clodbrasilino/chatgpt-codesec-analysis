#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
    int length;
} List;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

List* createList(const int* arr, int size) {
    List* list = (List*)malloc(sizeof(List));
    if (!list) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    list->length = size;

    if (size == 0) {
        return list;
    }

    list->head = createNode(arr[0]);
    Node* current = list->head;
    for (int i = 1; i < size; i++) {
        current->next = createNode(arr[i]);
        current = current->next;
    }

    return list;
}

void freeList(List* list) {
    if (!list) return;
    Node* current = list->head;
    while (current) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

List* findMinLengthSublist(List** lists, int numLists) {
    if (!lists || numLists == 0) {
        return NULL;
    }

    List* minList = NULL;
    int minLength = INT_MAX;

    for (int i = 0; i < numLists; i++) {
        if (lists[i] && lists[i]->length < minLength) {
            minLength = lists[i]->length;
            minList = lists[i];
        }
    }

    return minList;
}

void printList(List* list) {
    if (!list) {
        printf("Empty or NULL list\n");
        return;
    }
    Node* current = list->head;
    while (current) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("(Length: %d)\n", list->length);
}

int main(void) {
    /* Possible weaknesses found:
     *  Variable 'arr1' can be declared as const array [constVariable]
     */
    int arr1[] = {1, 2, 3};
    /* Possible weaknesses found:
     *  Variable 'arr2' can be declared as const array [constVariable]
     */
    int arr2[] = {4, 5};
    /* Possible weaknesses found:
     *  Variable 'arr3' can be declared as const array [constVariable]
     */
    int arr3[] = {6, 7, 8, 9};
    /* Possible weaknesses found:
     *  Variable 'arr4' can be declared as const array [constVariable]
     */
    int arr4[] = {10};

    List* lists[4];
    lists[0] = createList(arr1, 3);
    lists[1] = createList(arr2, 2);
    lists[2] = createList(arr3, 4);
    lists[3] = createList(arr4, 1);

    List* minList = findMinLengthSublist(lists, 4);

    if (minList) {
        printList(minList);
    }

    for (int i = 0; i < 4; i++) {
        freeList(lists[i]);
    }

    return 0;
}