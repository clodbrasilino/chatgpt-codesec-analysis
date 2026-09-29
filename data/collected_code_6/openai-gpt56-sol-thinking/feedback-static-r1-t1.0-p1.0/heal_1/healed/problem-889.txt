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
    List *new_list;
    Node **node_tail;
    List **list_tail;
    size_t i;

    if (lists == NULL || (values == NULL && count != 0U)) {
        return false;
    }

    new_list = calloc(1U, sizeof(*new_list));
    if (new_list == NULL) {
        return false;
    }

    node_tail = &new_list->head;

    for (i = 0U; i < count; ++i) {
        Node *node = malloc(sizeof(*node));

        if (node == NULL) {
            free_nodes(new_list->head);
            free(new_list);
            return false;
        }

        node->value = values[i];
        node->next = NULL;
        *node_tail = node;
        node_tail = &node->next;
    }

    list_tail = lists;
    while (*list_tail != NULL) {
        list_tail = &(*list_tail)->next;
    }

    *list_tail = new_list;
    return true;
}

static void reverse_each_list(List *lists)
{
    while (lists != NULL) {
        Node *previous = NULL;
        Node *current = lists->head;

        while (current != NULL) {
            Node *next = current->next;
            current->next = previous;
            previous = current;
            current = next;
        }

        lists->head = previous;
        lists = lists->next;
    }
}

static bool print_lists(const List *lists)
{
    if (fputc('[', stdout) == EOF) {
        return false;
    }

    while (lists != NULL) {
        const Node *node = lists->head;

        if (fputc('[', stdout) == EOF) {
            return false;
        }

        while (node != NULL) {
            if (fprintf(stdout, "%d", node->value) < 0) {
                return false;
            }

            if (node->next != NULL && fputs(", ", stdout) == EOF) {
                return false;
            }

            node = node->next;
        }

        if (fputc(']', stdout) == EOF) {
            return false;
        }

        if (lists->next != NULL && fputs(", ", stdout) == EOF) {
            return false;
        }

        lists = lists->next;
    }

    return fputs("]\n", stdout) != EOF;
}

int main(void)
{
    const int first[] = {1, 2, 3, 4};
    const int second[] = {5, 6, 7};
    const int third[] = {8, 9};
    List *lists = NULL;
    int status = EXIT_SUCCESS;

    if (!append_list(&lists, first, sizeof(first) / sizeof(first[0])) ||
        !append_list(&lists, second, sizeof(second) / sizeof(second[0])) ||
        !append_list(&lists, third, sizeof(third) / sizeof(third[0]))) {
        (void)fputs("Failed to create lists.\n", stderr);
        free_lists(lists);
        return EXIT_FAILURE;
    }

    reverse_each_list(lists);

    if (!print_lists(lists) || fflush(stdout) == EOF) {
        status = EXIT_FAILURE;
    }

    free_lists(lists);
    return status;
}