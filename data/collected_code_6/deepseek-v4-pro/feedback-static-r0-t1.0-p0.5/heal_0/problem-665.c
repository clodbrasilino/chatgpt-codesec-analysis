#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *create_node(int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void append_node(Node **head, int data) {
    Node *new_node = create_node(data);
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

void shift_first_to_end(Node **head) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }
    Node *first = *head;
    *head = first->next;
    first->next = NULL;
    Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = first;
}

void print_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

int main(void) {
    Node *head = NULL;
    append_node(&head, 10);
    append_node(&head, 20);
    append_node(&head, 30);
    append_node(&head, 40);
    append_node(&head, 50);

    printf("Original list: ");
    print_list(head);

    shift_first_to_end(&head);

    printf("After shifting first to end: ");
    print_list(head);

    free_list(head);
    return 0;
}