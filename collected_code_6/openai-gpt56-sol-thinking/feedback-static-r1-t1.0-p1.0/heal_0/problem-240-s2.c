#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

static void list_destroy(Node *head)
{
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

static bool list_from_array(const int *values, size_t count, Node **out)
{
    Node *head = NULL;
    Node **tail = &head;

    if (out == NULL || (values == NULL && count != 0U)) {
        return false;
    }

    *out = NULL;

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

static bool list_clone(const Node *source, Node **out)
{
    Node *copy = NULL;
    Node **tail = &copy;

    if (out == NULL) {
        return false;
    }

    *out = NULL;

    while (source != NULL) {
        Node *node = malloc(sizeof(*node));

        if (node == NULL) {
            list_destroy(copy);
            return false;
        }

        node->value = source->value;
        node->next = NULL;
        *tail = node;
        tail = &node->next;
        source = source->next;
    }

    *out = copy;
    return true;
}

static bool replace_last_with_list(Node **list, const Node *replacement)
{
    Node *replacement_copy = NULL;
    Node *current;

    if (list == NULL || *list == NULL) {
        return false;
    }

    if (!list_clone(replacement, &replacement_copy)) {
        return false;
    }

    if ((*list)->next == NULL) {
        free(*list);
        *list = replacement_copy;
        return true;
    }

    current = *list;

    while (current->next->next != NULL) {
        current = current->next;
    }

    free(current->next);
    current->next = replacement_copy;
    return true;
}

static bool list_print(const Node *head)
{
    const Node *current = head;

    while (current != NULL) {
        if (printf("%d", current->value) < 0) {
            return false;
        }

        current = current->next;

        if (current != NULL && putchar(' ') == EOF) {
            return false;
        }
    }

    return putchar('\n') != EOF;
}

int main(void)
{
    const int original_values[] = {1, 2, 3};
    const int replacement_values[] = {7, 8, 9};
    Node *list = NULL;
    Node *replacement = NULL;
    int status = EXIT_FAILURE;

    if (!list_from_array(
            original_values,
            sizeof(original_values) / sizeof(original_values[0]),
            &list)) {
        goto cleanup;
    }

    if (!list_from_array(
            replacement_values,
            sizeof(replacement_values) / sizeof(replacement_values[0]),
            &replacement)) {
        goto cleanup;
    }

    if (!replace_last_with_list(&list, replacement)) {
        goto cleanup;
    }

    if (!list_print(list)) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    list_destroy(replacement);
    list_destroy(list);
    return status;
}