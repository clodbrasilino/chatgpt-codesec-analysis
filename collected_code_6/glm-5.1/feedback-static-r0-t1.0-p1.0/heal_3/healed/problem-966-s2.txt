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
        list->capacity *= 2;
        Tuple *new_items = (Tuple *)realloc(list->items, list->capacity * sizeof(Tuple));
        if (new_items == NULL) {
            exit(EXIT_FAILURE);
        }
        list->items = new_items;
    }
    list->items[list->count].size = size;
    list->items[list->count].elements = NULL;
    if (size > 0) {
        list->items[list->count].elements = (int *)malloc(size * sizeof(int));
        if (list->items[list->count].elements == NULL) {
            exit(EXIT_FAILURE);
        }
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
    int b[] = {};
    int c[] = {3, 4, 5};
    int d[] = {};

    add_tuple(&list, a, sizeof(a) / sizeof(a[0]));
    add_tuple(&list, b, sizeof(b) / sizeof(b[0]));
    add_tuple(&list, c, sizeof(c) / sizeof(c[0]));
    add_tuple(&list, d, sizeof(d) / sizeof(d[0]));

    remove_empty_tuples(&list);

    for (size_t i = 0; i < list.count; i++) {
        printf("(");
        for (size_t j = 0; j < list.items[i].size; j++) {
            if (j > 0) {
                printf(", ");
            }
            printf("%d", list.items[i].elements[j]);
        }
        printf(")\n");
    }

    free_tuple_list(&list);

    return 0;
}