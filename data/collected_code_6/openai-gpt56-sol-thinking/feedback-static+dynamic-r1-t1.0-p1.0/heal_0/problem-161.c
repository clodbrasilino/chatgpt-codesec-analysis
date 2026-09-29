#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

static void destroy_list(Node **head)
{
    Node *current;

    if (head == NULL) {
        return;
    }

    current = *head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
}

static bool create_list(const int values[], size_t count, Node **head)
{
    Node **tail;
    size_t i;

    if (head == NULL || (count > 0U && values == NULL)) {
        return false;
    }

    *head = NULL;
    tail = head;

    for (i = 0U; i < count; ++i) {
        Node *node = malloc(sizeof(*node));

        if (node == NULL) {
            destroy_list(head);
            return false;
        }

        node->value = values[i];
        node->next = NULL;
        *tail = node;
        tail = &node->next;
    }

    return true;
}

static bool contains(const Node *head, int value)
{
    const Node *current = head;

    while (current != NULL) {
        if (current->value == value) {
            return true;
        }
        current = current->next;
    }

    return false;
}

static void remove_all_present(Node **list, const Node *other)
{
    Node **current;

    if (list == NULL) {
        return;
    }

    current = list;

    while (*current != NULL) {
        if (contains(other, (*current)->value)) {
            Node *removed = *current;
            *current = removed->next;
            free(removed);
        } else {
            current = &(*current)->next;
        }
    }
}

static bool print_list(const Node *head)
{
    const Node *current = head;
    bool first = true;

    while (current != NULL) {
        if (!first && fputc(' ', stdout) == EOF) {
            return false;
        }

        if (printf("%d", current->value) < 0) {
            return false;
        }

        first = false;
        current = current->next;
    }

    return fputc('\n', stdout) != EOF;
}

int main(void)
{
    const int first_values[] = {1, 2, 3, 4, 2, 5};
    const int second_values[] = {2, 4, 6};
    Node *first = NULL;
    Node *second = NULL;
    bool output_succeeded;

    if (!create_list(first_values,
                     sizeof(first_values) / sizeof(first_values[0]),
                     &first)) {
        return EXIT_FAILURE;
    }

    if (!create_list(second_values,
                     sizeof(second_values) / sizeof(second_values[0]),
                     &second)) {
        destroy_list(&first);
        return EXIT_FAILURE;
    }

    remove_all_present(&first, second);
    output_succeeded = print_list(first);

    destroy_list(&first);
    destroy_list(&second);

    return output_succeeded ? EXIT_SUCCESS : EXIT_FAILURE;
}