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

static bool create_list(const int values[], size_t count, Node **result)
{
    Node *head = NULL;
    Node **tail = &head;
    size_t i;

    if (result == NULL || (values == NULL && count != 0U)) {
        return false;
    }

    *result = NULL;

    for (i = 0U; i < count; ++i) {
        Node *node = malloc(sizeof(*node));

        if (node == NULL) {
            free_list(head);
            return false;
        }

        node->value = values[i];
        node->next = NULL;
        *tail = node;
        tail = &node->next;
    }

    *result = head;
    return true;
}

static bool contains_value(const Node *head, int value)
{
    while (head != NULL) {
        if (head->value == value) {
            return true;
        }
        head = head->next;
    }

    return false;
}

static void remove_elements_present_in(Node **list, const Node *other)
{
    Node **current;

    if (list == NULL) {
        return;
    }

    current = list;

    while (*current != NULL) {
        Node *node = *current;

        if (contains_value(other, node->value)) {
            *current = node->next;
            free(node);
        } else {
            current = &node->next;
        }
    }
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
    const int first_values[] = {1, 2, 3, 4, 5, 2, 6};
    const int second_values[] = {2, 4, 7};
    Node *first = NULL;
    Node *second = NULL;
    int status = EXIT_SUCCESS;

    if (!create_list(first_values,
                     sizeof(first_values) / sizeof(first_values[0]),
                     &first)) {
        return EXIT_FAILURE;
    }

    if (!create_list(second_values,
                     sizeof(second_values) / sizeof(second_values[0]),
                     &second)) {
        free_list(first);
        return EXIT_FAILURE;
    }

    remove_elements_present_in(&first, second);

    if (!print_list(first)) {
        status = EXIT_FAILURE;
    }

    free_list(first);
    free_list(second);

    return status;
}