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

static Node *create_list(const int values[], size_t count, bool *success)
{
    Node *head = NULL;
    Node *tail = NULL;
    size_t i;

    if (success == NULL || (values == NULL && count != 0U)) {
        return NULL;
    }

    *success = false;

    for (i = 0U; i < count; ++i) {
        if (!append_node(&head, &tail, values[i])) {
            free_list(head);
            return NULL;
        }
    }

    *success = true;
    return head;
}

static Node *create_alternate_list(const Node *source, bool *success)
{
    Node *head = NULL;
    Node *tail = NULL;
    bool take = true;

    if (success == NULL) {
        return NULL;
    }

    *success = false;

    while (source != NULL) {
        if (take && !append_node(&head, &tail, source->value)) {
            free_list(head);
            return NULL;
        }

        take = !take;
        source = source->next;
    }

    *success = true;
    return head;
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
    const int values[] = {1, 2, 3, 4, 5, 6, 7};
    const size_t count = sizeof(values) / sizeof(values[0]);
    Node *source;
    Node *alternate;
    bool success;

    source = create_list(values, count, &success);
    if (!success) {
        return EXIT_FAILURE;
    }

    alternate = create_alternate_list(source, &success);
    if (!success) {
        free_list(source);
        return EXIT_FAILURE;
    }

    if (!print_list(alternate)) {
        free_list(alternate);
        free_list(source);
        return EXIT_FAILURE;
    }

    free_list(alternate);
    free_list(source);

    return EXIT_SUCCESS;
}