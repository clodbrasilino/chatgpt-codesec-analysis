#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
} List;

void addNode(List *list, int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = list->head;
    list->head = newNode;
}

List* createList() {
    List *list = (List *)malloc(sizeof(List));
    list->head = NULL;
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

void reverseList(List *list) {
    Node *prev = NULL;
    Node *current = list->head;
    Node *next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    list->head = prev;
}

int main() {
    List *lists[3];
    for (int i = 0; i < 3; ++i) {
        lists[i] = createList();
        addNode(lists[i], i + 1);
        addNode(lists[i], i + 2);
        addNode(lists[i], i + 3);
    }

    for (int i = 0; i < 3; ++i) {
        reverseList(lists[i]);
    }

    for (int i = 0; i < 3; ++i) {
        Node *current = lists[i]->head;
        while (current != NULL) {
            printf("%d ", current->data);
            current = current->next;
        }
        printf("\n");
    }

    for (int i = 0; i < 3; ++i) {
        freeList(lists[i]);
    }

    return 0;
}