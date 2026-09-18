#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

void insert_before_each(Node** head, int value);
Node* create_node(int value);
void append_node(Node** head, int value);
void free_list(Node* head);
void print_list(const Node* head);

Node* create_node(int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

void insert_before_each(Node** head, int value) {
    if (head == NULL) {
        return;
    }

    Node* current = *head;
    Node* previous = NULL;

    while (current != NULL) {
        Node* new_node = create_node(value);
        new_node->next = current;

        if (previous == NULL) {
            *head = new_node;
        } else {
            previous->next = new_node;
        }

        previous = current;
        current = current->next;
    }
}

void append_node(Node** head, int value) {
    Node* new_node;
    Node* current;

    if (head == NULL) {
        return;
    }

    new_node = create_node(value);

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

void free_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* next_node = current->next;
        free(current);
        current = next_node;
    }
}

void print_list(const Node* head) {
    const Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    Node* head = NULL;

    append_node(&head, 1);
    append_node(&head, 2);
    append_node(&head, 3);
    append_node(&head, 4);

    print_list(head);

    insert_before_each(&head, 99);

    print_list(head);

    free_list(head);
    head = NULL;

    return EXIT_SUCCESS;
}