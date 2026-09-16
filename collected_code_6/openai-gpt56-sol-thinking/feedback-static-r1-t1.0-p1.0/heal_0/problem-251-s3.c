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

static bool create_list(const int values[], size_t count, Node **head)
{
    Node *new_head = NULL;
    Node *tail = NULL;

    if (head == NULL || (values == NULL && count != 0U)) {
        return false;
    }

    for (size_t i = 0U; i < count; ++i) {
        Node *node = malloc(sizeof(*node));

        if (node == NULL) {
            free_list(new_head);
            return false;
        }

        node->value = values[i];
        node->next = NULL;

        if (new_head == NULL) {
            new_head = node;
        } else {
            tail->next = node;
        }

        tail = node;
    }

    *head = new_head;
    return true;
}

static bool insert_before_each(Node **head, int value)
{
    Node *pending_head = NULL;
    Node *pending_tail = NULL;
    Node *current;
    Node *pending;

    if (head == NULL || list_has_cycle(*head)) {
        return false;
    }

    for (current = *head; current != NULL; current = current->next) {
        Node *node = malloc(sizeof(*node));

        if (node == NULL) {
            free_list(pending_head);
            return false;
        }

        node->value = value;
        node->next = NULL;

        if (pending_head == NULL) {
            pending_head = node;
        } else {
            pending_tail->next = node;
        }

        pending_tail = node;
    }

    current = *head;
    pending = pending_head;

    if (current != NULL) {
        *head = pending;
    }

    while (current != NULL) {
        Node *next_current = current->next;
        Node *next_pending = pending->next;

        pending->next = current;
        current->next = next_pending;

        current = next_current;
        pending = next_pending;
    }

    return true;
}

static bool print_list(const Node *head)
{
    bool first = true;

    while (head != NULL) {
        if (!first && printf(" ") < 0) {
            return false;
        }

        if (printf("%d", head->value) < 0) {
            return false;
        }

        first = false;
        head = head->next;
    }

    return putchar('\n') != EOF;
}

int main(void)
{
    const int values[] = {1, 2, 3, 4, 5};
    Node *head = NULL;

    if (!create_list(values, sizeof(values) / sizeof(values[0]), &head)) {
        return EXIT_FAILURE;
    }

    if (!insert_before_each(&head, 0)) {
        free_list(head);
        return EXIT_FAILURE;
    }

    if (!print_list(head)) {
        free_list(head);
        return EXIT_FAILURE;
    }

    free_list(head);
    return EXIT_SUCCESS;
}