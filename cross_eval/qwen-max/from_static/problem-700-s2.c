#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

int countRange(struct Node *head, int lower, int upper) {
    int count = 0;
    struct Node *current = head;
    while (current != NULL) {
        if (current->data >= lower && current->data <= upper) {
            count++;
        }
        current = current->next;
    }
    return count;
}

struct Node* createNode(int data) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertAtEnd(struct Node **head, int data) {
    struct Node *newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void freeList(struct Node *head) {
    struct Node *current = head;
    while (current != NULL) {
        struct Node *next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    struct Node *head = NULL;
    insertAtEnd(&head, 5);
    insertAtEnd(&head, 10);
    insertAtEnd(&head, 15);
    insertAtEnd(&head, 20);

    int lower = 7;
    int upper = 17;

    int result = countRange(head, lower, upper);
    printf("Number of elements in range [%d, %d]: %d\n", lower, upper, result);

    freeList(head);
    return 0;
}