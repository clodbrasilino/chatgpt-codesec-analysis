#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *create_node(int data) {
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
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
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf("\n");
}

Node *insert_before_each(Node *head, int value) {
    if (head == NULL) {
        return NULL;
    }

    Node *new_head = NULL;
    Node *current = head;
    Node *prev = NULL;

    while (current != NULL) {
        Node *new_node = create_node(value);
        if (new_node == NULL) {
            free_list(new_head);
            return NULL;
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

int main(void) {
    Node *head = create_node(1);
    if (head == NULL) {
        return 1;
    }
    head->next = create_node(2);
    if (head->next == NULL) {
        free_list(head);
        return 1;
    }
    head->next->next = create_node(3);
    if (head->next->next == NULL) {
        free_list(head);
        return 1;
    }

    printf("Original list: ");
    print_list(head);

    head = insert_before_each(head, 0);
    if (head == NULL) {
        return 1;
    }

    printf("After insertion: ");
    print_list(head);

    free_list(head);

    return 0;
}