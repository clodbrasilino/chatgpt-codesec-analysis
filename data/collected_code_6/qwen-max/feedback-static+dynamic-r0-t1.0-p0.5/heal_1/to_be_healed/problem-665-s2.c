#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* createNode(int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void shiftFirstToEnd(Node **head) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }

    Node *current = *head;
    /* Possible weaknesses found:
     *  Assignment 'prev=NULL', assigned value is 0
     */
    Node *prev = NULL;

    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }

    /* Possible weaknesses found:
     *  Null pointer dereference
     *  Possible null pointer dereference: prev [nullPointer]
     */
    prev->next = NULL;
    current->next = *head;
    *head = current;
}

void printList(Node *node) {
    while (node != NULL) {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

int main() {
    Node *head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);

    printf("Original list: ");
    printList(head);

    shiftFirstToEnd(&head);

    printf("List after shifting first to end: ");
    printList(head);

    return 0;
}