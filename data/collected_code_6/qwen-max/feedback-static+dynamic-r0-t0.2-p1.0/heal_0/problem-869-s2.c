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

void removeOutOfRange(List *list, int min, int max) {
    Node *current = list->head;
    Node *prev = NULL;
    while (current != NULL) {
        if (current->value < min || current->value > max) {
            if (prev == NULL) {
                list->head = current->next;
            } else {
                prev->next = current->next;
            }
            Node *temp = current;
            current = current->next;
            free(temp);
        } else {
            prev = current;
            current = current->next;
        }
    }
    if (prev != NULL) {
        list->tail = prev;
    } else {
        list->tail = NULL;
    }
}

int main() {
    List *list = createList();
    addNode(list, 10);
    addNode(list, 20);
    addNode(list, 30);
    addNode(list, 40);
    addNode(list, 50);

    removeOutOfRange(list, 20, 40);

    Node *current = list->head;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }

    freeList(list);
    return 0;
}