#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL) {
        printf("Error creating a new node.\n");
        exit(0);
    }
    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}

int countNodes(Node* head) {
    Node* current = head;
    int count = 0;

    while(current != NULL) {
        count++;
        current = current->next;
    }

    return count;
}

int main() {
    Node* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);

    printf("Number of nodes: %d\n", countNodes(head));

    return 0;
}