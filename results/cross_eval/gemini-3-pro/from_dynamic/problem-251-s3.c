#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertBeforeEach(struct Node** head, int val) {
    if (head == NULL || *head == NULL) {
        return;
    }

    struct Node* current = *head;
    struct Node* prev = NULL;

    while (current != NULL) {
        struct Node* newNode = createNode(val);
        newNode->next = current;

        if (prev == NULL) {
            *head = newNode;
        } else {
            prev->next = newNode;
        }

        prev = current;
        current = current->next;
    }
}

void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void freeList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        struct Node* next = current->next;
        free(current);
        current = next;
    }
}

int main(void) {
    struct Node* head = createNode(1);
    if (head == NULL) {
        return 1;
    }
    head->next = createNode(2);
    if (head->next == NULL) {
        freeList(head);
        return 1;
    }
    head->next->next = createNode(3);
    if (head->next->next == NULL) {
        freeList(head);
        return 1;
    }

    insertBeforeEach(&head, 0);
    printList(head);
    freeList(head);

    return 0;
}