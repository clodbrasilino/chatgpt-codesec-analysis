#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef enum {
    LIST_SUCCESS,
    LIST_INVALID_ARGUMENT,
    LIST_EMPTY,
    LIST_INVALID_STRUCTURE
} ListResult;

static void list_destroy(Node *head)
{
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

static bool list_is_acyclic(const Node *head)
{
    const Node *slow = head;
    const Node *fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            return false;
        }
    }

    return true;
}

static bool lists_are_disjoint(const Node *first, const Node *second)
{
    for (const Node *a = first; a != NULL; a = a->next) {
        for (const Node *b = second; b != NULL; b = b->next) {
            if (a == b) {
                return false;
            }
        }
    }

    return true;
}

static bool list_from_array(Node **out, const int *values, size_t count)
{
    Node *head = NULL;
    Node **tail = &head;

    if (out == NULL || *out != NULL || (values == NULL && count != 0U)) {
        return false;
    }

    for (size_t i = 0; i < count; ++i) {
        Node *node = malloc(sizeof(*node));

        if (node == NULL) {
            list_destroy(head);
            return false;
        }

        node->value = values[i];
        node->next = NULL;
        *tail = node;
        tail = &node->next;
    }

    *out = head;
    return true;
}

static ListResult list_replace_last(Node **list, Node **replacement)
{
    Node *previous = NULL;
    Node *current;

    if (list == NULL || replacement == NULL || list == replacement) {
        return LIST_INVALID_ARGUMENT;
    }

    if (!list_is_acyclic(*list) || !list_is_acyclic(*replacement)) {
        return LIST_INVALID_STRUCTURE;
    }

    if (*list == NULL) {
        return LIST_EMPTY;
    }

    if (!lists_are_disjoint(*list, *replacement)) {
        return LIST_INVALID_STRUCTURE;
    }

    current = *list;

    while (current->next != NULL) {
        previous = current;
        current = current->next;
    }

    if (previous == NULL) {
        *list = *replacement;
    } else {
        previous->next = *replacement;
    }

    *replacement = NULL;
    free(current);

    return LIST_SUCCESS;
}

static bool list_print(const Node *head)
{
    if (putchar('[') == EOF) {
        return false;
    }

    while (head != NULL) {
        if (printf("%d", head->value) < 0) {
            return false;
        }

        head = head->next;

        if (head != NULL && fputs(", ", stdout) == EOF) {
            return false;
        }
    }

    return fputs("]\n", stdout) != EOF;
}

int main(void)
{
    const int original_values[] = {1, 2, 3};
    const int replacement_values[] = {7, 8, 9};
    Node *list = NULL;
    Node *replacement = NULL;
    ListResult result;

    if (!list_from_array(&list, original_values,
                         sizeof(original_values) / sizeof(original_values[0]))) {
        return EXIT_FAILURE;
    }

    if (!list_from_array(&replacement, replacement_values,
                         sizeof(replacement_values) / sizeof(replacement_values[0]))) {
        list_destroy(list);
        return EXIT_FAILURE;
    }

    result = list_replace_last(&list, &replacement);

    if (result != LIST_SUCCESS) {
        list_destroy(list);
        list_destroy(replacement);
        return EXIT_FAILURE;
    }

    if (!list_print(list)) {
        list_destroy(list);
        return EXIT_FAILURE;
    }

    list_destroy(list);
    return EXIT_SUCCESS;
}