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

void initList(List *list) {
    list->head = NULL;
    list->tail = NULL;
}

void appendToList(List *list, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
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

void flattenList(List *source, List *destination) {
    for (Node *current = source->head; current != NULL; current = current->next) {
        appendToList(destination, current->value);
    }
}

void freeList(List *list) {
    Node *current = list->head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
    list->tail = NULL;
}

int main() {
    List source, destination;
    initList(&source);
    initList(&destination);

    appendToList(&source, 1);
    appendToList(&source, 2);
    appendToList(&source, 3);

    flattenList(&source, &destination);

    for (Node *current = destination.head; current != NULL; current = current->next) {
        printf("%d ", current->value);
    }

    freeList(&source);
    freeList(&destination);

    return 0;
}