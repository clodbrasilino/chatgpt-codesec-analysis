#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void appendNode(Node** head, int data) {
    if (!head) {
        return;
    }
    Node* newNode = createNode(data);
    if (!*head) {
        *head = newNode;
        return;
    }
    Node* current = *head;
    while (current->next) {
        current = current->next;
    }
    current->next = newNode;
}

void removeKthNode(Node** head, int k) {
    if (!head || !*head || k <= 0) {
        return;
    }

    Node* current = *head;
    Node* prev = NULL;

    if (k == 1) {
        *head = current->next;
        free(current);
        return;
    }

    for (int i = 1; current != NULL && i < k; ++i) {
        prev = current;
        current = current->next;
    }

    if (!current) {
        return;
    }

    prev->next = current->next;
    free(current);
}

void printList(Node* head) {
    Node* current = head;
    while (current) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

void freeList(Node* head) {
    Node* current = head;
    while (current) {
        Node* next = current->next;
        free(current);
        current = next;
    }
}

int main(void) {
    Node* head = NULL;

    appendNode(&head, 10);
    appendNode(&head, 20);
    appendNode(&head, 30);
    appendNode(&head, 40);
    appendNode(&head, 50);

    printList(head);

    removeKthNode(&head, 3);
    printList(head);

    removeKthNode(&head, 1);
    printList(head);

    removeKthNode(&head, 10); 
    printList(head);

    freeList(head);

    return 0;
}