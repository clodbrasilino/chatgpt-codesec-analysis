#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

static bool append_node(Node **head, Node **tail, int value)
{
    Node *node;

    if (head == NULL || tail == NULL) {
        return false;
    }

    node = malloc(sizeof(*node));
    if (node == NULL) {
        return false;
    }

    node->value = value;
    node->next = NULL;

    if (*tail == NULL) {
        *head = node;
    } else {
        (*tail)->next = node;
    }

    *tail = node;
    return true;
}

static bool split_list(Node *head, size_t first_length,
                       Node **first_part, Node **second_part)
{
    Node *current;
    size_t index;

    if (first_part == NULL || second_part == NULL ||
        first_part == second_part) {
        return false;
    }

    *first_part = NULL;
    *second_part = NULL;

    if (first_length == 0U) {
        *second_part = head;
        return true;
    }

    current = head;

    for (index = 1U; index < first_length; ++index) {
        if (current == NULL) {
            return false;
        }
        current = current->next;
    }

    if (current == NULL) {
        return false;
    }

    *first_part = head;
    *second_part = current->next;
    current->next = NULL;

    return true;
}

static bool print_list(const Node *head)
{
    const Node *current = head;

    if (fputc('[', stdout) == EOF) {
        return false;
    }

    while (current != NULL) {
        if (fprintf(stdout, "%d", current->value) < 0) {
            return false;
        }

        current = current->next;

        if (current != NULL && fputc(' ', stdout) == EOF) {
            return false;
        }
    }

    return fputs("]\n", stdout) != EOF;
}

static void free_list(Node *head)
{
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

int main(void)
{
    const int values[] = {1, 2, 3, 4, 5, 6};
    const size_t value_count = sizeof(values) / sizeof(values[0]);
    const size_t first_length = 3U;
    Node *head = NULL;
    Node *tail = NULL;
    Node *first_part = NULL;
    Node *second_part = NULL;
    size_t index;

    for (index = 0U; index < value_count; ++index) {
        if (!append_node(&head, &tail, values[index])) {
            free_list(head);
            return EXIT_FAILURE;
        }
    }

    if (!split_list(head, first_length, &first_part, &second_part)) {
        free_list(head);
        return EXIT_FAILURE;
    }

    if (!print_list(first_part) || !print_list(second_part)) {
        free_list(first_part);
        free_list(second_part);
        return EXIT_FAILURE;
    }

    free_list(first_part);
    free_list(second_part);

    return EXIT_SUCCESS;
}