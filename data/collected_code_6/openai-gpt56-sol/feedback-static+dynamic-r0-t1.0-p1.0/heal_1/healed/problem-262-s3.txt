#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

    Node *node = malloc(sizeof *node);
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

static bool split_list(Node *head, size_t first_length,
                       Node **first, Node **second)
{
    if (first == NULL || second == NULL || first == second) {
        return false;
    }

    *first = NULL;
    *second = NULL;

    if (first_length == 0) {
        *second = head;
        return true;
    }

    Node *last = head;

    for (size_t i = 1; i < first_length; ++i) {
        if (last == NULL) {
            return false;
        }
        last = last->next;
    }

    if (last == NULL) {
        return false;
    }

    *first = head;
    *second = last->next;
    last->next = NULL;

    return true;
}

static void print_list(const Node *head)
{
    for (const Node *node = head; node != NULL; node = node->next) {
        if (node != head) {
            putchar(' ');
        }
        printf("%d", node->value);
    }

    putchar('\n');
}

int main(void)
{
    Node *list = NULL;
    Node *tail = NULL;
    Node *first = NULL;
    Node *second = NULL;
    size_t count;
    size_t first_length;

    if (scanf("%zu", &count) != 1) {
        fprintf(stderr, "Invalid list length\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        int value;

        if (scanf("%d", &value) != 1) {
            fprintf(stderr, "Invalid list element\n");
            free_list(list);
            return EXIT_FAILURE;
        }

        if (!append_node(&list, &tail, value)) {
            fprintf(stderr, "Memory allocation failed\n");
            free_list(list);
            return EXIT_FAILURE;
        }
    }

    if (scanf("%zu", &first_length) != 1) {
        fprintf(stderr, "Invalid split length\n");
        free_list(list);
        return EXIT_FAILURE;
    }

    if (!split_list(list, first_length, &first, &second)) {
        fprintf(stderr, "Split length exceeds list length\n");
        free_list(list);
        return EXIT_FAILURE;
    }

    list = NULL;
    tail = NULL;

    print_list(first);
    print_list(second);

    free_list(first);
    free_list(second);

    return EXIT_SUCCESS;
}