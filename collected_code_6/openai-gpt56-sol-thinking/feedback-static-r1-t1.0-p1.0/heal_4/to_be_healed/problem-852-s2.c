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
        Node *node = *current;

        if (node->value < 0) {
            *current = node->next;
            free(node);
        } else {
            current = &node->next;
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
    bool first = true;

    for (const Node *current = head; current != NULL;
         current = current->next) {
        if (!first && putchar(' ') == EOF) {
            return false;
        }

        if (printf("%d", current->value) < 0) {
            return false;
        }

        first = false;
    }

    return putchar('\n') != EOF;
}

static bool parse_integer(const char *text, int *value)
{
    if (text == NULL || value == NULL || text[0] == '\0') {
        return false;
    }

    errno = 0;
    char *end = NULL;
    long result = strtol(text, &end, 10);

    if (errno == ERANGE || end == text || end == NULL || *end != '\0' ||
        result < INT_MIN || result > INT_MAX) {
        return false;
    }

    *value = (int)result;
    return true;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[const])
{
    Node *head = NULL;
    Node *tail = NULL;
    int status = EXIT_SUCCESS;

    for (int i = 1; i < argc; ++i) {
        int value;

        if (!parse_integer(argv[i], &value)) {
            if (fprintf(stderr, "Invalid integer: %s\n", argv[i]) < 0) {
                status = EXIT_FAILURE;
            } else {
                status = EXIT_FAILURE;
            }
            goto cleanup;
        }

        if (!append_node(&head, &tail, value)) {
            if (fputs("Unable to allocate memory\n", stderr) == EOF) {
                status = EXIT_FAILURE;
            } else {
                status = EXIT_FAILURE;
            }
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