#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

void printList(Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
}

Node* modifiedRLE(Node* head) {
    Node* newHead = NULL;
    Node** lastPtr = &newHead;
    while (head != NULL) {
        int count = 1;
        while (head->next != NULL && head->data == head->next->data) {
            count++;
            head = head->next;
        }
        *lastPtr = newNode(head->data);
        lastPtr = &((*lastPtr)->next);
        *lastPtr = newNode(count);
        lastPtr = &((*lastPtr)->next);
        head = head->next;
    }
    return newHead;
}

int main() {
    Node* head = newNode(1);
    head->next = newNode(1);
    head->next->next = newNode(2);
    head->next->next->next = newNode(3);
    head->next->next->next->next = newNode(3);
    head->next->next->next->next->next = newNode(3);
    head->next->next->next->next->next->next = newNode(4);
    head->next->next->next->next->next->next->next = newNode(4);
    printf("Original list: ");
    printList(head);
    printf("\nModified run-length encoding: ");
    Node* newHead = modifiedRLE(head);
    printList(newHead);
    return 0;
}