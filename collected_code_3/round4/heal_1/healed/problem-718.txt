#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory error\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Node* createAlternateList(Node* head) {
    if (!head)
        return NULL;

    Node* alternateHead = createNode(head->data);
    if (!alternateHead)
        return NULL;
        
    Node* alternateCurrent = alternateHead;
    head = head->next;

    while (head != NULL && head->next != NULL) {
        alternateCurrent->next = createNode(head->next->data);
        if (!alternateCurrent->next)
            return NULL;

        alternateCurrent = alternateCurrent->next;
        head = head->next->next;
    }

    return alternateHead;
}

void printList(Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main() {
    Node* head = createNode(1);
    if (!head)
        return 1;

    head->next = createNode(2);
    if (!head->next)
        return 1;
        
    head->next->next = createNode(3);
    if (!head->next->next)
        return 1;

    head->next->next->next = createNode(4);
    if (!head->next->next->next)
        return 1;

    head->next->next->next->next = createNode(5);
    if (!head->next->next->next->next)
        return 1;

    printf("Original List: ");
    printList(head);

    Node* alternateHead = createAlternateList(head);
    if (!alternateHead)
        return 1;

    printf("Alternate List: ");
    printList(alternateHead);

    return 0;
}