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

void insertBeforeEach(Node **head, int value) {
    Node *current = *head;
    while (current != NULL) {
        Node *newNode = createNode(value);
        newNode->next = current;
        if (current == *head) {
            *head = newNode;
        } else {
            Node *temp = *head;
            while (temp->next != current) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
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