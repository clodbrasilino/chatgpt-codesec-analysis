#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* createNode(int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Node* removeConsecutiveDuplicates(Node *head) {
    if (!head) return head;

    Node *current = head;
    while (current && current->next) {
        if (current->data == current->next->data) {
            Node *temp = current->next;
            current->next = current->next->next;
            free(temp);
        } else {
            current = current->next;
        }
    }
    return head;
}

void printList(Node *head) {
    Node *temp = head;
    while (temp) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    Node *head = createNode(1);
    head->next = createNode(1);
    head->next->next = createNode(2);
    head->next->next->next = createNode(2);
    head->next->next->next->next = createNode(3);
    head->next->next->next->next->next = createNode(3);
    head->next->next->next->next->next->next = createNode(4);

    printf("Original list: ");
    printList(head);

    head = removeConsecutiveDuplicates(head);

    printf("List after removing consecutive duplicates: ");
    printList(head);

    // Free the allocated memory
    while (head) {
        Node *temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}