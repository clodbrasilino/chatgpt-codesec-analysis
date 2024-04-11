#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* removeNegatives(Node* head) {
    Node* current = head;
    Node* prev = NULL;

    while (current != NULL) {
        if (current->data < 0) {
            if (prev == NULL) {
                head = current->next;
            } else {
                prev->next = current->next;
            }
            Node* temp = current;
            current = current->next;
            free(temp);
        } else {
            prev = current;
            current = current->next;
        }
    }
    return head;
}

Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if(node == NULL){
       return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    Node* head = newNode(-1);
    if(head == NULL){
        return 1;
    }
    head->next = newNode(2);
    if(head->next == NULL){
        free(head);
        return 1;
    }

    head->next->next = newNode(-3);
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

    head->next->next->next->next = newNode(-5);
    if(head->next->next->next->next == NULL){
        free(head->next->next->next);
        free(head->next->next);
        free(head->next);
        free(head);
        return 1;
    }

    printf("Original list: ");
    printList(head);

    head = removeNegatives(head);

    printf("List after removing negatives: ");
    printList(head);

    return 0;
}