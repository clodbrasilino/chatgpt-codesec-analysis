#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

int insert_before_each(Node **head, int value) {
    if (head == NULL) {
        return -1;
    }

    Node *new_nodes = NULL;
    Node *new_tail = NULL;
    Node *current = *head;

    while (current != NULL) {
        Node *new_node = malloc(sizeof(*new_node));
        if (new_node == NULL) {
            while (new_nodes != NULL) {
                Node *tmp = new_nodes;
                new_nodes = new_nodes->next;
                free(tmp);
            }
            return -1;
        }

        new_node->data = value;
        new_node->next = NULL;

        if (new_nodes == NULL) {
            new_nodes = new_node;
            new_tail = new_node;
        } else {
            new_tail->next = new_node;
            new_tail = new_node;
        }

        current = current->next;
    }

    Node **pp = head;
    Node *new_current = new_nodes;

    while (new_current != NULL) {
        Node *original = *pp;
        Node *next_new = new_current->next;

        new_current->next = original;
        *pp = new_current;
        pp = &original->next;
        new_current = next_new;
    }

    return 0;
}

void free_list(Node *head) {
    while (head != NULL) {
        Node *tmp = head;
        head = head->next;
        free(tmp);
    }
}

void print_list(const Node *head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main(void) {
    Node *head = NULL;
    Node *tail = NULL;
    int values[] = {1, 2, 3};
    size_t count = sizeof(values) / sizeof(values[0]);

    for (size_t i = 0; i < count; i++) {
        Node *new_node = malloc(sizeof(*new_node));
        if (new_node == NULL) {
            free_list(head);
            return EXIT_FAILURE;
        }

        new_node->data = values[i];
        new_node->next = NULL;

        if (head == NULL) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }

    print_list(head);

    if (insert_before_each(&head, 0) != 0) {
        free_list(head);
        return EXIT_FAILURE;
    }

    print_list(head);

    free_list(head);
    return EXIT_SUCCESS;
}