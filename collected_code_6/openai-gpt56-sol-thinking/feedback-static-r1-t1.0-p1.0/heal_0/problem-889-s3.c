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

static bool create_node_list(const int values[], size_t count, Node **head)
{
    Node **tail;

    if (head == NULL || (count > 0U && values == NULL)) {
        return false;
    }

    *head = NULL;
    tail = head;

    for (size_t i = 0; i < count; ++i) {
        Node *node = malloc(sizeof(*node));

        if (node == NULL) {
            free_nodes(*head);
            *head = NULL;
            return false;
        }

        node->value = values[i];
        node->next = NULL;
        *tail = node;
        tail = &node->next;
    }

    return true;
}

static bool append_list(List **lists, Node *head)
{
    List *new_list;
    List **tail;

    if (lists == NULL) {
        return false;
    }

    new_list = malloc(sizeof(*new_list));
    if (new_list == NULL) {
        return false;
    }

    new_list->head = head;
    new_list->next = NULL;

    tail = lists;
    while (*tail != NULL) {
        tail = &(*tail)->next;
    }

    *tail = new_list;
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

void reverse_each_list(List *lists)
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

        if (fputs("]\n", stdout) == EOF) {
            return false;
        }

        lists = lists->next;
    }

    return true;
}

int main(void)
{
    static const int first[] = {1, 2, 3, 4};
    static const int second[] = {5, 6, 7};
    static const int third[] = {8, 9};
    static const struct {
        const int *values;
        size_t count;
    } input[] = {
        {first, sizeof(first) / sizeof(first[0])},
        {second, sizeof(second) / sizeof(second[0])},
        {third, sizeof(third) / sizeof(third[0])},
        {NULL, 0U}
    };

    List *lists = NULL;

    for (size_t i = 0; i < sizeof(input) / sizeof(input[0]); ++i) {
        Node *head = NULL;

        if (!create_node_list(input[i].values, input[i].count, &head)) {
            free_lists(lists);
            return EXIT_FAILURE;
        }

        if (!append_list(&lists, head)) {
            free_nodes(head);
            free_lists(lists);
            return EXIT_FAILURE;
        }
    }

    reverse_each_list(lists);

    if (!print_lists(lists)) {
        free_lists(lists);
        return EXIT_FAILURE;
    }

    free_lists(lists);
    return EXIT_SUCCESS;
}