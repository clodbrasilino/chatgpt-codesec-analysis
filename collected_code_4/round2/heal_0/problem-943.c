#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} Node;

Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

Node* sortedMerge(Node* a, Node* b) {
    Node* result = NULL;

    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);

    if (a->data <= b->data) {
        result = a;
        result->next = sortedMerge(a->next, b);
    } else {
        result = b;
        result->next = sortedMerge(a, b->next);
    }

    return result;
}

void printList(Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
}

int main() {
    Node* res = NULL;
    Node* a = NULL;
    Node* b = NULL;

    a = newNode(5);
    a->next = newNode(10);
    a->next->next = newNode(15);

    b = newNode(2);
    b->next = newNode(3);
    b->next->next = newNode(20);

    res = sortedMerge(a, b);

    printList(res);

    return 0;
}