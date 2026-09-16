#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *create_node(int data) {
    Node *node = malloc(sizeof(*node));
    if (node != NULL) {
        node->data = data;
        node->next = NULL;
    }
    return node;
}

int append_node(Node **head, int data) {
    Node *node = create_node(data);
    if (node == NULL) {
        return 0;
    }
    if (*head == NULL) {
        *head = node;
        return 1;
    }
    Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = node;
    return 1;
}

void reverse_list(Node **head) {
    Node *previous = NULL;
    Node *current = *head;
    while (current != NULL) {
        Node *next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    *head = previous;
}

void reverse_each_list(Node **lists, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        reverse_list(&lists[i]);
    }
}

void print_list(const Node *head) {
    for (const Node *current = head; current != NULL; current = current->next) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(" ");
        }
    }
}

void free_list(Node *head) {
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

int main(void) {
    Node *lists[3] = {NULL, NULL, NULL};

    if (!append_node(&lists[0], 1) ||
        !append_node(&lists[0], 2) ||
        !append_node(&lists[0], 3) ||
        !append_node(&lists[1], 4) ||
        !append_node(&lists[1], 5) ||
        !append_node(&lists[2], 6)) {
        for (size_t i = 0; i < 3; ++i) {
            free_list(lists[i]);
        }
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < 3; ++i) {
        print_list(lists[i]);
        printf("\n");
    }

    reverse_each_list(lists, 3);

    for (size_t i = 0; i < 3; ++i) {
        print_list(lists[i]);
        printf("\n");
    }

    for (size_t i = 0; i < 3; ++i) {
        free_list(lists[i]);
    }
    return 0;
}