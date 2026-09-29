#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* createNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertAtEnd(Node **head, int data) {
    Node *newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void freeList(Node *head) {
    while (head != NULL) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }
}

Node* extractSublist(Node *head, int start, int numElements) {
    if (numElements <= 0 || head == NULL) {
        return NULL;
    }
    Node *current = head;
    for (int i = 1; i < start && current != NULL; ++i) {
        current = current->next;
    }
    if (current == NULL) {
        return NULL;
    }
    Node *newHead = current, *tail = newHead;
    for (int i = 0; i < numElements - 1 && current != NULL; ++i) {
        current = current->next;
        tail->next = current;
        tail = tail->next;
    }
    tail->next = NULL;
    return newHead;
}

void printList(Node *head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    Node *head = NULL;
    insertAtEnd(&head, 1);
    insertAtEnd(&head, 2);
    insertAtEnd(&head, 3);
    insertAtEnd(&head, 4);
    insertAtEnd(&head, 5);

    printf("Original list: ");
    printList(head);

    int start = 2, numElements = 3;
    Node *extracted = extractSublist(head, start, numElements);
    printf("Extracted sublist: ");
    printList(extracted);

    freeList(head);
    freeList(extracted);
    return 0;
}