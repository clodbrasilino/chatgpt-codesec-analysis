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
        Node* temp = current->next;
        free(current);
        current = temp;
    }
}

void splitList(Node* head, int k, Node** firstPart, Node** secondPart) {
    if (!firstPart || !secondPart) {
        return;
    }
    
    if (k <= 0 || !head) {
        *firstPart = NULL;
        *secondPart = head;
        return;
    }

    Node* current = head;
    int count = 1;
    
    while (count < k && current->next) {
        current = current->next;
        count++;
    }

    *firstPart = head;
    *secondPart = current->next;
    current->next = NULL;
}

void printList(const Node* head) {
    const Node* current = head;
    while (current) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    Node* head = NULL;
    Node* firstPart = NULL;
    Node* secondPart = NULL;

    for (int i = 1; i <= 10; i++) {
        appendNode(&head, i);
    }

    splitList(head, 4, &firstPart, &secondPart);

    printList(firstPart);
    printList(secondPart);

    freeList(firstPart);
    freeList(secondPart);

    return EXIT_SUCCESS;
}