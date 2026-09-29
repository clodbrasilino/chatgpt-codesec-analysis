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

static bool list_from_array(Node **out, const int *values, size_t count)
{
    Node *head = NULL;
    Node *tail = NULL;

    if (out == NULL || *out != NULL || (count > 0U && values == NULL)) {
        return false;
    }

    for (size_t i = 0U; i < count; ++i) {
        Node *node = malloc(sizeof(*node));

        if (node == NULL) {
            free_list(head);
            return false;
        }

        node->value = values[i];
        node->next = NULL;

        if (tail == NULL) {
            head = node;
        } else {
            tail->next = node;
        }

        tail = node;
    }

    *out = head;
    return true;
}

static bool contains_value(const Node *head, int value)
{
    for (const Node *current = head; current != NULL; current = current->next) {
        if (current->value == value) {
            return true;
        }
    }

    return false;
}

size_t remove_all_present(Node **list, const Node *other)
{
    Node **link;
    size_t removed = 0U;

    if (list == NULL) {
        return 0U;
    }

    link = list;

    while (*link != NULL) {
        Node *current = *link;

        if (contains_value(other, current->value)) {
            *link = current->next;
            free(current);
            ++removed;
        } else {
            link = &current->next;
        }
    }

    return removed;
}

static bool print_list(const Node *head)
{
    const Node *current = head;
    bool first = true;

    while (current != NULL) {
        if (!first && fputc(' ', stdout) == EOF) {
            return false;
        }

        if (fprintf(stdout, "%d", current->value) < 0) {
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
    int status = EXIT_SUCCESS;

    if (!list_from_array(
            &first,
            first_values,
            sizeof(first_values) / sizeof(first_values[0]))) {
        fputs("Failed to create the first list.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!list_from_array(
            &second,
            second_values,
            sizeof(second_values) / sizeof(second_values[0]))) {
        fputs("Failed to create the second list.\n", stderr);
        free_list(first);
        return EXIT_FAILURE;
    }

    remove_all_present(&first, second);

    if (!print_list(first) || fflush(stdout) == EOF) {
        fputs("Failed to write output.\n", stderr);
        status = EXIT_FAILURE;
    }

    free_list(first);
    free_list(second);

    return status;
}