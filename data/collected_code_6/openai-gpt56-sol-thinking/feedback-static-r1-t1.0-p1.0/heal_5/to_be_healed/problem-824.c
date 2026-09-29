#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

static void remove_even_numbers(Node **head)
{
    Node **current;

    if (head == NULL) {
        return;
    }

    current = head;

    while (*current != NULL) {
        Node *node = *current;

        if (node->value % 2 == 0) {
            *current = node->next;
            free(node);
        } else {
            current = &node->next;
        }
    }
}

static void free_list(Node *head)
{
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

static int parse_integer(const char *text, int *value)
{
    char *end;
    long parsed;

    if (text == NULL || value == NULL || *text == '\0') {
        return 0;
    }

    errno = 0;
    parsed = strtol(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed < INT_MIN || parsed > INT_MAX) {
        return 0;
    }

    *value = (int)parsed;
    return 1;
}

static int build_list(int count, const char *const values[], Node **head)
{
    Node *tail = NULL;
    int i;

    if (head == NULL || count < 0 || (count > 0 && values == NULL)) {
        return -1;
    }

    *head = NULL;

    for (i = 0; i < count; ++i) {
        Node *node;
        int value;

        if (!parse_integer(values[i], &value)) {
            free_list(*head);
            *head = NULL;
            return -1;
        }

        node = malloc(sizeof(*node));
        if (node == NULL) {
            free_list(*head);
            *head = NULL;
            return -2;
        }

        node->value = value;
        node->next = NULL;

        if (tail == NULL) {
            *head = node;
        } else {
            tail->next = node;
        }

        tail = node;
    }

    return 0;
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
int main(int argc, char *argv[])
{
    Node *head = NULL;
    const char **values = NULL;
    int count = argc > 1 ? argc - 1 : 0;
    int result;
    /* Possible weaknesses found:
     *  The scope of the variable 'i' can be reduced. [variableScope]
     */
    int i;

    if (count > 0) {
        values = calloc((size_t)count, sizeof(*values));
        if (values == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }

        for (i = 0; i < count; ++i) {
            values[i] = argv[i + 1];
        }
    }

    result = build_list(count, values, &head);
    free(values);

    if (result == -1) {
        fputs("Invalid integer input\n", stderr);
        return EXIT_FAILURE;
    }

    if (result == -2) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    remove_even_numbers(&head);

    if (!print_list(head)) {
        free_list(head);
        return EXIT_FAILURE;
    }

    free_list(head);
    return EXIT_SUCCESS;
}