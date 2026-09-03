#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

Node* splitList(Node* head, int length) {
    if (head == NULL || length <= 0) {
        return NULL;
    }

    Node* current = head;
    for (int i = 1; i < length && current != NULL; ++i) {
        current = current->next;
    }

    if (current == NULL) {
        return NULL;
    }

    Node* newHead = current->next;
    current->next = NULL;

    return newHead;
}

int main() {
    Node* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);
    head->next->next->next->next = createNode(5);

    int length = 3;
    Node* secondPart = splitList(head, length);

    Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");

    current = secondPart;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");

    freeList(head);
    freeList(secondPart);

    return 0;
}