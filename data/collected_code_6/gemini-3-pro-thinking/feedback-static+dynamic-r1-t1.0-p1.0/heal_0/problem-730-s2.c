#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* create_node(int data);
void append_node(struct Node** head, int data);
void remove_consecutive_duplicates(struct Node* head);
void free_list(struct Node* head);
void print_list(const struct Node* head);

struct Node* create_node(int data) {
    struct Node* new_node = malloc(sizeof(struct Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void append_node(struct Node** head, int data) {
    if (head == NULL) {
        return;
    }
    struct Node* new_node = create_node(data);
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    struct Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

void remove_consecutive_duplicates(struct Node* head) {
    if (head == NULL) {
        return;
    }
    struct Node* current = head;
    while (current->next != NULL) {
        if (current->data == current->next->data) {
            struct Node* duplicate = current->next;
            current->next = current->next->next;
            free(duplicate);
        } else {
            current = current->next;
        }
    }
}

void free_list(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        struct Node* next_node = current->next;
        free(current);
        current = next_node;
    }
}

void print_list(const struct Node* head) {
    const struct Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(void) {
    struct Node* head = NULL;

    append_node(&head, 1);
    append_node(&head, 1);
    append_node(&head, 2);
    append_node(&head, 3);
    append_node(&head, 3);
    append_node(&head, 3);
    append_node(&head, 4);
    append_node(&head, 5);
    append_node(&head, 5);

    print_list(head);
    remove_consecutive_duplicates(head);
    print_list(head);

    free_list(head);
    head = NULL;

    return 0;
}