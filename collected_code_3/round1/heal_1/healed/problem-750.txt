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

Node* addTupleToList(Node* head, Tuple tuple) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        return head;
    }
    newNode->data = tuple;
    newNode->next = head;
    return newNode;
}

int main() {
    Node* head = NULL;
    Tuple tuple1 = {1, 2};
    Tuple tuple2 = {3, 4};
    Tuple tuple3 = {5, 6};

    head = addTupleToList(head, tuple1);
    if(head == NULL) {
        return -1;
    }

    head = addTupleToList(head, tuple2);
    if(head == NULL) {
        return -1;
    }

    head = addTupleToList(head, tuple3);
    if(head == NULL) {
        return -1;
    }

    Node* temp = head;
    while(temp != NULL) {
        printf("(%d, %d)\n", temp->data.a, temp->data.b);
        temp = temp->next;
    }

    // Free allocated memory
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}