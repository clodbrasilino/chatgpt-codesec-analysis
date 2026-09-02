#include <stdio.h>
#include <stdlib.h>

typedef struct {
    /* Possible weaknesses found:
     *  struct member 'Tuple::y' is never used. [unusedStructMember]
     *  struct member 'Tuple::x' is never used. [unusedStructMember]
     */
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

void addTupleToList(List* list, Tuple tuple) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->data = tuple;
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

    Tuple t1 = {1, 2};
    Tuple t2 = {3, 4};

    addTupleToList(&myList, t1);
    addTupleToList(&myList, t2);

    freeList(&myList);
    return 0;
}