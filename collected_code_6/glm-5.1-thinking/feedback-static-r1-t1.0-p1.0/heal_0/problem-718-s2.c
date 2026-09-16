#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *create_node(int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
}

Node *alternate_list(Node *head) {
    if (head == NULL) {
        return NULL;
    }

    Node *new_head = create_node(head->data);
    if (new_head == NULL) {
        return NULL;
    }

    Node *current_new = new_head;
    Node *current_old = head->next;
    int take = 0;

    while (current_old != NULL) {
        if (take) {
            Node *new_node = create_node(current_old->data);
            if (new_node == NULL) {
                free_list(new_head);
                return NULL;
            }
            current_new->next = new_node;
            current_new = current_new->next;
        }
        take = !take;
        current_old = current_old->next;
    }

    return new_head;
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

    Node *current = head;
    for (int i = 2; i <= 6; ++i) {
        Node *new_node = create_node(i);
        if (new_node == NULL) {
            free_list(head);
            return EXIT_FAILURE;
        }
        current->next = new_node;
        current = current->next;
    }

    print_list(head);

    Node *alt_head = alternate_list(head);
    if (alt_head == NULL) {
        free_list(head);
        return EXIT_FAILURE;
    }

    print_list(alt_head);

    free_list(head);
    free_list(alt_head);

    return EXIT_SUCCESS;
}