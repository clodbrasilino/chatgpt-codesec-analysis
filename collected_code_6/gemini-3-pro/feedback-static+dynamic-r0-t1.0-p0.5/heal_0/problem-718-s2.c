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
    if (!head) return;
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

Node* createAlternateList(Node* head) {
    Node* newList = NULL;
    Node* current = head;
    int toggle = 1;

    while (current) {
        if (toggle) {
            appendNode(&newList, current->data);
        }
        toggle = !toggle;
        current = current->next;
    }
    return newList;
}

void printList(Node* head) {
    Node* current = head;
    while (current) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void freeList(Node* head) {
    Node* current = head;
    while (current) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

int main(void) {
    Node* originalList = NULL;
    
    for (int i = 1; i <= 10; i++) {
        appendNode(&originalList, i);
    }

    Node* alternateList = createAlternateList(originalList);

    printList(originalList);
    printList(alternateList);

    freeList(originalList);
    freeList(alternateList);

    return 0;
}