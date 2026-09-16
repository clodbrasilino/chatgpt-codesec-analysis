#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct TupleNode {
    Tuple value;
    struct TupleNode *next;
} TupleNode;

typedef struct {
    TupleNode *head;
    TupleNode *tail;
    size_t size;
} TupleList;

static void tuple_list_init(TupleList *list)
{
    if (list != NULL) {
        list->head = NULL;
        list->tail = NULL;
        list->size = 0;
    }
}

static bool tuple_list_add(TupleList *list, const Tuple *tuple)
{
    TupleNode *node;

    if (list == NULL || tuple == NULL || list->size == SIZE_MAX) {
        return false;
    }

    node = malloc(sizeof(*node));
    if (node == NULL) {
        return false;
    }

    node->value.first = tuple->first;
    node->value.second = tuple->second;
    node->next = NULL;

    if (list->tail == NULL) {
        list->head = node;
    } else {
        list->tail->next = node;
    }

    list->tail = node;
    ++list->size;

    return true;
}

static bool tuple_list_contains(const TupleList *list, const Tuple *tuple)
{
    const TupleNode *current;

    if (list == NULL || tuple == NULL) {
        return false;
    }

    current = list->head;
    while (current != NULL) {
        if (current->value.first == tuple->first &&
            current->value.second == tuple->second) {
            return true;
        }

        current = current->next;
    }

    return false;
}

static void tuple_list_destroy(TupleList *list)
{
    TupleNode *current;

    if (list == NULL) {
        return;
    }

    current = list->head;
    while (current != NULL) {
        TupleNode *next = current->next;
        free(current);
        current = next;
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

int main(void)
{
    TupleList list;
    const Tuple tuple = {1, 2};
    int result = EXIT_SUCCESS;

    tuple_list_init(&list);

    if (!tuple_list_add(&list, &tuple) ||
        !tuple_list_contains(&list, &tuple)) {
        result = EXIT_FAILURE;
    }

    tuple_list_destroy(&list);
    return result;
}