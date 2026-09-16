#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

static void free_list(Node *head)
{
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

static bool create_list(const int values[], size_t count, Node **head)
{
    Node *new_head = NULL;
    Node **tail = &new_head;

    if (head == NULL || (values == NULL && count != 0U)) {
        return false;
    }

    for (size_t i = 0; i < count; ++i) {
        Node *node = malloc(sizeof(*node));

        if (node == NULL) {
            free_list(new_head);
            return false;
        }

        node->value = values[i];
        node->next = NULL;
        *tail = node;
        tail = &node->next;
    }

    *head = new_head;
    return true;
}

bool insert_before_each(Node **head, int value)
{
    Node *available = NULL;
    Node *current;
    Node **link;

    if (head == NULL) {
        return false;
    }

    for (current = *head; current != NULL; current = current->next) {
        Node *node = malloc(sizeof(*node));

        if (node == NULL) {
            free_list(available);
            return false;
        }

        node->value = value;
        node->next = available;
        available = node;
    }

    current = *head;
    link = head;

    while (current != NULL) {
        Node *inserted = available;

        available = available->next;
        inserted->next = current;
        *link = inserted;
        link = &current->next;
        current = current->next;
    }

    return true;
}

static bool print_list(const Node *head)
{
    const char *separator = "";

    while (head != NULL) {
        if (printf("%s%d", separator, head->value) < 0) {
            return false;
        }

        separator = " ";
        head = head->next;
    }

    return putchar('\n') != EOF;
}

int main(void)
{
    const int values[] = {1, 2, 3, 4, 5};
    Node *head = NULL;

    if (!create_list(values, sizeof(values) / sizeof(values[0]), &head)) {
        fputs("Failed to create the list.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!insert_before_each(&head, 0)) {
        fputs("Failed to insert elements.\n", stderr);
        free_list(head);
        return EXIT_FAILURE;
    }

    if (!print_list(head)) {
        free_list(head);
        return EXIT_FAILURE;
    }

    free_list(head);
    return EXIT_SUCCESS;
}