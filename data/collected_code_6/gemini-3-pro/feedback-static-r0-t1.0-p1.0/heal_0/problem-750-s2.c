#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    float value;
} Tuple;

typedef struct Node {
    Tuple data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
} List;

List* createList() {
    List* list = (List*)malloc(sizeof(List));
    if (list != NULL) {
        list->head = NULL;
        list->tail = NULL;
    }
    return list;
}

int addTupleToList(List* list, Tuple tuple) {
    if (list == NULL) {
        return 0;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        return 0;
    }

    newNode->data = tuple;
    newNode->next = NULL;

    if (list->tail == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }

    return 1;
}

void freeList(List* list) {
    if (list == NULL) {
        return;
    }
    Node* current = list->head;
    Node* nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    free(list);
}

void printList(const List* list) {
    if (list == NULL) {
        return;
    }
    Node* current = list->head;
    while (current != NULL) {
        printf("ID: %d, Value: %.2f\n", current->data.id, current->data.value);
        current = current->next;
    }
}

int main() {
    List* myList = createList();
    if (myList == NULL) {
        fprintf(stderr, "Failed to create list.\n");
        return 1;
    }

    Tuple t1 = {1, 10.5f};
    Tuple t2 = {2, 20.0f};

    if (!addTupleToList(myList, t1)) {
        fprintf(stderr, "Failed to add tuple 1.\n");
    }
    if (!addTupleToList(myList, t2)) {
        fprintf(stderr, "Failed to add tuple 2.\n");
    }

    printList(myList);

    freeList(myList);

    return 0;
}