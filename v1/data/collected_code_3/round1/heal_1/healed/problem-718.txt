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
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Node* createAlternateList(Node* head) {
    if (head == NULL)
        return NULL;

    Node* alternateHead = createNode(head->data);
    if(!alternateHead)
        return NULL;
    
    Node* alternateCurrent = alternateHead;
    while (head && head->next) {
        head = head->next->next;
        if (head) {
            Node* temp = createNode(head->data);
            if(!temp)
                return NULL;
            alternateCurrent->next = temp;
            alternateCurrent = alternateCurrent->next;
        }
    }
    return alternateHead;
}

void printList(Node* head) {
    while (head) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main() {
    Node* head = createNode(1);
    if(!head)
        return 1;

    Node* temp = createNode(2);
    if(!temp)
        return 1;
    head->next = temp;

    temp = createNode(3);
    if(!temp)
        return 1;
    head->next->next = temp;

    temp = createNode(4);
    if(!temp)
        return 1;
    head->next->next->next = temp;

    temp = createNode(5);
    if(!temp)
        return 1;
    head->next->next->next->next = temp;

    printf("Original List: ");
    printList(head);

    Node* alternateList = createAlternateList(head);
    printf("Alternate List: ");
    printList(alternateList);

    return 0;
}