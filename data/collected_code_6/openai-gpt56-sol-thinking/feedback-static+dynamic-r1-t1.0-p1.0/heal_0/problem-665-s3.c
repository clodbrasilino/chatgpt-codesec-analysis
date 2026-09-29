#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

static bool shift_first_to_end(Node **head)
{
    Node *first;
    Node *last;

    if (head == NULL) {
        return false;
    }

    if (*head == NULL || (*head)->next == NULL) {
        return true;
    }

    first = *head;
    *head = first->next;
    first->next = NULL;

    last = *head;
    while (last->next != NULL) {
        last = last->next;
    }

    last->next = first;
    return true;
}

static void free_list(Node *head)
{
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
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
    Node *head = NULL;
    Node *tail = NULL;
    size_t count;

    if (scanf("%zu", &count) != 1) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        Node *node = malloc(sizeof(*node));

        if (node == NULL) {
            free_list(head);
            return EXIT_FAILURE;
        }

        if (scanf("%d", &node->value) != 1) {
            free(node);
            free_list(head);
            return EXIT_FAILURE;
        }

        node->next = NULL;

        if (tail == NULL) {
            head = node;
        } else {
            tail->next = node;
        }

        tail = node;
    }

    if (!shift_first_to_end(&head)) {
        free_list(head);
        return EXIT_FAILURE;
    }

    if (!print_list(head) || fflush(stdout) == EOF) {
        free_list(head);
        return EXIT_FAILURE;
    }

    free_list(head);
    return EXIT_SUCCESS;
}