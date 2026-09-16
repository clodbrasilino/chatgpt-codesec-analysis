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

    node = malloc(sizeof(*node));
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

static bool create_alternate_list(const Node *source, Node **result)
{
    Node *head = NULL;
    Node *tail = NULL;
    bool take_element = true;

    if (result == NULL) {
        return false;
    }

    *result = NULL;

    while (source != NULL) {
        if (take_element && !append_node(&head, &tail, source->value)) {
            free_list(head);
            return false;
        }

        take_element = !take_element;
        source = source->next;
    }

    *result = head;
    return true;
}

static void print_list(const Node *head)
{
    bool first = true;

    while (head != NULL) {
        if (!first) {
            putchar(' ');
        }

        printf("%d", head->value);
        first = false;
        head = head->next;
    }

    putchar('\n');
}

int main(void)
{
    Node *source = NULL;
    Node *source_tail = NULL;
    Node *alternate = NULL;
    size_t count;

    if (scanf("%zu", &count) != 1) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        int value;

        if (scanf("%d", &value) != 1) {
            free_list(source);
            return EXIT_FAILURE;
        }

        if (!append_node(&source, &source_tail, value)) {
            free_list(source);
            return EXIT_FAILURE;
        }
    }

    if (!create_alternate_list(source, &alternate)) {
        free_list(source);
        return EXIT_FAILURE;
    }

    print_list(alternate);

    free_list(alternate);
    free_list(source);

    return EXIT_SUCCESS;
}