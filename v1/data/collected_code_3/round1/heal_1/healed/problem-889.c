#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* reverseList(Node* head) {
    Node* prev = NULL;
    Node* current = head;
    Node* next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
}

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory error\n");
        exit(-1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void push(Node** head_ref, int new_data) {
    Node* new_node = createNode(new_data);
    if (new_node == NULL) {
        return;
    }
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void printList(Node* head) {
    while (head != NULL) {
        printf(" %d ", head->data);
        head = head->next;
    }
}

int main() {
    Node* head = NULL;
    push(&head, 20);
    push(&head, 4);
    push(&head, 15);
    push(&head, 85);

    printf("Given linked list\n");
    printList(head);
    head = reverseList(head);

    printf("\nReversed Linked list \n");
    printList(head);
    return 0;
}