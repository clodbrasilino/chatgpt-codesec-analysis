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

static bool append_node(Node **head, Node **tail, int value)
{
    Node *node;

    if (head == NULL || tail == NULL) {
        return false;
    }

    node = malloc(sizeof *node);
    if (node == NULL) {
        return false;
    }

    node->value = value;
    node->next = NULL;

    if (*tail == NULL) {
        *head = node;
    } else {
        (*tail)->next = node;
    }

    *tail = node;
    return true;
}

static bool remove_kth(Node **head, size_t k)
{
    Node **link;
    Node *removed;

    if (head == NULL || k == 0U) {
        return false;
    }

    link = head;

    while (*link != NULL && k > 1U) {
        link = &(*link)->next;
        --k;
    }

    if (*link == NULL) {
        return false;
    }

    removed = *link;
    *link = removed->next;
    free(removed);

    return true;
}

static bool print_list(const Node *head)
{
    bool first = true;

    while (head != NULL) {
        if (!first && putchar(' ') == EOF) {
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
    Node *head = NULL;
    Node *tail = NULL;
    size_t count;
    size_t k;

    if (scanf("%zu", &count) != 1) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        int value;

        if (scanf("%d", &value) != 1) {
            free_list(head);
            return EXIT_FAILURE;
        }

        if (!append_node(&head, &tail, value)) {
            free_list(head);
            return EXIT_FAILURE;
        }
    }

    if (scanf("%zu", &k) != 1) {
        free_list(head);
        return EXIT_FAILURE;
    }

    if (!remove_kth(&head, k)) {
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