#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

void shift_first_to_end(struct Node **head) {
    if (head == NULL || *head == NULL || (*head)->next == NULL) {
        return;
    }

    struct Node *first = *head;
    *head = first->next;
    first->next = NULL;

    struct Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = first;
}

struct Node *create_node(int data) {
    struct Node *node = malloc(sizeof(*node));
    if (node == NULL) {
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->next = NULL;
    return node;
}

void append_node(struct Node **head, int data) {
    struct Node *new_node = create_node(data);

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    struct Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

void print_list(const struct Node *head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void free_list(struct Node *head) {
    while (head != NULL) {
        struct Node *tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main(void) {
    struct Node *list = NULL;

    append_node(&list, 1);
    append_node(&list, 2);
    append_node(&list, 3);
    append_node(&list, 4);

    print_list(list);
    shift_first_to_end(&list);
    print_list(list);

    free_list(list);
    return 0;
}