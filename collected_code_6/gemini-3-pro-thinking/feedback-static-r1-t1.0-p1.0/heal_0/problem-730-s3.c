#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* create_node(int data);
void append_node(Node** head, int data);
void remove_consecutive_duplicates(Node* head);
void print_list(const Node* head);
void free_list(Node* head);

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void append_node(Node** head, int data) {
    if (!head) {
        return;
    }
    Node* new_node = create_node(data);
    if (!*head) {
        *head = new_node;
        return;
    }
    Node* current = *head;
    while (current->next) {
        current = current->next;
    }
    current->next = new_node;
}

void remove_consecutive_duplicates(Node* head) {
    if (!head) {
        return;
    }
    Node* current = head;
    while (current->next) {
        if (current->data == current->next->data) {
            Node* duplicate = current->next;
            current->next = duplicate->next;
            free(duplicate);
        } else {
            current = current->next;
        }
    }
}

void print_list(const Node* head) {
    const Node* current = head;
    while (current) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void free_list(Node* head) {
    Node* current = head;
    while (current) {
        Node* next_node = current->next;
        free(current);
        current = next_node;
    }
}

int main(void) {
    Node* head = NULL;
    int values[] = {1, 1, 1, 2, 3, 3, 4, 5, 5, 5, 1, 1, 6};
    size_t num_values = sizeof(values) / sizeof(values[0]);

    for (size_t i = 0; i < num_values; ++i) {
        append_node(&head, values[i]);
    }

    print_list(head);
    remove_consecutive_duplicates(head);
    print_list(head);
    
    free_list(head);
    head = NULL;

    return EXIT_SUCCESS;
}