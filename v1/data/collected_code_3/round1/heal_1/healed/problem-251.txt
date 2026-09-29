#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if(node==NULL){
        return NULL;
    }
    node->data = data;
    node->next = NULL;

    return node;
}

Node* insertBeforeEveryElement(Node* head, int data) {
    Node* current = head;
    Node* prev = NULL;

    while (current != NULL) {
        Node* node = newNode(data);
        if (node == NULL){
            return NULL;
        }
        if (prev == NULL) {
            node->next = head;
            head = node;
        } else {
            node->next = current;
            prev->next = node;
        }
        prev = current;
        current = current->next;
    }
    return head;
}

void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    Node* head = newNode(1);
    if(head == NULL){
        return 1;
    }
    head->next = newNode(2);
    if(head->next == NULL){
        free(head);
        return 1;
    }
    head->next->next = newNode(3);
    if(head->next->next == NULL){
        free(head->next);
        free(head);
        return 1;
    }
    head->next->next->next = newNode(4);
    if(head->next->next->next == NULL){
        free(head->next->next);
        free(head->next);
        free(head);
        return 1;
    }
    head->next->next->next->next = newNode(5);
    if(head->next->next->next->next == NULL){
        free(head->next->next->next);
        free(head->next->next);
        free(head->next);
        free(head);
        return 1;
    }

    printf("Original list: ");
    printList(head);

    head = insertBeforeEveryElement(head, 0);
    if(head == NULL){
        return 1;
    }

    printf("Modified list: ");
    printList(head);

    return 0;
}