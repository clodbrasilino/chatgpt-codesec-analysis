#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

void swapFirstLast(struct Node **head) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }

    struct Node *first = *head;
    struct Node *second_last = NULL;
    struct Node *last = *head;

    while (last->next != NULL) {
        second_last = last;
        last = last->next;
    }

    if (first->next == last) {
        last->next = first;
        first->next = NULL;
        *head = last;
        return;
    }

    last->next = first->next;
    second_last->next = first;
    first->next = NULL;
    *head = last;
}

struct Node *createNode(int data) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void appendNode(struct Node **head, int data) {
    struct Node *newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void printList(struct Node *head) {
    struct Node *temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void freeList(struct Node *head) {
    struct Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main(void) {
    struct Node *head = NULL;

    appendNode(&head, 10);
    appendNode(&head, 20);
    appendNode(&head, 30);
    appendNode(&head, 40);
    appendNode(&head, 50);

    printf("Original list: ");
    printList(head);

    swapFirstLast(&head);

    printf("After swapping first and last: ");
    printList(head);

    freeList(head);
    return 0;
}