#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

int list_sum(struct Node* head) {
    if (head == NULL) {
        return 0;
    }
    return head->data + list_sum(head->next);
}

struct Node* create_node(int data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void append_node(struct Node** head, int data) {
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

void free_list(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        struct Node* next = current->next;
        free(current);
        current = next;
    }
}

int main(void) {
    struct Node* head = NULL;
    append_node(&head, 10);
    append_node(&head, 20);
    append_node(&head, 30);
    append_node(&head, 40);
    append_node(&head, 50);

    int sum = list_sum(head);
    printf("Sum of list elements: %d\n", sum);

    free_list(head);
    return 0;
}