#include <stdio.h>

typedef struct Tuple {
    int first;
    int second;
} Tuple;

typedef struct Node {
    Tuple data;
    struct Node *next;
} Node;

void addTupleToList(Node **head, Tuple tuple) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = tuple;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    Node *current = *head;

    while (current->next != NULL) {
        current = current->next;
    }

    current->next = newNode;
}

int main() {
    Node *list = NULL;

    Tuple tuple1 = {1, 2};
    Tuple tuple2 = {3, 4};
    Tuple tuple3 = {5, 6};

    addTupleToList(&list, tuple1);
    addTupleToList(&list, tuple2);
    addTupleToList(&list, tuple3);

    Node *current = list;

    while (current != NULL) {
        printf("(%d, %d)\n", current->data.first, current->data.second);
        current = current->next;
    }

    return 0;
}