#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *next;
} Node;

int countInRange(Node *head, int lower, int upper) {
    if (head == NULL) return 0;
    Node *current = head;
    int count = 0;
    while (current != NULL) {
        if (current->value >= lower && current->value <= upper) {
            count++;
        }
        current = current->next;
    }
    return count;
}

Node* createNode(int value) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) return NULL;
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

void insertAtEnd(Node **head, int value) {
    Node *newNode = createNode(value);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

int main() {
    Node *list = NULL;
    insertAtEnd(&list, 10);
    insertAtEnd(&list, 20);
    insertAtEnd(&list, 30);
    insertAtEnd(&list, 40);
    insertAtEnd(&list, 50);

    int lowerBound = 20;
    int upperBound = 40;

    int result = countInRange(list, lowerBound, upperBound);
    printf("Count: %d\n", result);

    // Free the list
    Node *current = list;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }

    return 0;
}