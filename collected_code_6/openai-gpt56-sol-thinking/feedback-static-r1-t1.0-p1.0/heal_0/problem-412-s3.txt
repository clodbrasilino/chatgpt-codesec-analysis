#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
} List;

static bool list_append(List *list, int value)
{
    Node *node;

    if (list == NULL ||
        ((list->head == NULL) != (list->tail == NULL))) {
        return false;
    }

    node = malloc(sizeof(*node));
    if (node == NULL) {
        return false;
    }

    node->value = value;
    node->next = NULL;

    if (list->tail == NULL) {
        list->head = node;
    } else {
        list->tail->next = node;
    }

    list->tail = node;
    return true;
}

static bool remove_odd_numbers(List *list)
{
    Node **link;
    Node *node;
    Node *new_tail = NULL;

    if (list == NULL ||
        ((list->head == NULL) != (list->tail == NULL))) {
        return false;
    }

    link = &list->head;

    while (*link != NULL) {
        node = *link;

        if (node->value % 2 != 0) {
            *link = node->next;
            free(node);
        } else {
            new_tail = node;
            link = &node->next;
        }
    }

    list->tail = new_tail;
    return true;
}

static bool print_list(const List *list)
{
    const Node *node;
    bool first = true;

    if (list == NULL ||
        ((list->head == NULL) != (list->tail == NULL))) {
        return false;
    }

    for (node = list->head; node != NULL; node = node->next) {
        if (!first && fputc(' ', stdout) == EOF) {
            return false;
        }

        if (fprintf(stdout, "%d", node->value) < 0) {
            return false;
        }

        first = false;
    }

    return fputc('\n', stdout) != EOF;
}

static void list_destroy(List *list)
{
    Node *node;

    if (list == NULL) {
        return;
    }

    while (list->head != NULL) {
        node = list->head;
        list->head = node->next;
        free(node);
    }

    list->tail = NULL;
}

int main(void)
{
    List list = {NULL, NULL};
    size_t count;
    size_t index;
    int value;

    if (scanf("%zu", &count) != 1) {
        return EXIT_FAILURE;
    }

    for (index = 0; index < count; ++index) {
        if (scanf("%d", &value) != 1) {
            list_destroy(&list);
            return EXIT_FAILURE;
        }

        if (!list_append(&list, value)) {
            list_destroy(&list);
            return EXIT_FAILURE;
        }
    }

    if (!remove_odd_numbers(&list) || !print_list(&list)) {
        list_destroy(&list);
        return EXIT_FAILURE;
    }

    list_destroy(&list);
    return EXIT_SUCCESS;
}