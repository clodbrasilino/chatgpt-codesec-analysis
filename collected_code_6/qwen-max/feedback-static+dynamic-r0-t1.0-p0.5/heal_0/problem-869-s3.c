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

List* createList() {
    List *list = (List *)malloc(sizeof(List));
    if (list == NULL) {
        return NULL;
    }
    list->head = NULL;
    list->tail = NULL;
    return list;
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

List* removeOutOfRange(List *list, int min, int max) {
    List *newList = createList();
    if (newList == NULL) {
        return NULL;
    }

    Node *current = list->head;
    while (current != NULL) {
        if (current->value >= min && current->value <= max) {
            addNode(newList, current->value);
        }
        current = current->next;
    }
    return newList;
}

int main() {
    List *list = createList();
    if (list == NULL) {
        return 1;
    }

    addNode(list, 10);
    addNode(list, 20);
    addNode(list, 30);
    addNode(list, 40);
    addNode(list, 50);

    List *filtered = removeOutOfRange(list, 20, 40);
    if (filtered == NULL) {
        freeList(list);
        return 1;
    }

    Node *current = filtered->head;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");

    freeList(list);
    freeList(filtered);
    return 0;
}