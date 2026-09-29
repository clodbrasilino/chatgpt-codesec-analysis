#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;


Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) return NULL;
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
        if(*lastPtr == NULL) break;
        lastPtr = &((*lastPtr)->next);
        *lastPtr = newNode(count);
        if(*lastPtr == NULL) break;
        lastPtr = &((*lastPtr)->next);
        head = head->next;
    }
    return newHead;
}

void freeList(Node* node) {
    Node* temp;
    while (node != NULL) {
        temp = node;
        node = node->next;
        free(temp);
    }
}

int main() {
    Node* head = newNode(1);
    if(head == NULL) return 1;
    Node* temp = head;

    for(int i = 0; i < 7; i++) {
        temp->next = newNode(i/2 + 1);
        if(temp->next == NULL) {
            freeList(head);
            return 1;
        }
        temp = temp->next;
    }

    printf("Original list: ");
    printList(head);

    printf("\nModified run-length encoding: ");
    Node* newHead = modifiedRLE(head);
    if(newHead == NULL) {
        freeList(head);
        return 1;
    }
    printList(newHead);

    freeList(head);
    freeList(newHead);
    return 0;
}
