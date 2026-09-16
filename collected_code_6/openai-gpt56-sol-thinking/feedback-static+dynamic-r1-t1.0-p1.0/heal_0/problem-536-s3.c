#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    long value;
    struct Node *next;
} Node;

typedef enum {
    LIST_OK,
    LIST_INVALID_ARGUMENT,
    LIST_OUT_OF_MEMORY
} ListStatus;

static void free_list(Node *head)
{
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

static ListStatus append_node(Node **head, Node **tail, long value)
{
    Node *node;

    if (head == NULL || tail == NULL) {
        return LIST_INVALID_ARGUMENT;
    }

    node = malloc(sizeof(*node));
    if (node == NULL) {
        return LIST_OUT_OF_MEMORY;
    }

    node->value = value;
    node->next = NULL;

    if (*tail == NULL) {
        *head = node;
    } else {
        (*tail)->next = node;
    }

    *tail = node;
    return LIST_OK;
}

ListStatus select_nth_items(const Node *head, size_t n, Node **result)
{
    Node *selected_head = NULL;
    Node *selected_tail = NULL;
    size_t remaining;
    ListStatus status;

    if (result == NULL || n == 0) {
        return LIST_INVALID_ARGUMENT;
    }

    *result = NULL;
    remaining = n;

    while (head != NULL) {
        --remaining;

        if (remaining == 0) {
            status = append_node(&selected_head, &selected_tail, head->value);
            if (status != LIST_OK) {
                free_list(selected_head);
                return status;
            }
            remaining = n;
        }

        head = head->next;
    }

    *result = selected_head;
    return LIST_OK;
}

static int parse_size(const char *text, size_t *value)
{
    char *end;
    uintmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || *end != '\0' || parsed == 0 || parsed > SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int parse_long(const char *text, long *value)
{
    char *end;
    long parsed;

    if (text == NULL || value == NULL || *text == '\0') {
        return 0;
    }

    errno = 0;
    parsed = strtol(text, &end, 10);

    if (errno == ERANGE || *end != '\0') {
        return 0;
    }

    *value = parsed;
    return 1;
}

static int print_list(const Node *head)
{
    int first = 1;

    while (head != NULL) {
        if (!first && putchar(' ') == EOF) {
            return 0;
        }

        if (printf("%ld", head->value) < 0) {
            return 0;
        }

        first = 0;
        head = head->next;
    }

    return putchar('\n') != EOF;
}

int main(int argc, char **argv)
{
    Node *head = NULL;
    Node *tail = NULL;
    Node *selected = NULL;
    size_t n;
    ListStatus status;
    int i;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s n [item ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_size(argv[1], &n)) {
        fprintf(stderr, "Invalid selection interval: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    for (i = 2; i < argc; ++i) {
        long value;

        if (!parse_long(argv[i], &value)) {
            fprintf(stderr, "Invalid list item: %s\n", argv[i]);
            free_list(head);
            return EXIT_FAILURE;
        }

        status = append_node(&head, &tail, value);
        if (status != LIST_OK) {
            fprintf(stderr, "Unable to allocate memory\n");
            free_list(head);
            return EXIT_FAILURE;
        }
    }

    status = select_nth_items(head, n, &selected);
    if (status != LIST_OK) {
        fprintf(stderr, "Unable to select list items\n");
        free_list(head);
        return EXIT_FAILURE;
    }

    if (!print_list(selected) || fflush(stdout) == EOF) {
        fprintf(stderr, "Unable to write output\n");
        free_list(selected);
        free_list(head);
        return EXIT_FAILURE;
    }

    free_list(selected);
    free_list(head);
    return EXIT_SUCCESS;
}