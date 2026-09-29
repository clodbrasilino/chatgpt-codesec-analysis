#include <errno.h>
#include <limits.h>
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

static int append_node(Node **head, Node **tail, int value)
{
    Node *node = malloc(sizeof *node);

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

static Node *remove_consecutive_duplicates(Node *head)
{
    Node *current = head;

    while (current != NULL && current->next != NULL) {
        if (current->value == current->next->value) {
            Node *duplicate = current->next;
            current->next = duplicate->next;
            free(duplicate);
        } else {
            current = current->next;
        }
    }

    return head;
}

static int print_list(const Node *head)
{
    const Node *current = head;

    while (current != NULL) {
        if (printf("%d", current->value) < 0) {
            return 0;
        }

        current = current->next;

        if (current != NULL && putchar(' ') == EOF) {
            return 0;
        }
    }

    return putchar('\n') != EOF;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[const])
{
    Node *head = NULL;
    Node *tail = NULL;

    for (int i = 1; i < argc; ++i) {
        const char *argument = argv[i];
        char *end = NULL;
        long value;

        errno = 0;
        value = strtol(argument, &end, 10);

        if (errno == ERANGE ||
            end == argument ||
            *end != '\0' ||
            value < INT_MIN ||
            value > INT_MAX) {
            fprintf(stderr, "Invalid integer: %s\n", argument);
            free_list(head);
            return EXIT_FAILURE;
        }

        if (!append_node(&head, &tail, (int)value)) {
            fputs("Memory allocation failed\n", stderr);
            free_list(head);
            return EXIT_FAILURE;
        }
    }

    head = remove_consecutive_duplicates(head);

    if (!print_list(head)) {
        free_list(head);
        return EXIT_FAILURE;
    }

    free_list(head);
    return EXIT_SUCCESS;
}