#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

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

    if (secLast != NULL) {
        secLast->next = *head_ref;
    }

    last->next = (*head_ref)->next;
    (*head_ref)->next = NULL;
    *head_ref = last;
}

void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

void push(struct Node** head_ref, int new_data) {
    if (head_ref == NULL) {
        return;
    }
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    if (new_node == NULL) {
        exit(EXIT_FAILURE);
    }
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void freeList(struct Node** head_ref) {
    if (head_ref == NULL) {
        return;
    }
    struct Node* current = *head_ref;
    struct Node* next = NULL;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *head_ref = NULL;
}

int main() {
    struct Node* start = NULL;

    push(&start, 5);
    push(&start, 4);
    push(&start, 3);
    push(&start, 2);
    push(&start, 1);

    printList(start);
    swapFirstAndLast(&start);
    printList(start);

    freeList(&start);

    return 0;
}