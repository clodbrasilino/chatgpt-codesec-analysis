#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed.\n");
        exit(0);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertNodeAtEnd(Node** head, int data) {
    Node* newNode = createNode(data);
    if (!*head) {
        *head = newNode;
        return;
    }
    Node* lastNode = *head;
    while (lastNode->next) {
        lastNode = lastNode->next;
    }
    lastNode->next = newNode;
}

int getNthNode(Node* head, int n) {
    int index = 0;
    while (head) {
        if (index == n)
            return head->data;
        index++;
        head = head->next;
    }
    printf("The list is not long enough.\n");
    exit(0);
}

int main() {
    Node* head = NULL;
    for (int i = 0; i < 10; i++)
        insertNodeAtEnd(&head, i+1);

    int n = 5;
    printf("The data at node %d is: %d.\n",n, getNthNode(head, n));
    return 0;
}