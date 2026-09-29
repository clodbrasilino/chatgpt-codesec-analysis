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
    Node* temp = *head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void freeList(Node* head) {
    Node* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void findMaxSublist(Node* head, Node** maxSublistHead, int* maxLength) {
    if (!head || !maxSublistHead || !maxLength) return;

    *maxSublistHead = NULL;
    *maxLength = 0;

    Node* current = head;
    Node* currentSublistHead = head;
    int currentLength = 1;

    while (current && current->next) {
        if (current->data < current->next->data) {
            currentLength++;
        } else {
            if (currentLength > *maxLength) {
                *maxLength = currentLength;
                *maxSublistHead = currentSublistHead;
            }
            currentSublistHead = current->next;
            currentLength = 1;
        }
        current = current->next;
    }

    if (currentLength > *maxLength) {
        *maxLength = currentLength;
        *maxSublistHead = currentSublistHead;
    }
}

void printSublist(Node* head, int length) {
    if (!head) return;
    Node* temp = head;
    for (int i = 0; i < length && temp; i++) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main(void) {
    Node* head = NULL;
    
    appendNode(&head, 1);
    appendNode(&head, 2);
    appendNode(&head, 5);
    appendNode(&head, 3);
    appendNode(&head, 4);
    appendNode(&head, 6);
    appendNode(&head, 8);
    appendNode(&head, 9);
    appendNode(&head, 2);
    
    Node* maxSublistHead = NULL;
    int maxLength = 0;
    
    findMaxSublist(head, &maxSublistHead, &maxLength);
    
    if (maxSublistHead) {
        printSublist(maxSublistHead, maxLength);
    }
    
    freeList(head);
    
    return 0;
}