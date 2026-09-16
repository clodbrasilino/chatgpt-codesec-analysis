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

static int append_node(Node ***tail, int value)
{
    Node *node;

    if (tail == NULL || *tail == NULL) {
        return 0;
    }

    node = malloc(sizeof(*node));
    if (node == NULL) {
        return 0;
    }

    node->value = value;
    node->next = NULL;

    **tail = node;
    *tail = &node->next;

    return 1;
}

static void remove_negative_numbers(Node **head)
{
    Node **link;

    if (head == NULL) {
        return;
    }

    link = head;

    while (*link != NULL) {
        Node *node = *link;

        if (node->value < 0) {
            *link = node->next;
            free(node);
        } else {
            link = &node->next;
        }
    }
}

static int parse_integer(const char *text, int *value)
{
    char *end;
    long result;

    if (text == NULL || value == NULL || *text == '\0') {
        return 0;
    }

    errno = 0;
    result = strtol(text, &end, 10);

    if (errno == ERANGE ||
        end == text ||
        *end != '\0' ||
        result < INT_MIN ||
        result > INT_MAX) {
        return 0;
    }

    *value = (int)result;
    return 1;
}

static int print_list(const Node *head)
{
    int first = 1;

    while (head != NULL) {
        if (!first && putchar(' ') == EOF) {
            return 0;
        }

        if (printf("%d", head->value) < 0) {
            return 0;
        }

        first = 0;
        head = head->next;
    }

    return putchar('\n') != EOF;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    Node *head = NULL;
    Node **tail = &head;

    for (int index = 1; index < argc; ++index) {
        int value;

        if (!parse_integer(argv[index], &value)) {
            fprintf(stderr, "Invalid integer: %s\n", argv[index]);
            free_list(head);
            return EXIT_FAILURE;
        }

        if (!append_node(&tail, value)) {
            fputs("Unable to allocate memory.\n", stderr);
            free_list(head);
            return EXIT_FAILURE;
        }
    }

    remove_negative_numbers(&head);

    if (!print_list(head)) {
        free_list(head);
        return EXIT_FAILURE;
    }

    free_list(head);
    return EXIT_SUCCESS;
}