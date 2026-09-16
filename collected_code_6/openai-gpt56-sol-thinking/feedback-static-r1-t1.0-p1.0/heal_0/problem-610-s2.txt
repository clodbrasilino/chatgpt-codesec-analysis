#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>

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
    if (head == NULL || tail == NULL) {
        return false;
    }

    Node *node = malloc(sizeof(*node));
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

static bool remove_kth_element(Node **head, size_t k)
{
    if (head == NULL || k == 0) {
        return false;
    }

    Node **link = head;

    for (size_t position = 1; position < k; ++position) {
        if (*link == NULL) {
            return false;
        }
        link = &(*link)->next;
    }

    if (*link == NULL) {
        return false;
    }

    Node *removed = *link;
    *link = removed->next;
    free(removed);

    return true;
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
    size_t count;
    size_t k;
    Node *head = NULL;
    Node *tail = NULL;

    if (scanf("%zu", &count) != 1) {
        fputs("Invalid list size\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        int value;

        if (scanf("%d", &value) != 1) {
            fputs("Invalid list element\n", stderr);
            free_list(head);
            return EXIT_FAILURE;
        }

        if (!append_node(&head, &tail, value)) {
            fputs("Unable to allocate memory\n", stderr);
            free_list(head);
            return EXIT_FAILURE;
        }
    }

    if (scanf("%zu", &k) != 1) {
        fputs("Invalid element position\n", stderr);
        free_list(head);
        return EXIT_FAILURE;
    }

    if (!remove_kth_element(&head, k)) {
        fputs("Element position is out of range\n", stderr);
        free_list(head);
        return EXIT_FAILURE;
    }

    if (!print_list(head)) {
        fputs("Unable to write output\n", stderr);
        free_list(head);
        return EXIT_FAILURE;
    }

    free_list(head);
    return EXIT_SUCCESS;
}