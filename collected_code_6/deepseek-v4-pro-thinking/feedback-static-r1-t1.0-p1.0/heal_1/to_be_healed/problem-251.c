#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *create_node(int data) {
    Node *node = malloc(sizeof(*node));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

void print_list(const Node *head) {
    while (head != NULL) {
        printf("%d", head->data);
        head = head->next;
        if (head != NULL) {
            printf(" -> ");
        }
    }
    printf("\n");
}

void free_list(Node *head) {
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

int insert_before_each(Node **head, int value) {
    if (head == NULL) {
        return -1;
    }

    size_t count = 0;
    for (Node *current = *head; current != NULL; current = current->next) {
        count++;
    }

    if (count == 0) {
        return 0;
    }

    Node **new_nodes = malloc(count * sizeof(*new_nodes));
    if (new_nodes == NULL) {
        return -1;
    }

    size_t created = 0;
    for (size_t i = 0; i < count; i++) {
        new_nodes[i] = create_node(value);
        if (new_nodes[i] == NULL) {
            for (size_t j = 0; j < created; j++) {
                free(new_nodes[j]);
            }
            free(new_nodes);
            return -1;
        }
        created++;
    }

    Node *current = *head;
    Node *previous = NULL;
    size_t index = 0;
    while (current != NULL && index < count) {
        Node *new_node = new_nodes[index++];
        new_node->next = current;
        if (previous == NULL) {
            *head = new_node;
        } else {
            previous->next = new_node;
        }
        previous = current;
        current = current->next;
    }

    free(new_nodes);
    return 0;
}

int main(void) {
    Node *nodes[3] = {NULL, NULL, NULL};
    /* Possible weaknesses found:
     *  Variable 'values' can be declared as const array [constVariable]
     */
    int values[] = {1, 2, 3};

    for (size_t i = 0; i < 3; i++) {
        nodes[i] = create_node(values[i]);
        if (nodes[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(nodes[j]);
            }
            return 1;
        }
    }

    Node *head = nodes[0];
    nodes[0]->next = nodes[1];
    nodes[1]->next = nodes[2];
    nodes[2]->next = NULL;

    printf("Original list: ");
    print_list(head);

    if (insert_before_each(&head, 0) != 0) {
        free_list(head);
        return 1;
    }

    printf("After insertion: ");
    print_list(head);

    free_list(head);
    return 0;
}