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

void freeList(Node* head) {
    Node* current = head;
    while (current) {
        Node* next = current->next;
        free(current);
        current = next;
    }
}

const Node* getNthNode(const Node* head, int n) {
    if (n < 0) {
        return NULL;
    }
    const Node* current = head;
    int count = 0;
    while (current) {
        if (count == n) {
            return current;
        }
        count++;
        current = current->next;
    }
    return NULL;
}

int main(void) {
    Node* head = NULL;
    
    appendNode(&head, 10);
    appendNode(&head, 20);
    appendNode(&head, 30);
    appendNode(&head, 40);
    appendNode(&head, 50);

    int n = 2;
    const Node* nthNode = getNthNode(head, n);
    
    if (nthNode) {
        printf("Node at index %d: %d\n", n, nthNode->data);
    } else {
        printf("Node at index %d not found.\n", n);
    }

    freeList(head);
    
    return EXIT_SUCCESS;
}