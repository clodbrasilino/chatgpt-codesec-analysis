#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

static void list_destroy(Node **head)
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

static bool list_create(const int *values, size_t count, Node **head)
{
    Node *tail = NULL;
    size_t i;

    if (head == NULL || (values == NULL && count != 0U)) {
        return false;
    }

    *head = NULL;

    for (i = 0U; i < count; ++i) {
        Node *node = malloc(sizeof(*node));

        if (node == NULL) {
            list_destroy(head);
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

static bool list_remove_kth(Node **head, size_t k, int *removed_value)
{
    Node **link;
    Node *removed;
    size_t position;

    if (head == NULL || k == 0U) {
        return false;
    }

    link = head;

    for (position = 1U; position < k; ++position) {
        if (*link == NULL) {
            return false;
        }
        link = &(*link)->next;
    }

    if (*link == NULL) {
        return false;
    }

    removed = *link;
    *link = removed->next;

    if (removed_value != NULL) {
        *removed_value = removed->value;
    }

    free(removed);
    return true;
}

static bool list_print(const Node *head)
{
    const Node *current = head;

    while (current != NULL) {
        if (printf("%d%s", current->value,
                   current->next == NULL ? "\n" : " ") < 0) {
            return false;
        }
        current = current->next;
    }

    if (head == NULL && putchar('\n') == EOF) {
        return false;
    }

    return true;
}

int main(void)
{
    const int values[] = {10, 20, 30, 40, 50};
    const size_t k = 3U;
    Node *head = NULL;
    int removed_value;

    if (!list_create(values, sizeof(values) / sizeof(values[0]), &head)) {
        fputs("Failed to create list.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!list_remove_kth(&head, k, &removed_value)) {
        fputs("Unable to remove the requested element.\n", stderr);
        list_destroy(&head);
        return EXIT_FAILURE;
    }

    if (printf("Removed: %d\n", removed_value) < 0 || !list_print(head)) {
        list_destroy(&head);
        return EXIT_FAILURE;
    }

    list_destroy(&head);
    return EXIT_SUCCESS;
}