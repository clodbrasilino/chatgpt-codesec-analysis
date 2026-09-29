#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void shiftFirstToEnd(Node** head) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }

    Node* current = *head;
    Node* second = (*head)->next;

    while (second->next != NULL) {
        current = current->next;
        second = second->next;
    }

    current->next = NULL;
    second->next = *head;
    *head = second;
}

void printList(Node* head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    Node* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);

    printf("Original list: ");
    printList(head);

    shiftFirstToEnd(&head);

    printf("List after shifting first to end: ");
    printList(head);

    // Free the list
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}