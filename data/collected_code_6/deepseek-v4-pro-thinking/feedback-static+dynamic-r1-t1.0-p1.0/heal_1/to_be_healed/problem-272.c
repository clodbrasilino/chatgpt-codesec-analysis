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
    size_t size;
} TupleList;

int tuple_list_init(TupleList *list) {
    if (list == NULL) {
        return 0;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return 1;
}

int tuple_list_append(TupleList *list, const int *items, size_t length) {
    if (list == NULL || (items == NULL && length > 0)) {
        return 0;
    }
    TupleNode *node = malloc(sizeof(*node));
    if (node == NULL) {
        return 0;
    }
    node->tuple.items = NULL;
    node->tuple.length = length;
    if (length > 0) {
        node->tuple.items = malloc(length * sizeof(int));
        if (node->tuple.items == NULL) {
            free(node);
            return 0;
        }
        for (size_t i = 0; i < length; ++i) {
            node->tuple.items[i] = items[i];
        }
    }
    node->next = NULL;
    if (list->tail == NULL) {
        list->head = node;
    } else {
        list->tail->next = node;
    }
    list->tail = node;
    list->size++;
    return 1;
}

void tuple_list_free(TupleList *list) {
    if (list == NULL) {
        return;
    }
    TupleNode *current = list->head;
    while (current != NULL) {
        TupleNode *next = current->next;
        free(current->tuple.items);
        free(current);
        current = next;
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

int *extract_rear_elements(const TupleList *list, size_t *out_count) {
    if (list == NULL || out_count == NULL || list->size == 0) {
        if (out_count != NULL) {
            *out_count = 0;
        }
        return NULL;
    }
    int *result = malloc(list->size * sizeof(int));
    if (result == NULL) {
        *out_count = 0;
        return NULL;
    }
    size_t index = 0;
    const TupleNode *current = list->head;
    while (current != NULL) {
        if (current->tuple.length == 0) {
            free(result);
            *out_count = 0;
            return NULL;
        }
        result[index] = current->tuple.items[current->tuple.length - 1];
        index++;
        current = current->next;
    }
    *out_count = index;
    return result;
}

int main(void) {
    TupleList list;
    if (!tuple_list_init(&list)) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     *  Variable 't1' can be declared as const array [constVariable]
     */
    int t1[] = {10, 20, 30};
    /* Possible weaknesses found:
     *  Variable 't2' can be declared as const array [constVariable]
     */
    int t2[] = {40, 50};
    /* Possible weaknesses found:
     *  Variable 't3' can be declared as const array [constVariable]
     */
    int t3[] = {60, 70, 80, 90};

    if (!tuple_list_append(&list, t1, 3) ||
        !tuple_list_append(&list, t2, 2) ||
        !tuple_list_append(&list, t3, 4)) {
        tuple_list_free(&list);
        return EXIT_FAILURE;
    }

    size_t count = 0;
    int *rear_elements = extract_rear_elements(&list, &count);
    if (rear_elements == NULL) {
        tuple_list_free(&list);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        printf("%d\n", rear_elements[i]);
    }

    free(rear_elements);
    tuple_list_free(&list);
    return EXIT_SUCCESS;
}