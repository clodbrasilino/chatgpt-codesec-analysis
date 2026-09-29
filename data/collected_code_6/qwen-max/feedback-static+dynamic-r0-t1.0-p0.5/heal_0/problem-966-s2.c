#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t length;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
} TupleList;

void free_tuple(Tuple *tuple) {
    if (tuple->data) {
        free(tuple->data);
    }
    free(tuple);
}

Tuple* create_tuple(size_t length) {
    Tuple *new_tuple = (Tuple *)malloc(sizeof(Tuple));
    new_tuple->data = (int *)malloc(length * sizeof(int));
    new_tuple->length = length;
    return new_tuple;
}

TupleList* create_tuple_list(size_t count) {
    TupleList *list = (TupleList *)malloc(sizeof(TupleList));
    list->tuples = (Tuple *)malloc(count * sizeof(Tuple));
    list->count = count;
    return list;
}

void remove_empty_tuples(TupleList *list) {
    for (size_t i = 0; i < list->count; ) {
        if (list->tuples[i].length == 0) {
            free_tuple(&list->tuples[i]);
            for (size_t j = i; j < list->count - 1; ++j) {
                list->tuples[j] = list->tuples[j + 1];
            }
            --list->count;
        } else {
            ++i;
        }
    }
}

void free_tuple_list(TupleList *list) {
    for (size_t i = 0; i < list->count; ++i) {
        free_tuple(&list->tuples[i]);
    }
    free(list->tuples);
    free(list);
}

int main() {
    TupleList *list = create_tuple_list(5);

    list->tuples[0] = *create_tuple(2);
    list->tuples[1] = *create_tuple(0);
    list->tuples[2] = *create_tuple(3);
    list->tuples[3] = *create_tuple(0);
    list->tuples[4] = *create_tuple(1);

    remove_empty_tuples(list);

    for (size_t i = 0; i < list->count; ++i) {
        printf("Tuple %zu: Length = %zu\n", i, list->tuples[i].length);
    }

    free_tuple_list(list);
    return 0;
}