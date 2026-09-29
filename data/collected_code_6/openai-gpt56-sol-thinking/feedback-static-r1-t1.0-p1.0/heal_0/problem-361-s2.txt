#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Item {
    int value;
    struct Item *next;
} Item;

typedef struct List {
    Item *items;
    struct List *next;
} List;

static bool append_list(List **head, List **created)
{
    List *node;
    List **current;

    if (head == NULL || created == NULL) {
        return false;
    }

    node = calloc(1, sizeof(*node));
    if (node == NULL) {
        return false;
    }

    current = head;
    while (*current != NULL) {
        current = &(*current)->next;
    }

    *current = node;
    *created = node;
    return true;
}

static bool append_item(List *list, int value)
{
    Item *node;
    Item **current;

    if (list == NULL) {
        return false;
    }

    node = malloc(sizeof(*node));
    if (node == NULL) {
        return false;
    }

    node->value = value;
    node->next = NULL;

    current = &list->items;
    while (*current != NULL) {
        current = &(*current)->next;
    }

    *current = node;
    return true;
}

bool remove_empty_lists(List **head)
{
    List **current;

    if (head == NULL) {
        return false;
    }

    current = head;
    while (*current != NULL) {
        if ((*current)->items == NULL) {
            List *empty = *current;
            *current = empty->next;
            free(empty);
        } else {
            current = &(*current)->next;
        }
    }

    return true;
}

static void destroy_lists(List **head)
{
    List *list;

    if (head == NULL) {
        return;
    }

    list = *head;
    while (list != NULL) {
        List *next_list = list->next;
        Item *item = list->items;

        while (item != NULL) {
            Item *next_item = item->next;
            free(item);
            item = next_item;
        }

        free(list);
        list = next_list;
    }

    *head = NULL;
}

static bool print_lists(const List *head)
{
    const List *list = head;
    bool first_list = true;

    if (fputc('[', stdout) == EOF) {
        return false;
    }

    while (list != NULL) {
        const Item *item = list->items;
        bool first_item = true;

        if (!first_list && fputs(", ", stdout) == EOF) {
            return false;
        }

        if (fputc('[', stdout) == EOF) {
            return false;
        }

        while (item != NULL) {
            if (!first_item && fputs(", ", stdout) == EOF) {
                return false;
            }

            if (fprintf(stdout, "%d", item->value) < 0) {
                return false;
            }

            first_item = false;
            item = item->next;
        }

        if (fputc(']', stdout) == EOF) {
            return false;
        }

        first_list = false;
        list = list->next;
    }

    return fputs("]\n", stdout) != EOF;
}

int main(void)
{
    List *lists = NULL;
    List *list = NULL;
    int status = EXIT_FAILURE;

    if (!append_list(&lists, &list) ||
        !append_item(list, 1) ||
        !append_item(list, 2) ||
        !append_list(&lists, &list) ||
        !append_list(&lists, &list) ||
        !append_item(list, 3) ||
        !append_list(&lists, &list) ||
        !append_list(&lists, &list) ||
        !append_item(list, 4) ||
        !append_item(list, 5)) {
        goto cleanup;
    }

    if (!print_lists(lists)) {
        goto cleanup;
    }

    if (!remove_empty_lists(&lists)) {
        goto cleanup;
    }

    if (!print_lists(lists)) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    destroy_lists(&lists);

    if (fflush(stdout) == EOF) {
        status = EXIT_FAILURE;
    }

    return status;
}