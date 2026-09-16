#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct IntNode {
    int value;
    struct IntNode *next;
} IntNode;

typedef struct SublistNode {
    IntNode *head;
    IntNode *tail;
    size_t size;
    struct SublistNode *next;
} SublistNode;

typedef struct {
    SublistNode *head;
    SublistNode *tail;
    size_t size;
} ListOfLists;

static void initialize_list_of_lists(ListOfLists *list)
{
    if (list != NULL) {
        list->head = NULL;
        list->tail = NULL;
        list->size = 0;
    }
}

static void destroy_int_nodes(IntNode *node)
{
    while (node != NULL) {
        IntNode *next = node->next;
        free(node);
        node = next;
    }
}

static void destroy_sublist_node(SublistNode *sublist)
{
    if (sublist != NULL) {
        destroy_int_nodes(sublist->head);
        free(sublist);
    }
}

static void clear_list_of_lists(ListOfLists *list)
{
    if (list == NULL) {
        return;
    }

    SublistNode *sublist = list->head;

    while (sublist != NULL) {
        SublistNode *next = sublist->next;
        destroy_sublist_node(sublist);
        sublist = next;
    }

    initialize_list_of_lists(list);
}

static SublistNode *create_sublist(const int *values, size_t count)
{
    if (count > 0 && values == NULL) {
        return NULL;
    }

    SublistNode *sublist = malloc(sizeof(*sublist));

    if (sublist == NULL) {
        return NULL;
    }

    sublist->head = NULL;
    sublist->tail = NULL;
    sublist->size = 0;
    sublist->next = NULL;

    for (size_t i = 0; i < count; ++i) {
        IntNode *node = malloc(sizeof(*node));

        if (node == NULL) {
            destroy_sublist_node(sublist);
            return NULL;
        }

        node->value = values[i];
        node->next = NULL;

        if (sublist->tail == NULL) {
            sublist->head = node;
        } else {
            sublist->tail->next = node;
        }

        sublist->tail = node;
        ++sublist->size;
    }

    return sublist;
}

static bool append_sublist(ListOfLists *list, const int *values, size_t count)
{
    if (list == NULL || (count > 0 && values == NULL)) {
        return false;
    }

    SublistNode *sublist = create_sublist(values, count);

    if (sublist == NULL) {
        return false;
    }

    if (list->tail == NULL) {
        list->head = sublist;
    } else {
        list->tail->next = sublist;
    }

    list->tail = sublist;
    ++list->size;

    return true;
}

bool remove_sublists_outside_range(
    ListOfLists *list,
    size_t first_index,
    size_t last_index)
{
    if (list == NULL || first_index > last_index) {
        return false;
    }

    if (first_index >= list->size) {
        clear_list_of_lists(list);
        return true;
    }

    size_t original_size = list->size;

    for (size_t i = 0; i < first_index; ++i) {
        SublistNode *removed = list->head;
        list->head = removed->next;
        destroy_sublist_node(removed);
    }

    size_t retained_count;

    if (last_index >= original_size) {
        retained_count = original_size - first_index;
    } else {
        retained_count = last_index - first_index + 1;
    }

    SublistNode *last_retained = list->head;

    for (size_t i = 1; i < retained_count; ++i) {
        last_retained = last_retained->next;
    }

    SublistNode *removed = last_retained->next;
    last_retained->next = NULL;
    list->tail = last_retained;
    list->size = retained_count;

    while (removed != NULL) {
        SublistNode *next = removed->next;
        destroy_sublist_node(removed);
        removed = next;
    }

    return true;
}

static bool print_list_of_lists(const ListOfLists *list)
{
    if (list == NULL || putchar('[') == EOF) {
        return false;
    }

    const SublistNode *sublist = list->head;

    while (sublist != NULL) {
        if (putchar('[') == EOF) {
            return false;
        }

        const IntNode *node = sublist->head;

        while (node != NULL) {
            if (printf("%d", node->value) < 0) {
                return false;
            }

            if (node->next != NULL && fputs(", ", stdout) == EOF) {
                return false;
            }

            node = node->next;
        }

        if (putchar(']') == EOF) {
            return false;
        }

        if (sublist->next != NULL && fputs(", ", stdout) == EOF) {
            return false;
        }

        sublist = sublist->next;
    }

    return fputs("]\n", stdout) != EOF;
}

int main(void)
{
    ListOfLists list;
    const int first[] = {1, 2, 3};
    const int second[] = {4, 5};
    const int third[] = {6, 7, 8, 9};
    const int fourth[] = {10};
    const int fifth[] = {11, 12};

    initialize_list_of_lists(&list);

    if (!append_sublist(&list, first, sizeof(first) / sizeof(first[0])) ||
        !append_sublist(&list, second, sizeof(second) / sizeof(second[0])) ||
        !append_sublist(&list, third, sizeof(third) / sizeof(third[0])) ||
        !append_sublist(&list, fourth, sizeof(fourth) / sizeof(fourth[0])) ||
        !append_sublist(&list, fifth, sizeof(fifth) / sizeof(fifth[0]))) {
        clear_list_of_lists(&list);
        return EXIT_FAILURE;
    }

    if (fputs("Before: ", stdout) == EOF || !print_list_of_lists(&list)) {
        clear_list_of_lists(&list);
        return EXIT_FAILURE;
    }

    if (!remove_sublists_outside_range(&list, 1, 3)) {
        clear_list_of_lists(&list);
        return EXIT_FAILURE;
    }

    if (fputs("After:  ", stdout) == EOF || !print_list_of_lists(&list)) {
        clear_list_of_lists(&list);
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        clear_list_of_lists(&list);
        return EXIT_FAILURE;
    }

    clear_list_of_lists(&list);
    return EXIT_SUCCESS;
}