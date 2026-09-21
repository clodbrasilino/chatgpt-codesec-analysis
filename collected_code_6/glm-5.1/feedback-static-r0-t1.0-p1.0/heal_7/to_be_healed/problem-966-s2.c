#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

typedef struct {
    Tuple *items;
    size_t count;
    size_t capacity;
} TupleList;

TupleList create_tuple_list(size_t capacity) {
    TupleList list;
    list.items = (Tuple *)malloc(capacity * sizeof(Tuple));
    if (list.items == NULL) {
        exit(EXIT_FAILURE);
    }
    list.count = 0;
    list.capacity = capacity;
    return list;
}

void add_tuple(TupleList *list, int *elements, size_t size) {
    if (list->count >= list->capacity) {
        if (list->capacity == 0) {
            list->capacity = 1;
        }
        size_t new_capacity = list->capacity * 2;
        Tuple *new_items = (Tuple *)realloc(list->items, new_capacity * sizeof(Tuple));
        if (new_items == NULL) {
            exit(EXIT_FAILURE);
        }
        list->items = new_items;
        list->capacity = new_capacity;
    }
    list->items[list->count].size = size;
    list->items[list->count].elements = NULL;
    if (size > 0) {
        list->items[list->count].elements = (int *)malloc(size * sizeof(int));
        if (list->items[list->count].elements == NULL) {
            exit(EXIT_FAILURE);
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(list->items[list->count].elements, elements, size * sizeof(int));
    }
    list->count++;
}

void remove_empty_tuples(TupleList *list) {
    size_t write_index = 0;
    for (size_t read_index = 0; read_index < list->count; read_index++) {
        if (list->items[read_index].size == 0) {
            free(list->items[read_index].elements);
        } else {
            if (write_index != read_index) {
                list->items[write_index] = list->items[read_index];
                list->items[read_index].elements = NULL;
                list->items[read_index].size = 0;
            }
            write_index++;
        }
    }
    list->count = write_index;
}

void free_tuple_list(TupleList *list) {
    for (size_t i = 0; i < list->count; i++) {
        free(list->items[i].elements);
    }
    free(list->items);
    list->items = NULL;
    list->count = 0;
    list->capacity = 0;
}

int main() {
    TupleList list = create_tuple_list(4);

    int a[] = {1, 2};
    int b[] = {0};
    int c[] = {3, 4, 5};
    int d[] = {0};

    add_tuple(&list, a, sizeof(a) / sizeof(a[0]));
    add_tuple(&list, b, 0);
    add_tuple(&list, c, sizeof(c) / sizeof(c[0]));
    add_tuple(&list, d, 0);

    remove_empty_tuples(&list);

    for (size_t i = 0; i < list.count; i++) {
        printf("(");
        for (size_t j = 0; j < list.items[i].size; j++) {
            if (j > 0) {
                printf(", ");
            }
            /* Possible weaknesses found:
             *  invalid type argument of '->' (have 'TupleList')
             *  member reference type 'TupleList' is not a pointer; did you mean to use '.'?
             */
            printf("%d", list->items[i].elements[j]);
        }
        printf(")\n");
    }

    free_tuple_list(&list);

    return 0;
}