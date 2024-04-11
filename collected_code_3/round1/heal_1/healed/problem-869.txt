#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} Node;

Node* newNode(int data) {
    Node* temp = (Node*)malloc(sizeof(Node));

    if (temp == NULL) {
        return NULL;
    }

    temp->data = data;
    temp->next = NULL;
    return temp;
}

Node* removeOutsideRange(Node* head, int min, int max) {
    if (head == NULL)
        return NULL;

    head->next = removeOutsideRange(head->next, min, max);

    if (head->data < min || head->data > max) {
        Node* res = head->next;
        free(head);
        return res;
    }

    return head;
}

void printList(Node* head) {
    while (head) {
        printf("%d ", head->data);
        head = head->next;
    }
}

int main() {
    Node* head = newNode(7);
    if (head == NULL) {
        return -1;
    }

    head->next = newNode(3);
    if (head->next == NULL) {
        free(head);
        return -1;
    }

    head->next->next = newNode(5);
    if (head->next->next == NULL) {
        free(head->next);
        free(head);
        return -1;
    }

    head->next->next->next = newNode(1);
    if (head->next->next->next == NULL) {
        free(head->next->next);
        free(head->next);
        free(head);
        return -1;
    }

    head->next->next->next->next = newNode(8);
    if (head->next->next->next->next == NULL) {
        free(head->next->next->next);
        free(head->next->next);
        free(head->next);
        free(head);
        return -1;
    }

    head->next->next->next->next->next = newNode(10);
    if (head->next->next->next->next->next == NULL) {
        free(head->next->next->next);
        free(head->next->next);
        free(head->next);
        free(head);
        return -1;
    }

    int min = 3, max = 8;
    head = removeOutsideRange(head, min, max);
    printList(head);
    return 0;
}