#include <stdint.h>
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

static void free_parts(Node **parts, size_t count)
{
    if (parts == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free_list(parts[i]);
    }

    free(parts);
}

static int create_list(const int *values, size_t count, Node **head)
{
    Node **tail;

    if (head == NULL || (values == NULL && count != 0U)) {
        return -1;
    }

    *head = NULL;
    tail = head;

    for (size_t i = 0; i < count; ++i) {
        Node *node = malloc(sizeof(*node));

        if (node == NULL) {
            free_list(*head);
            *head = NULL;
            return -1;
        }

        node->value = values[i];
        node->next = NULL;
        *tail = node;
        tail = &node->next;
    }

    return 0;
}

static int split_list_every_n(Node *head, size_t n, Node ***parts,
                              size_t *part_count)
{
    Node **result;
    Node *current;
    size_t length = 0;
    size_t count;

    if (parts != NULL) {
        *parts = NULL;
    }

    if (part_count != NULL) {
        *part_count = 0;
    }

    if (parts == NULL || part_count == NULL || n == 0U) {
        return -1;
    }

    for (current = head; current != NULL; current = current->next) {
        if (length == SIZE_MAX) {
            return -1;
        }
        ++length;
    }

    if (length == 0U) {
        return 0;
    }

    count = length / n;
    if (length % n != 0U) {
        ++count;
    }

    if (count > SIZE_MAX / sizeof(*result)) {
        return -1;
    }

    result = malloc(count * sizeof(*result));
    if (result == NULL) {
        return -1;
    }

    current = head;

    for (size_t i = 0; i < count; ++i) {
        Node *next;

        result[i] = current;

        for (size_t j = 1; j < n && current->next != NULL; ++j) {
            current = current->next;
        }

        next = current->next;
        current->next = NULL;
        current = next;
    }

    *parts = result;
    *part_count = count;
    return 0;
}

int main(void)
{
    const int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Node *list = NULL;
    Node **parts = NULL;
    size_t part_count = 0;
    int status = EXIT_SUCCESS;

    if (create_list(values, sizeof(values) / sizeof(values[0]), &list) != 0) {
        fputs("Failed to create the list.\n", stderr);
        return EXIT_FAILURE;
    }

    if (split_list_every_n(list, 3U, &parts, &part_count) != 0) {
        fputs("Failed to split the list.\n", stderr);
        free_list(list);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < part_count; ++i) {
        for (Node *node = parts[i]; node != NULL; node = node->next) {
            if (printf("%d%s", node->value,
                       node->next == NULL ? "" : " ") < 0) {
                status = EXIT_FAILURE;
                break;
            }
        }

        if (status != EXIT_SUCCESS || putchar('\n') == EOF) {
            status = EXIT_FAILURE;
            break;
        }
    }

    free_parts(parts, part_count);
    return status;
}