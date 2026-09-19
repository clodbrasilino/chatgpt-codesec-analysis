#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

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

static void remove_negative_numbers(Node **head)
{
    if (head == NULL) {
        return;
    }

    Node **current = head;

    while (*current != NULL) {
        if ((*current)->value < 0) {
            Node *node = *current;
            *current = node->next;
            free(node);
        } else {
            current = &(*current)->next;
        }
    }
}

static void free_list(Node **head)
{
    if (head == NULL) {
        return;
    }

    Node *current = *head;

    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
}

static bool print_list(const Node *head)
{
    const Node *current = head;
    bool first = true;

    while (current != NULL) {
        if (!first && putchar(' ') == EOF) {
            return false;
        }

        if (printf("%d", current->value) < 0) {
            return false;
        }

        first = false;
        current = current->next;
    }

    return putchar('\n') != EOF;
}

static bool parse_integer(const char *text, int *value)
{
    if (text == NULL || value == NULL || *text == '\0') {
        return false;
    }

    char *end = NULL;

    errno = 0;
    long result = strtol(text, &end, 10);

    if (errno == ERANGE ||
        end == text ||
        *end != '\0' ||
        result < INT_MIN ||
        result > INT_MAX) {
        return false;
    }

    *value = (int)result;
    return true;
}

int main(int argc, char *const argv[])
{
    Node *head = NULL;
    Node *tail = NULL;
    int status = EXIT_SUCCESS;

    for (int i = 1; i < argc; ++i) {
        int value;

        if (!parse_integer(argv[i], &value)) {
            fprintf(stderr, "Invalid integer: %s\n", argv[i]);
            status = EXIT_FAILURE;
            goto cleanup;
        }

        if (!append_node(&head, &tail, value)) {
            fputs("Unable to allocate memory\n", stderr);
            status = EXIT_FAILURE;
            goto cleanup;
        }
    }

    remove_negative_numbers(&head);

    if (!print_list(head)) {
        status = EXIT_FAILURE;
    }

cleanup:
    free_list(&head);
    return status;
}