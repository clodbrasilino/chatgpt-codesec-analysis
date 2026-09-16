#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

void shift_first_to_end(Node **head) {
    if (head == NULL || *head == NULL || (*head)->next == NULL) {
        return;
    }
    Node *first = *head;
    *head = first->next;
    Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = first;
    first->next = NULL;
}

Node *create_node(int data) {
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->next = NULL;
    return node;
}

void append_node(Node **head, int data) {
    if (head == NULL) {
        return;
    }
    if (*head == NULL) {
        *head = create_node(data);
        return;
    }
    Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = create_node(data);
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
}

void print_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    Node *head = NULL;
    append_node(&head, 1);
    append_node(&head, 2);
    append_node(&head, 3);
    append_node(&head, 4);

    print_list(head);
    shift_first_to_end(&head);
    print_list(head);

    Node *empty = NULL;
    shift_first_to_end(&empty);

    Node *single = NULL;
    append_node(&single, 5);
    shift_first_to_end(&single);

    free_list(head);
    free_list(single);

    return 0;
}