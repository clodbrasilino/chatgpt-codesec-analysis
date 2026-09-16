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

static bool create_list(Node **head, const int *values, size_t count)
{
    Node **tail;

    if (head == NULL || (values == NULL && count != 0U)) {
        return false;
    }

    *head = NULL;
    tail = head;

    for (size_t i = 0; i < count; ++i) {
        Node *node = malloc(sizeof(*node));

        if (node == NULL) {
            free_list(*head);
            *head = NULL;
            return false;
        }

        node->value = values[i];
        node->next = NULL;
        *tail = node;
        tail = &node->next;
    }

    return true;
}

static bool insert_before_each(Node **head, int value)
{
    Node *insertions = NULL;
    Node **tail = &insertions;

    if (head == NULL) {
        return false;
    }

    for (Node *current = *head; current != NULL; current = current->next) {
        Node *node = malloc(sizeof(*node));

        if (node == NULL) {
            free_list(insertions);
            return false;
        }

        node->value = value;
        node->next = NULL;
        *tail = node;
        tail = &node->next;
    }

    if (*head == NULL) {
        return true;
    }

    Node *original = *head;
    Node *insertion = insertions;
    *head = insertions;

    while (original != NULL) {
        Node *next_original = original->next;
        Node *next_insertion = insertion->next;

        insertion->next = original;
        original->next = next_insertion;

        original = next_original;
        insertion = next_insertion;
    }

    return true;
}

static void print_list(const Node *head)
{
    for (const Node *current = head; current != NULL; current = current->next) {
        printf("%d%s", current->value, current->next == NULL ? "\n" : " ");
    }
}

int main(void)
{
    const int values[] = {1, 2, 3, 4, 5};
    Node *head = NULL;

    if (!create_list(&head, values, sizeof(values) / sizeof(values[0]))) {
        fputs("Failed to create the list.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!insert_before_each(&head, 0)) {
        fputs("Failed to insert elements.\n", stderr);
        free_list(head);
        return EXIT_FAILURE;
    }

    print_list(head);
    free_list(head);

    return EXIT_SUCCESS;
}