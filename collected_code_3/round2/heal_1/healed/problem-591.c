#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void swap(struct Node** head_ref) {
    struct Node* temp = *head_ref;
    struct Node* prev = NULL;

    if (temp == NULL || temp->next == NULL)
        return;

    while (temp->next != NULL) {
        prev = temp;
        temp = temp->next;
    }

    prev->next = *head_ref;
    temp->next = (*head_ref)->next;
    (*head_ref)->next = NULL;
    *head_ref = temp;
}

void push(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    if (new_node == NULL) {
        printf("Failed to allocate memory for new node");
        exit(1);
    }

    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d  ", node->data);
        node = node->next;
    }
}

int main() {
    struct Node* start = NULL;

    push(&start, 12);
    push(&start, 56);
    push(&start, 2);
    push(&start, 11);

    printf("Linked list before calling swap function\n");
    printList(start);

    swap(&start);

    printf("\nLinked list after calling swap function\n");
    printList(start);

    return 0;
}