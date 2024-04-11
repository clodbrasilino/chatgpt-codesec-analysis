#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* copyList(Node* head) {
    if (head == NULL) {
        return NULL;
    }

    Node* newHead = (Node*)malloc(sizeof(Node));
    if(newHead == NULL) {
        return NULL;
    }

    newHead->data = head->data;
    newHead->next = copyList(head->next);

    return newHead;
}

int main() {
    Node* head = (Node*)malloc(sizeof(Node));
    if(head == NULL) {
        return -1;
    }

    head->data = 1;
    head->next = NULL;

    Node* newHead = copyList(head);
    if(newHead == NULL) {
        free(head);
        return -1;
    }

    printf("Original list: %d\n", head->data);
    printf("Copied list: %d\n", newHead->data);

    free(head);
    free(newHead);

    return 0;
}