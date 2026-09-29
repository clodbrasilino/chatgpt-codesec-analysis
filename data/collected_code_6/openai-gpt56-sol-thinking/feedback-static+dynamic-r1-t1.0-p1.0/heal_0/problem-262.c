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
    Node **tail;

    if (head == NULL || (values == NULL && count != 0U)) {
        return false;
    }

    *head = NULL;
    tail = head;

    for (size_t i = 0U; i < count; ++i) {
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

static bool split_list(Node *source, size_t first_length,
                       Node **first_part, Node **second_part)
{
    Node *last;

    if (first_part == NULL || second_part == NULL ||
        first_part == second_part) {
        return false;
    }

    *first_part = NULL;
    *second_part = NULL;

    if (first_length == 0U) {
        *second_part = source;
        return true;
    }

    last = source;

    for (size_t i = 1U; i < first_length && last != NULL; ++i) {
        last = last->next;
    }

    if (last == NULL) {
        return false;
    }

    *first_part = source;
    *second_part = last->next;
    last->next = NULL;

    return true;
}

static bool print_list(const char *label, const Node *head)
{
    if (label == NULL || printf("%s", label) < 0) {
        return false;
    }

    for (const Node *node = head; node != NULL; node = node->next) {
        if (printf("%s%d", node == head ? "" : " ", node->value) < 0) {
            return false;
        }
    }

    return putchar('\n') != EOF;
}

int main(void)
{
    const int values[] = {1, 2, 3, 4, 5};
    const size_t first_length = 3U;
    Node *list = NULL;
    Node *first_part = NULL;
    Node *second_part = NULL;

    if (!create_list(values, sizeof(values) / sizeof(values[0]), &list)) {
        fputs("Failed to create the list.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!split_list(list, first_length, &first_part, &second_part)) {
        free_list(list);
        fputs("Failed to split the list.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!print_list("First part: ", first_part) ||
        !print_list("Second part: ", second_part)) {
        free_list(first_part);
        free_list(second_part);
        return EXIT_FAILURE;
    }

    free_list(first_part);
    free_list(second_part);

    return EXIT_SUCCESS;
}