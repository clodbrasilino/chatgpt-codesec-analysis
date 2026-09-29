#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void **values;
    size_t length;
} Tuple;

typedef struct {
    Tuple *items;
    size_t count;
    size_t capacity;
} TupleList;

bool tuple_is_all_none(const Tuple *tuple) {
    if (tuple == NULL || tuple->values == NULL) {
        return true;
    }
    for (size_t i = 0; i < tuple->length; ++i) {
        if (tuple->values[i] != NULL) {
            return false;
        }
    }
    return true;
}

void remove_all_none_tuples(TupleList *list) {
    if (list == NULL || list->items == NULL || list->count == 0) {
        return;
    }
    size_t write = 0;
    for (size_t read = 0; read < list->count; ++read) {
        Tuple *current = &list->items[read];
        if (tuple_is_all_none(current)) {
            free(current->values);
            current->values = NULL;
            current->length = 0;
        } else {
            if (write != read) {
                list->items[write] = list->items[read];
                list->items[read].values = NULL;
                list->items[read].length = 0;
            }
            ++write;
        }
    }
    list->count = write;
}

TupleList *tuple_list_create(void) {
    TupleList *list = malloc(sizeof(*list));
    if (list == NULL) {
        return NULL;
    }
    list->items = NULL;
    list->count = 0;
    list->capacity = 0;
    return list;
}

bool tuple_list_append(TupleList *list, void **values, size_t length) {
    if (list == NULL || (length > 0 && values == NULL)) {
        return false;
    }
    if (list->count == list->capacity) {
        size_t new_capacity = list->capacity == 0 ? 4 : list->capacity * 2;
        Tuple *new_items = realloc(list->items, new_capacity * sizeof(*new_items));
        if (new_items == NULL) {
            return false;
        }
        list->items = new_items;
        list->capacity = new_capacity;
    }
    list->items[list->count].values = values;
    list->items[list->count].length = length;
    ++list->count;
    return true;
}

void tuple_list_free(TupleList *list) {
    if (list == NULL) {
        return;
    }
    for (size_t i = 0; i < list->count; ++i) {
        free(list->items[i].values);
    }
    free(list->items);
    free(list);
}

int main(void) {
    TupleList *list = tuple_list_create();
    if (list == NULL) {
        return EXIT_FAILURE;
    }

    void **tuple1 = malloc(3 * sizeof(*tuple1));
    if (tuple1 == NULL) {
        tuple_list_free(list);
        return EXIT_FAILURE;
    }
    tuple1[0] = NULL;
    tuple1[1] = NULL;
    tuple1[2] = NULL;

    if (!tuple_list_append(list, tuple1, 3)) {
        free(tuple1);
        tuple_list_free(list);
        return EXIT_FAILURE;
    }

    void **tuple2 = malloc(3 * sizeof(*tuple2));
    if (tuple2 == NULL) {
        tuple_list_free(list);
        return EXIT_FAILURE;
    }
    tuple2[0] = NULL;
    tuple2[1] = (void *)0x1;
    tuple2[2] = NULL;

    if (!tuple_list_append(list, tuple2, 3)) {
        free(tuple2);
        tuple_list_free(list);
        return EXIT_FAILURE;
    }

    void **tuple3 = malloc(2 * sizeof(*tuple3));
    if (tuple3 == NULL) {
        tuple_list_free(list);
        return EXIT_FAILURE;
    }
    tuple3[0] = NULL;
    tuple3[1] = NULL;

    if (!tuple_list_append(list, tuple3, 2)) {
        free(tuple3);
        tuple_list_free(list);
        return EXIT_FAILURE;
    }

    remove_all_none_tuples(list);

    printf("Remaining tuples: %zu\n", list->count);
    for (size_t i = 0; i < list->count; ++i) {
        printf("Tuple %zu length %zu\n", i, list->items[i].length);
    }

    tuple_list_free(list);
    return EXIT_SUCCESS;
}