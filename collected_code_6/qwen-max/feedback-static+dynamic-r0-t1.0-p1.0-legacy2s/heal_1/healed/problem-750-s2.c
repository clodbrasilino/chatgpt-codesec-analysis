#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y;
} Tuple;

typedef struct Node {
    Tuple data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} List;

void initList(List* list) {
    list->head = NULL;
}

void addTupleToList(List* list, int x, int y) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->data.x = x;
    newNode->data.y = y;
    newNode->next = list->head;
    list->head = newNode;
}

void freeList(List* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
}

int main() {
    List myList;
    initList(&myList);

    addTupleToList(&myList, 1, 2);
    addTupleToList(&myList, 3, 4);

    freeList(&myList);
    return 0;
}