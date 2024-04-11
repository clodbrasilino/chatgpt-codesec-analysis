#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if(node == NULL){
        return NULL;
    }
    
    node->data = data;
    node->next = NULL;
    return node;
}

void removeDuplicates(Node* head) {
    Node* current = head;
    Node* next_next;

    if (current == NULL)
        return;

    while (current->next != NULL) {
        if (current->data == current->next->data) {
            next_next = current->next->next;
            free(current->next);
            current->next = next_next;
        } else {
            current = current->next;
        }
    }
}

void printList(Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
}

int main() {
    Node* head = newNode(10);
    if(head == NULL){
        return -1;
    }

    head->next = newNode(20);
    if(head->next == NULL){
        return -1;
    }

    head->next->next = newNode(20);
    if(head->next->next == NULL){
        return -1;
    }

    head->next->next->next = newNode(30);
    if(head->next->next->next == NULL){
        return -1;
    }

    head->next->next->next->next = newNode(30);
    if(head->next->next->next->next == NULL){
        return -1;
    }

    head->next->next->next->next->next = newNode(40);
    if(head->next->next->next->next->next == NULL){
        return -1;
    }

    printf("Before removing duplicates: ");
    printList(head);

    removeDuplicates(head);

    printf("\nAfter removing duplicates: ");
    printList(head);

    return 0;
}