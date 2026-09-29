#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* createNode(int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertBeforeEach(Node **head, int newData) {
    Node *current = *head;
    Node *prev = NULL;
    while (current != NULL) {
        Node *newNode = createNode(newData);
        if (prev == NULL) {
            newNode->next = current;
            *head = newNode;
        } else {
            prev->next = newNode;
            newNode->next = current;
        }
        prev = current;
        current = current->next;
    }
}

void printList(Node *head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    Node *head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);

    printf("Original list: ");
    printList(head);

    insertBeforeEach(&head, 0);

    printf("Modified list: ");
    printList(head);

    return 0;
}