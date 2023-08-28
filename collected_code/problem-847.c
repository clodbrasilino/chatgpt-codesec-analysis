#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Node* copyListFromSingletonTuple(Node* head) {
    if (head == NULL) {
        return NULL;
    }
    Node* newList = createNode(head->data);
    Node* current = newList;
    Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
        current->next = createNode(temp->data);
        current = current->next;
    }
    return newList;
}