#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void append(struct Node** head_ref, int new_data) {
    if (head_ref == NULL) {
        return;
    }
    struct Node* newNode = createNode(new_data);
    struct Node* last = *head_ref;
    if (*head_ref == NULL) {
        *head_ref = newNode;
        return;
    }
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = newNode;
}

void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

void freeList(struct Node* head) {
    while (head != NULL) {
        struct Node* tmp = head;
        head = head->next;
        free(tmp);
    }
}

void swapFirstAndLast(struct Node** head_ref) {
    if (head_ref == NULL || *head_ref == NULL || (*head_ref)->next == NULL) {
        return;
    }

    struct Node* secLast = NULL;
    struct Node* last = *head_ref;

    while (last->next != NULL) {
        secLast = last;
        last = last->next;
    }

    if (secLast == *head_ref) {
        last->next = *head_ref;
        (*head_ref)->next = NULL;
        *head_ref = last;
        return;
    }

    struct Node* temp = (*head_ref)->next;
    secLast->next = *head_ref;
    (*head_ref)->next = NULL;
    last->next = temp;
    *head_ref = last;
}

int main(void) {
    struct Node* head = NULL;

    append(&head, 1);
    append(&head, 2);
    append(&head, 3);
    append(&head, 4);
    append(&head, 5);

    swapFirstAndLast(&head);
    printList(head);

    freeList(head);

    return 0;
}