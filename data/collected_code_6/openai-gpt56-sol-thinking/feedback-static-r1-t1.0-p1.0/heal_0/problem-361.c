#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int value;
    struct ListNode *next;
} ListNode;

typedef struct InnerList {
    ListNode *head;
} InnerList;

typedef struct ListOfListsNode {
    InnerList *list;
    struct ListOfListsNode *next;
} ListOfListsNode;

static InnerList *inner_list_create(void)
{
    InnerList *list = malloc(sizeof(*list));

    if (list != NULL) {
        list->head = NULL;
    }

    return list;
}

static void inner_list_destroy(InnerList *list)
{
    if (list != NULL) {
        ListNode *current = list->head;

        while (current != NULL) {
            ListNode *next = current->next;
            free(current);
            current = next;
        }

        free(list);
    }
}

static bool inner_list_append(InnerList *list, int value)
{
    ListNode *node;
    ListNode **link;

    if (list == NULL) {
        return false;
    }

    node = malloc(sizeof(*node));
    if (node == NULL) {
        return false;
    }

    node->value = value;
    node->next = NULL;

    link = &list->head;
    while (*link != NULL) {
        link = &(*link)->next;
    }

    *link = node;
    return true;
}

static void list_of_lists_destroy(ListOfListsNode *head)
{
    while (head != NULL) {
        ListOfListsNode *next = head->next;
        inner_list_destroy(head->list);
        free(head);
        head = next;
    }
}

static bool list_of_lists_append_values(
    ListOfListsNode **head,
    const int *values,
    size_t count)
{
    InnerList *list;
    ListOfListsNode *node;
    ListOfListsNode **link;
    size_t i;

    if (head == NULL || (count > 0U && values == NULL)) {
        return false;
    }

    list = inner_list_create();
    if (list == NULL) {
        return false;
    }

    for (i = 0U; i < count; ++i) {
        if (!inner_list_append(list, values[i])) {
            inner_list_destroy(list);
            return false;
        }
    }

    node = malloc(sizeof(*node));
    if (node == NULL) {
        inner_list_destroy(list);
        return false;
    }

    node->list = list;
    node->next = NULL;

    link = head;
    while (*link != NULL) {
        link = &(*link)->next;
    }

    *link = node;
    return true;
}

void remove_empty_lists(ListOfListsNode **head)
{
    ListOfListsNode **link;

    if (head == NULL) {
        return;
    }

    link = head;

    while (*link != NULL) {
        ListOfListsNode *current = *link;

        if (current->list == NULL || current->list->head == NULL) {
            *link = current->next;
            inner_list_destroy(current->list);
            free(current);
        } else {
            link = &current->next;
        }
    }
}

static bool print_list_of_lists(const ListOfListsNode *head)
{
    while (head != NULL) {
        const ListNode *node;
        bool first = true;

        if (fputc('[', stdout) == EOF) {
            return false;
        }

        node = head->list->head;

        while (node != NULL) {
            if (!first && fputs(", ", stdout) == EOF) {
                return false;
            }

            if (fprintf(stdout, "%d", node->value) < 0) {
                return false;
            }

            first = false;
            node = node->next;
        }

        if (fputs("]\n", stdout) == EOF) {
            return false;
        }

        head = head->next;
    }

    return true;
}

int main(void)
{
    ListOfListsNode *lists = NULL;
    const int first[] = {1, 2};
    const int second[] = {3};

    if (!list_of_lists_append_values(&lists, NULL, 0U) ||
        !list_of_lists_append_values(
            &lists, first, sizeof(first) / sizeof(first[0])) ||
        !list_of_lists_append_values(&lists, NULL, 0U) ||
        !list_of_lists_append_values(
            &lists, second, sizeof(second) / sizeof(second[0])) ||
        !list_of_lists_append_values(&lists, NULL, 0U)) {
        list_of_lists_destroy(lists);
        fputs("Failed to create the list of lists.\n", stderr);
        return EXIT_FAILURE;
    }

    remove_empty_lists(&lists);

    if (!print_list_of_lists(lists) || fflush(stdout) == EOF) {
        list_of_lists_destroy(lists);
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    list_of_lists_destroy(lists);
    return EXIT_SUCCESS;
}