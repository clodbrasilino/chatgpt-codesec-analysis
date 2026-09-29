#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

static void free_list(Node **head)
{
    Node *current;
    Node *next;

    if (head == NULL) {
        return;
    }

    current = *head;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
}

static int append_node(Node **head, Node **tail, int value)
{
    Node *node;

    if (head == NULL || tail == NULL) {
        return 0;
    }

    node = malloc(sizeof(*node));
    if (node == NULL) {
        return 0;
    }

    node->value = value;
    node->next = NULL;

    if (*tail == NULL) {
        *head = node;
    } else {
        (*tail)->next = node;
    }

    *tail = node;
    return 1;
}

static int create_alternate_list(const Node *source, Node **result)
{
    Node *head = NULL;
    Node *tail = NULL;
    int take_element = 1;

    if (result == NULL) {
        return 0;
    }

    *result = NULL;

    while (source != NULL) {
        if (take_element && !append_node(&head, &tail, source->value)) {
            free_list(&head);
            return 0;
        }

        take_element = !take_element;
        source = source->next;
    }

    *result = head;
    return 1;
}

static int print_list(const Node *head)
{
    const Node *current = head;

    while (current != NULL) {
        if (printf("%d", current->value) < 0) {
            return 0;
        }

        if (current->next != NULL && fputs(" ", stdout) == EOF) {
            return 0;
        }

        current = current->next;
    }

    return putchar('\n') != EOF;
}

int main(void)
{
    const int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    const size_t count = sizeof(values) / sizeof(values[0]);
    Node *source = NULL;
    Node *source_tail = NULL;
    Node *alternate = NULL;
    size_t i;
    int status = EXIT_SUCCESS;

    for (i = 0; i < count; ++i) {
        if (!append_node(&source, &source_tail, values[i])) {
            status = EXIT_FAILURE;
            goto cleanup;
        }
    }

    if (!create_alternate_list(source, &alternate)) {
        status = EXIT_FAILURE;
        goto cleanup;
    }

    if (!print_list(alternate)) {
        status = EXIT_FAILURE;
    }

cleanup:
    free_list(&alternate);
    free_list(&source);
    return status;
}