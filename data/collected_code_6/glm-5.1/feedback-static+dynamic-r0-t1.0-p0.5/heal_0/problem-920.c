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

int tuple_list_init(TupleList *list, size_t initial_capacity) {
    if (list == NULL) {
        return -1;
    }
    list->items = (Tuple *)malloc(initial_capacity * sizeof(Tuple));
    if (list->items == NULL) {
        return -1;
    }
    list->count = 0;
    list->capacity = initial_capacity;
    return 0;
}

int tuple_list_append(TupleList *list, Tuple t) {
    if (list == NULL || list->items == NULL) {
        return -1;
    }
    if (list->count >= list->capacity) {
        size_t new_capacity = list->capacity * 2;
        Tuple *new_items = (Tuple *)realloc(list->items, new_capacity * sizeof(Tuple));
        if (new_items == NULL) {
            return -1;
        }
        list->items = new_items;
        list->capacity = new_capacity;
    }
    list->items[list->count] = t;
    list->count++;
    return 0;
}

void tuple_list_free(TupleList *list) {
    if (list != NULL) {
        free(list->items);
        list->items = NULL;
        list->count = 0;
        list->capacity = 0;
    }
}

int remove_all_none_tuples(TupleList *list) {
    if (list == NULL || list->items == NULL) {
        return -1;
    }
    size_t write_index = 0;
    for (size_t read_index = 0; read_index < list->count; read_index++) {
        Tuple current = list->items[read_index];
        if (!(current.is_none1 && current.is_none2 && current.is_none3)) {
            if (write_index != read_index) {
                list->items[write_index] = current;
            }
            write_index++;
        }
    }
    list->count = write_index;
    return 0;
}

int main(void) {
    TupleList list;
    if (tuple_list_init(&list, 4) != 0) {
        return EXIT_FAILURE;
    }

    Tuple t1 = {1, 2, 3, 0, 0, 0};
    Tuple t2 = {0, 0, 0, 1, 1, 1};
    Tuple t3 = {4, 5, 6, 0, 0, 0};
    Tuple t4 = {0, 0, 0, 1, 1, 1};
    Tuple t5 = {7, 8, 9, 0, 0, 0};

    if (tuple_list_append(&list, t1) != 0 ||
        tuple_list_append(&list, t2) != 0 ||
        tuple_list_append(&list, t3) != 0 ||
        tuple_list_append(&list, t4) != 0 ||
        tuple_list_append(&list, t5) != 0) {
        tuple_list_free(&list);
        return EXIT_FAILURE;
    }

    if (remove_all_none_tuples(&list) != 0) {
        tuple_list_free(&list);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < list.count; i++) {
        printf("Tuple %zu: %d %d %d\n", i, list.items[i].val1, list.items[i].val2, list.items[i].val3);
    }

    tuple_list_free(&list);
    return EXIT_SUCCESS;
}