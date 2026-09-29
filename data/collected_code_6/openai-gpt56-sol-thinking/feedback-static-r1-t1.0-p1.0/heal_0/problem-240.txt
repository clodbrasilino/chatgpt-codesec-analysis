#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef enum {
    LIST_STATUS_OK,
    LIST_STATUS_INVALID_ARGUMENT,
    LIST_STATUS_EMPTY,
    LIST_STATUS_CYCLE,
    LIST_STATUS_OVERLAP
} ListStatus;

static void free_list(Node *head)
{
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

static bool list_has_cycle(const Node *head)
{
    const Node *slow = head;
    const Node *fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            return true;
        }
    }

    return false;
}

static const Node *list_tail(const Node *head)
{
    while (head != NULL && head->next != NULL) {
        head = head->next;
    }

    return head;
}

static bool create_list(const int *values, size_t count, Node **result)
{
    Node *head = NULL;
    Node *tail = NULL;
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

ListStatus replace_last_with_list(Node **head, Node **replacement)
{
    Node *previous = NULL;
    Node *last;

    if (head == NULL || replacement == NULL) {
        return LIST_STATUS_INVALID_ARGUMENT;
    }

    if (*head == NULL) {
        return LIST_STATUS_EMPTY;
    }

    if (list_has_cycle(*head) || list_has_cycle(*replacement)) {
        return LIST_STATUS_CYCLE;
    }

    if (*replacement != NULL &&
        list_tail(*head) == list_tail(*replacement)) {
        return LIST_STATUS_OVERLAP;
    }

    last = *head;

    while (last->next != NULL) {
        previous = last;
        last = last->next;
    }

    if (previous == NULL) {
        *head = *replacement;
    } else {
        previous->next = *replacement;
    }

    *replacement = NULL;
    free(last);

    return LIST_STATUS_OK;
}

static bool print_list(const Node *head)
{
    while (head != NULL) {
        if (printf("%d", head->value) < 0) {
            return false;
        }

        if (head->next != NULL && printf(" -> ") < 0) {
            return false;
        }

        head = head->next;
    }

    return putchar('\n') != EOF;
}

int main(void)
{
    const int initial_values[] = {1, 2, 3, 4};
    const int replacement_values[] = {7, 8, 9};
    Node *list = NULL;
    Node *replacement = NULL;
    ListStatus status;
    int exit_status = EXIT_FAILURE;

    if (!create_list(initial_values,
                     sizeof(initial_values) / sizeof(initial_values[0]),
                     &list)) {
        fputs("Failed to create the initial list.\n", stderr);
        goto cleanup;
    }

    if (!create_list(replacement_values,
                     sizeof(replacement_values) / sizeof(replacement_values[0]),
                     &replacement)) {
        fputs("Failed to create the replacement list.\n", stderr);
        goto cleanup;
    }

    status = replace_last_with_list(&list, &replacement);

    if (status != LIST_STATUS_OK) {
        fputs("Failed to replace the last element.\n", stderr);
        goto cleanup;
    }

    if (!print_list(list)) {
        fputs("Failed to print the list.\n", stderr);
        goto cleanup;
    }

    exit_status = EXIT_SUCCESS;

cleanup:
    free_list(list);
    free_list(replacement);
    return exit_status;
}