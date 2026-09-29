#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *items;
    size_t length;
} Tuple;

typedef struct TupleNode {
    Tuple tuple;
    struct TupleNode *next;
} TupleNode;

typedef struct {
    TupleNode *head;
    TupleNode *tail;
} TupleList;

static void tuple_list_init(TupleList *list)
{
    if (list != NULL) {
        list->head = NULL;
        list->tail = NULL;
    }
}

static int tuple_list_append(TupleList *list, const int *items, size_t length)
{
    TupleNode *node;
    int *copied_items = NULL;

    if (list == NULL || (length != 0U && items == NULL)) {
        return 0;
    }

    if (length > SIZE_MAX / sizeof(*copied_items)) {
        return 0;
    }

    if (length != 0U) {
        copied_items = malloc(length * sizeof(*copied_items));
        if (copied_items == NULL) {
            return 0;
        }

        for (size_t i = 0U; i < length; ++i) {
            copied_items[i] = items[i];
        }
    }

    node = malloc(sizeof(*node));
    if (node == NULL) {
        free(copied_items);
        return 0;
    }

    node->tuple.items = copied_items;
    node->tuple.length = length;
    node->next = NULL;

    if (list->tail == NULL) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }

    return 1;
}

static size_t tuple_list_remove_empty(TupleList *list)
{
    TupleNode **current;
    TupleNode *last = NULL;
    size_t removed = 0U;

    if (list == NULL) {
        return 0U;
    }

    current = &list->head;

    while (*current != NULL) {
        TupleNode *node = *current;

        if (node->tuple.length == 0U) {
            *current = node->next;
            free(node->tuple.items);
            free(node);
            ++removed;
        } else {
            last = node;
            current = &node->next;
        }
    }

    list->tail = last;
    return removed;
}

static void tuple_list_print(const TupleList *list)
{
    const TupleNode *node;

    if (list == NULL) {
        return;
    }

    putchar('[');

    for (node = list->head; node != NULL; node = node->next) {
        putchar('(');

        for (size_t i = 0U; i < node->tuple.length; ++i) {
            if (i != 0U) {
                fputs(", ", stdout);
            }

            printf("%d", node->tuple.items[i]);
        }

        putchar(')');

        if (node->next != NULL) {
            fputs(", ", stdout);
        }
    }

    puts("]");
}

static void tuple_list_destroy(TupleList *list)
{
    TupleNode *node;

    if (list == NULL) {
        return;
    }

    node = list->head;

    while (node != NULL) {
        TupleNode *next = node->next;

        free(node->tuple.items);
        free(node);
        node = next;
    }

    list->head = NULL;
    list->tail = NULL;
}

int main(void)
{
    TupleList list;
    const int first[] = {1, 2};
    const int second[] = {3, 4, 5};

    tuple_list_init(&list);

    if (!tuple_list_append(&list, first, sizeof(first) / sizeof(first[0])) ||
        !tuple_list_append(&list, NULL, 0U) ||
        !tuple_list_append(&list, second, sizeof(second) / sizeof(second[0])) ||
        !tuple_list_append(&list, NULL, 0U)) {
        tuple_list_destroy(&list);
        fputs("Failed to create tuple list.\n", stderr);
        return EXIT_FAILURE;
    }

    tuple_list_remove_empty(&list);
    tuple_list_print(&list);
    tuple_list_destroy(&list);

    return EXIT_SUCCESS;
}