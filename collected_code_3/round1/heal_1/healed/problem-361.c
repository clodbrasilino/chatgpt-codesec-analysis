#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
    struct List* next;
} List;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return NULL;

    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

List* createList(Node* node) {
    List* newList = (List*)malloc(sizeof(List));
    if (!newList) return NULL;

    newList->head = node;
    newList->next = NULL;
    return newList;
}

void addNode(List* list, int data) {
    if (list == NULL) return;

    Node* current = list->head;
    while (current->next != NULL) {
        current = current->next;
    }

    Node* newNode = createNode(data);
    if (newNode != NULL) current->next = newNode;
}

void addList(List** list, Node* node) {
    if (list == NULL) return;

    List* newList = createList(node);
    if (newList != NULL) {
        newList->next = *list;
        *list = newList;
    }
}

void removeEmptyLists(List** list) {
    if (list == NULL || *list == NULL) return;

    List* current = *list;
    List* prev = NULL;
    while (current != NULL) {
        if (current->head == NULL) {
            if (prev == NULL) {
                *list = current->next;
            } else {
                prev->next = current->next;
            }

            List* temp = current;
            current = current->next;
            free(temp);
        } else {
            prev = current;
            current = current->next;
        }
    }
}

int main() {
    List* list = createList(createNode(1));
    if(list != NULL) {
        addNode(list, 2);
        addNode(list, 3);
        addList(&list, NULL);
        addList(&list, createNode(4));
        removeEmptyLists(&list);
    }
    return 0;
}