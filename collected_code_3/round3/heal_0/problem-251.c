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

Node* insertBeforeEveryElement(Node* head, int x) {
    Node* dummy = newNode(0);
    dummy->next = head;
    Node* prev = dummy;
    Node* curr = head;

    while (curr != NULL) {
        Node* temp = newNode(x);
        prev->next = temp;
        temp->next = curr;
        prev = curr;
        curr = curr->next;
    }

    head = dummy->next;
    free(dummy);
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
    head->next = newNode(2);
    head->next->next = newNode(3);
    head->next->next->next = newNode(4);

    printf("Original list: ");
    printList(head);

    head = insertBeforeEveryElement(head, 0);

    printf("Modified list: ");
    printList(head);

    return 0;
}