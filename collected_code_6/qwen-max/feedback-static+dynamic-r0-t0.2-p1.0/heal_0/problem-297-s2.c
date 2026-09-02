#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    Node *tail;
} List;

void addNode(List *list, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        return;
    }
    newNode->value = value;
    newNode->next = NULL;
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }
}

List* flattenNestedList(List *nestedList) {
    List *flatList = (List *)malloc(sizeof(List));
    if (flatList == NULL) {
        return NULL;
    }
    flatList->head = NULL;
    flatList->tail = NULL;

    Node *current = nestedList->head;
    while (current != NULL) {
        addNode(flatList, current->value);
        current = current->next;
    }

    return flatList;
}

void printList(List *list) {
    Node *current = list->head;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

void freeList(List *list) {
    Node *current = list->head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

int main() {
    List *nestedList = (List *)malloc(sizeof(List));
    if (nestedList == NULL) {
        return 1;
    }
    nestedList->head = NULL;
    nestedList->tail = NULL;

    addNode(nestedList, 1);
    addNode(nestedList, 2);
    addNode(nestedList, 3);

    List *flatList = flattenNestedList(nestedList);
    if (flatList == NULL) {
        freeList(nestedList);
        return 1;
    }

    printList(flatList);

    freeList(nestedList);
    freeList(flatList);

    return 0;
}