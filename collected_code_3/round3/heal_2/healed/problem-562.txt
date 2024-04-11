#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

int maxLength(struct Node* head) {
    int maxCount = 0;
    while (head != NULL) {
        struct Node* temp = head;
        int count = 0;
        while (temp != NULL && temp->data == head->data) {
            count++;
            temp = temp->next;
        }
        maxCount = (count > maxCount) ? count : maxCount;
        head = head->next;
    }
    return maxCount;
}

struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));

    if (node == NULL) {
        return NULL;
    }

    node->data = data;
    node->next = NULL;

    return node;
}

int main() {
    struct Node* head = newNode(1);

    if (head == NULL) {
        return 1;
    }

    struct Node* current = head;
    struct Node* newNodePointer = NULL;
    
    newNodePointer = newNode(1);
    if (newNodePointer != NULL) {
        current->next = newNodePointer;
        current = current->next;
    }
    
    newNodePointer = newNode(2);
    if (newNodePointer != NULL) {
        current->next = newNodePointer;
        current = current->next;
    }
    
    newNodePointer = newNode(2);
    if (newNodePointer != NULL) {
        current->next = newNodePointer;
        current = current->next;
    }
    
    newNodePointer = newNode(2);
    if (newNodePointer != NULL) {
        current->next = newNodePointer;
        current = current->next;
    }
    
    newNodePointer = newNode(3);
    if (newNodePointer != NULL) {
        current->next = newNodePointer;
        current = current->next;
    }
    
    newNodePointer = newNode(3);
    if (newNodePointer != NULL) {
        current->next = newNodePointer;
        current = current->next;
    }
    
    newNodePointer = newNode(3);
    if (newNodePointer != NULL) {
        current->next = newNodePointer;
        current = current->next;
    }
    
    newNodePointer = newNode(3);
    if (newNodePointer != NULL) {
        current->next = newNodePointer;
        current = current->next;
    }

    printf("Maximum length of sublist is %d\n", maxLength(head));

    return 0;
}