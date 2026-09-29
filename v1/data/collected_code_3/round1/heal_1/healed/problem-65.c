#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

int sumList(struct Node* head) {
    if (head == NULL) {
        return 0;
    } else {
        return head->data + sumList(head->next);
    }
}

struct Node* createNewNode(int data) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    
    if (newNode == NULL) {
        return NULL;
    }
    
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

int main() {
    struct Node* head = createNewNode(5);
    if (head == NULL) {
        return 1;
    }

    head->next = createNewNode(10);
    if (head->next == NULL) {
        return 1;
    }

    head->next->next = createNewNode(15);
    if (head->next->next == NULL) {
        return 1;
    }

    head->next->next->next = createNewNode(20);
    if (head->next->next->next == NULL) {
        return 1;
    }

    printf("Sum of elements in linked list is: %d\n", sumList(head));

    return 0;
}