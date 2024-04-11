#include <stdio.h>
#include <stdlib.h>

typedef struct Tuple {
    int a;
    int b;
} Tuple;

typedef struct Node {
    Tuple data;
    struct Node* next;
} Node;

Node* addTupleToList(Node* head, Tuple t) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = t;
    newNode->next = head;
    return newNode;
}

int main() {
    Node* head = NULL;
    Tuple t1 = {1, 2};
    Tuple t2 = {3, 4};
    Tuple t3 = {5, 6};

    head = addTupleToList(head, t1);
    head = addTupleToList(head, t2);
    head = addTupleToList(head, t3);

    Node* temp = head;
    while(temp != NULL) {
        printf("(%d, %d)\n", temp->data.a, temp->data.b);
        temp = temp->next;
    }

    return 0;
}