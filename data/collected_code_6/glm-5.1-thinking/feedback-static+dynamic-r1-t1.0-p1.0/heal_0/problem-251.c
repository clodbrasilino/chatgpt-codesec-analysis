#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *create_node(int data) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

Node *insert_before_each(Node *head, int value) {
    Node *current = head;
    Node *prev = NULL;
    Node *new_head = head;

    while (current != NULL) {
        Node *new_node = create_node(value);
        if (new_node == NULL) {
            return new_head;
        }
        new_node->next = current;

        if (prev == NULL) {
            new_head = new_node;
        } else {
            prev->next = new_node;
        }

        prev = current;
        current = current->next;
    }

    return new_head;
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
    Node *head = create_node(1);
    if (head == NULL) {
        return EXIT_FAILURE;
    }

    head->next = create_node(2);
    if (head->next == NULL) {
        free_list(head);
        return EXIT_FAILURE;
    }

    head->next->next = create_node(3);
    if (head->next->next == NULL) {
        free_list(head);
        return EXIT_FAILURE;
    }

    print_list(head);

    head = insert_before_each(head, 0);

    print_list(head);

    free_list(head);

    return EXIT_SUCCESS;
}