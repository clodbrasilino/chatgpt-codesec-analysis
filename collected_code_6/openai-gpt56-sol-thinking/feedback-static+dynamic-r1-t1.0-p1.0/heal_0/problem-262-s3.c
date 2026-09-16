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

static bool create_list(const int *values, size_t length, Node **head)
{
    Node *tail = NULL;

    if (head == NULL || (values == NULL && length != 0U)) {
        return false;
    }

    *head = NULL;

    for (size_t i = 0U; i < length; ++i) {
        Node *node = malloc(sizeof(*node));

        if (node == NULL) {
            free_list(*head);
            *head = NULL;
            return false;
        }

        node->value = values[i];
        node->next = NULL;

        if (tail == NULL) {
            *head = node;
        } else {
            tail->next = node;
        }

        tail = node;
    }

    return true;
}

bool split_list(Node *source, size_t first_length,
                Node **first_part, Node **second_part)
{
    Node *last;
    size_t remaining;

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
    remaining = first_length;

    while (remaining > 1U && last != NULL) {
        last = last->next;
        --remaining;
    }

    if (last == NULL) {
        return false;
    }

    *first_part = source;
    *second_part = last->next;
    last->next = NULL;

    return true;
}

static bool print_list(const Node *head)
{
    if (fputc('[', stdout) == EOF) {
        return false;
    }

    while (head != NULL) {
        if (fprintf(stdout, "%d", head->value) < 0) {
            return false;
        }

        head = head->next;

        if (head != NULL && fputs(", ", stdout) == EOF) {
            return false;
        }
    }

    return fputs("]\n", stdout) != EOF;
}

int main(void)
{
    const int values[] = {1, 2, 3, 4, 5};
    const size_t first_length = 3U;
    Node *list = NULL;
    Node *first_part = NULL;
    Node *second_part = NULL;

    if (!create_list(values, sizeof(values) / sizeof(values[0]), &list)) {
        return EXIT_FAILURE;
    }

    if (!split_list(list, first_length, &first_part, &second_part)) {
        free_list(list);
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