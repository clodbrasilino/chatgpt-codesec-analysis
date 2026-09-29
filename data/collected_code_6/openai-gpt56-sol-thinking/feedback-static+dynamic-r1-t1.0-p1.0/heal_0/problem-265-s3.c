#include <stdbool.h>
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

static bool list_has_cycle(const Node *head)
{
    const Node *slow = head;
    const Node *fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            return true;
        }
    }

    return false;
}

static bool split_list(Node **list, size_t n, Node ***parts_out,
                       size_t *part_count_out)
{
    Node **parts;
    Node *current;
    size_t length = 0;
    size_t part_count;
    size_t i;

    if (parts_out != NULL) {
        *parts_out = NULL;
    }

    if (part_count_out != NULL) {
        *part_count_out = 0;
    }

    if (list == NULL || parts_out == NULL || part_count_out == NULL || n == 0) {
        return false;
    }

    if (*list == NULL) {
        return true;
    }

    if (list_has_cycle(*list)) {
        return false;
    }

    for (current = *list; current != NULL; current = current->next) {
        if (length == SIZE_MAX) {
            return false;
        }
        ++length;
    }

    part_count = length / n;
    if (length % n != 0) {
        ++part_count;
    }

    if (part_count > SIZE_MAX / sizeof(*parts)) {
        return false;
    }

    parts = malloc(part_count * sizeof(*parts));
    if (parts == NULL) {
        return false;
    }

    current = *list;

    for (i = 0; i < part_count; ++i) {
        Node *next;
        size_t position;

        parts[i] = current;

        for (position = 1; position < n && current->next != NULL; ++position) {
            current = current->next;
        }

        next = current->next;
        current->next = NULL;
        current = next;
    }

    *list = NULL;
    *parts_out = parts;
    *part_count_out = part_count;
    return true;
}

static void free_parts(Node **parts, size_t part_count)
{
    size_t i;

    if (parts == NULL) {
        return;
    }

    for (i = 0; i < part_count; ++i) {
        free_list(parts[i]);
    }

    free(parts);
}

static bool print_parts(Node *const *parts, size_t part_count)
{
    size_t i;

    for (i = 0; i < part_count; ++i) {
        const Node *current;

        if (printf("Part %zu:", i + 1) < 0) {
            return false;
        }

        for (current = parts[i]; current != NULL; current = current->next) {
            if (printf(" %d", current->value) < 0) {
                return false;
            }
        }

        if (putchar('\n') == EOF) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    const int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    const size_t value_count = sizeof(values) / sizeof(values[0]);
    const size_t n = 3;
    Node *list = NULL;
    Node *tail = NULL;
    Node **parts = NULL;
    size_t part_count = 0;
    size_t i;
    bool printed;

    for (i = 0; i < value_count; ++i) {
        if (!append_node(&list, &tail, values[i])) {
            free_list(list);
            return EXIT_FAILURE;
        }
    }

    if (!split_list(&list, n, &parts, &part_count)) {
        free_list(list);
        return EXIT_FAILURE;
    }

    printed = print_parts(parts, part_count);
    free_parts(parts, part_count);

    return printed ? EXIT_SUCCESS : EXIT_FAILURE;
}