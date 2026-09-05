#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int val1;
    int val2;
    int val3;
    int is_none1;
    int is_none2;
    int is_none3;
} Tuple;

typedef struct {
    Tuple *items;
    size_t count;
    size_t capacity;
} TupleList;

TupleList tuple_list_create(size_t initial_capacity) {
    TupleList list;
    list.capacity = initial_capacity > 0 ? initial_capacity : 1;
    list.count = 0;
    list.items = (Tuple *)malloc(list.capacity * sizeof(Tuple));
    if (list.items == NULL) {
        exit(EXIT_FAILURE);
    }
    return list;
}

void tuple_list_append(TupleList *list, Tuple t) {
    if (list->count == list->capacity) {
        size_t new_capacity = list->capacity * 2;
        Tuple *new_items = (Tuple *)realloc(list->items, new_capacity * sizeof(Tuple));
        if (new_items == NULL) {
            free(list->items);
            exit(EXIT_FAILURE);
        }
        list->items = new_items;
        list->capacity = new_capacity;
    }
    list->items[list->count++] = t;
}

void tuple_list_destroy(TupleList *list) {
    free(list->items);
    list->items = NULL;
    list->count = 0;
    list->capacity = 0;
}

TupleList remove_all_none_tuples(TupleList *list) {
    TupleList result = tuple_list_create(list->count > 0 ? list->count : 1);
    for (size_t i = 0; i < list->count; i++) {
        if (!(list->items[i].is_none1 && list->items[i].is_none2 && list->items[i].is_none3)) {
            tuple_list_append(&result, list->items[i]);
        }
    }
    return result;
}

int main(void) {
    TupleList list = tuple_list_create(4);

    tuple_list_append(&list, (Tuple){1, 2, 3, 0, 0, 0});
    tuple_list_append(&list, (Tuple){0, 0, 0, 1, 1, 1});
    tuple_list_append(&list, (Tuple){4, 0, 5, 0, 1, 0});
    tuple_list_append(&list, (Tuple){0, 0, 0, 1, 1, 1});
    tuple_list_append(&list, (Tuple){7, 8, 9, 0, 0, 0});

    TupleList filtered = remove_all_none_tuples(&list);

    for (size_t i = 0; i < filtered.count; i++) {
        printf("Tuple %zu: val1=%d, val2=%d, val3=%d\n", i, filtered.items[i].val1, filtered.items[i].val2, filtered.items[i].val3);
    }

    tuple_list_destroy(&list);
    tuple_list_destroy(&filtered);

    return 0;
}