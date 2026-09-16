#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void shiftLastToFirst(struct Node** head_ref);
void push(struct Node** head_ref, int new_data);
void printList(struct Node* node);
void freeList(struct Node* node);

void shiftLastToFirst(struct Node** head_ref) {
    struct Node* secLast = NULL;
    struct Node* last = NULL;

    if (!head_ref || !(*head_ref) || !(*head_ref)->next) {
        return;
    }

    last = *head_ref;

    while (last->next != NULL) {
        secLast = last;
        last = last->next;
    }

    secLast->next = NULL;
    last->next = *head_ref;
    *head_ref = last;
}

void push(struct Node** head_ref, int new_data) {
    struct Node* new_node = NULL;
    
    if (!head_ref) {
        return;
    }

    new_node = (struct Node*)malloc(sizeof(struct Node));
    if (!new_node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

void freeList(struct Node* node) {
    struct Node* tmp = NULL;
    while (node != NULL) {
        tmp = node;
        node = node->next;
        free(tmp);
    }
}

int main(void) {
    struct Node* start = NULL;

    push(&start, 5);
    push(&start, 4);
    push(&start, 3);
    push(&start, 2);
    push(&start, 1);

    printList(start);

    shiftLastToFirst(&start);

    printList(start);

    freeList(start);
    start = NULL;

    return 0;
}