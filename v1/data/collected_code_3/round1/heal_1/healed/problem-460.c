#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* newNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(0);  
    } 
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void getFirst(struct Node* node) {
    if (node != NULL) {
        printf("%d ", node->data);
    }
}

int main() {
    struct Node* head = newNode(1);
    struct Node* current = head;

    for (int i = 2; i <= 5; ++i) {
        current->next = newNode(i);
        current = current->next;
    }

    getFirst(head);

    return 0;
}