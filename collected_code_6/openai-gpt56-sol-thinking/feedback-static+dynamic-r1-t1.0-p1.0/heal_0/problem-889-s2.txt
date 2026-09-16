#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    struct List *next;
} List;

static void free_nodes(Node *head)
{
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

static void free_lists(List *lists)
{
    while (lists != NULL) {
        List *next = lists->next;
        free_nodes(lists->head);
        free(lists);
        lists = next;
    }
}

static bool append_list(List **lists, const int *values, size_t count)
{
    Node *head = NULL;
    Node *tail = NULL;
    List *new_list;
    List **position;
    size_t i;

    if (lists == NULL || (values == NULL && count != 0U)) {
        return false;
    }

    for (i = 0U; i < count; ++i) {
        Node *node = malloc(sizeof(*node));

        if (node == NULL) {
            free_nodes(head);
            return false;
        }

        node->value = values[i];
        node->next = NULL;

        if (tail == NULL) {
            head = node;
        } else {
            tail->next = node;
        }

        tail = node;
    }

    new_list = malloc(sizeof(*new_list));
    if (new_list == NULL) {
        free_nodes(head);
        return false;
    }

    new_list->head = head;
    new_list->next = NULL;

    position = lists;
    while (*position != NULL) {
        position = &(*position)->next;
    }
    *position = new_list;

    return true;
}

static Node *reverse_list(Node *head)
{
    Node *previous = NULL;

    while (head != NULL) {
        Node *next = head->next;
        head->next = previous;
        previous = head;
        head = next;
    }

    return previous;
}

static void reverse_each_list(List *lists)
{
    while (lists != NULL) {
        lists->head = reverse_list(lists->head);
        lists = lists->next;
    }
}

static bool print_lists(const List *lists)
{
    while (lists != NULL) {
        const Node *node = lists->head;

        if (putchar('[') == EOF) {
            return false;
        }

        while (node != NULL) {
            if (printf("%d", node->value) < 0) {
                return false;
            }

            if (node->next != NULL && fputs(", ", stdout) == EOF) {
                return false;
            }

            node = node->next;
        }

        if (fputs("]\n", stdout) == EOF) {
            return false;
        }

        lists = lists->next;
    }

    return true;
}

int main(void)
{
    const int first[] = {1, 2, 3, 4};
    const int second[] = {5, 6, 7};
    const int third[] = {8, 9};
    List *lists = NULL;

    if (!append_list(&lists, first, sizeof(first) / sizeof(first[0])) ||
        !append_list(&lists, second, sizeof(second) / sizeof(second[0])) ||
        !append_list(&lists, NULL, 0U) ||
        !append_list(&lists, third, sizeof(third) / sizeof(third[0]))) {
        free_lists(lists);
        if (fputs("Failed to create lists.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    reverse_each_list(lists);

    if (!print_lists(lists)) {
        free_lists(lists);
        return EXIT_FAILURE;
    }

    free_lists(lists);
    return EXIT_SUCCESS;
}