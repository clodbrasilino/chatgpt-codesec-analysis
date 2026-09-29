#include <stdbool.h>
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
    Node *tail = NULL;

    if (result == NULL || (values == NULL && count != 0U)) {
        return false;
    }

    *result = NULL;

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

    *result = head;
    return true;
}

static Node *combine_sorted_lists(Node *first, Node *second)
{
    Node sentinel = {0, NULL};
    Node *tail = &sentinel;

    while (first != NULL && second != NULL) {
        if (first->value <= second->value) {
            tail->next = first;
            first = first->next;
        } else {
            tail->next = second;
            second = second->next;
        }

        tail = tail->next;
    }

    tail->next = first != NULL ? first : second;
    return sentinel.next;
}

static bool print_list(const Node *head)
{
    bool needs_separator = false;

    while (head != NULL) {
        if (needs_separator && putchar(' ') == EOF) {
            return false;
        }

        if (printf("%d", head->value) < 0) {
            return false;
        }

        needs_separator = true;
        head = head->next;
    }

    return putchar('\n') != EOF;
}

int main(void)
{
    const int first_values[] = {1, 3, 5, 7, 9};
    const int second_values[] = {2, 4, 6, 8, 10};
    Node *first = NULL;
    Node *second = NULL;
    Node *combined = NULL;

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

    combined = combine_sorted_lists(first, second);

    if (!print_list(combined)) {
        free_list(combined);
        return EXIT_FAILURE;
    }

    free_list(combined);
    return EXIT_SUCCESS;
}