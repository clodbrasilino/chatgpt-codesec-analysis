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

void remove_even(Node **head) {
    if (head == NULL) {
        return;
    }
    Node *current = *head;
    Node *prev = NULL;
    while (current != NULL) {
        if (current->data % 2 == 0) {
            Node *temp = current;
            if (prev == NULL) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            current = current->next;
            free(temp);
        } else {
            prev = current;
            current = current->next;
        }
    }
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
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
    Node *tail = NULL;
    int values[] = {1, 2, 3, 4, 5, 6};
    size_t count = sizeof(values) / sizeof(values[0]);

    for (size_t i = 0; i < count; i++) {
        Node *new_node = create_node(values[i]);
        if (new_node == NULL) {
            free_list(head);
            return EXIT_FAILURE;
        }
        if (head == NULL) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }

    print_list(head);
    remove_even(&head);
    print_list(head);
    free_list(head);

    return EXIT_SUCCESS;
}