#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* createNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void removeNegatives(Node **head) {
    Node *current = *head;
    Node *prev = NULL;

    while (current != NULL) {
        if (current->data < 0) {
            if (prev == NULL) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            current = (prev == NULL) ? *head : prev->next;
        } else {
            prev = current;
            current = current->next;
        }
    }
}

void printList(Node *node) {
    while (node != NULL) {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

int main() {
    Node *head = createNode(1);
    head->next = createNode(-2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(-4);

    printf("Original list: ");
    printList(head);

    removeNegatives(&head);

    printf("List after removing negatives: ");
    printList(head);

    // Free remaining nodes
    Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}