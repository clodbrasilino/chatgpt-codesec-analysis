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

Tuple *create_tuple(size_t length) {
    Tuple *tuple = (Tuple *)malloc(sizeof(Tuple));
    if (tuple == NULL) return NULL;
    tuple->data = (int *)calloc(length, sizeof(int));
    if (tuple->data == NULL) {
        free(tuple);
        return NULL;
    }
    tuple->length = length;
    return tuple;
}

void free_tuple(Tuple *tuple) {
    if (tuple != NULL) {
        free(tuple->data);
        free(tuple);
    }
}

TupleList *create_tuple_list(size_t count) {
    TupleList *list = (TupleList *)malloc(sizeof(TupleList));
    if (list == NULL) return NULL;
    list->tuples = (Tuple *)malloc(count * sizeof(Tuple));
    if (list->tuples == NULL) {
        free(list);
        return NULL;
    }
    list->count = count;
    for (size_t i = 0; i < count; ++i) {
        list->tuples[i] = (Tuple){NULL, 0};
    }
    return list;
}

void free_tuple_list(TupleList *list) {
    if (list != NULL) {
        for (size_t i = 0; i < list->count; ++i) {
            free_tuple(&list->tuples[i]);
        }
        free(list->tuples);
        free(list);
    }
}

TupleList *remove_empty_tuples(TupleList *list) {
    if (list == NULL) return NULL;
    TupleList *new_list = create_tuple_list(list->count);
    if (new_list == NULL) return NULL;
    size_t new_count = 0;
    for (size_t i = 0; i < list->count; ++i) {
        if (list->tuples[i].length > 0) {
            new_list->tuples[new_count++] = list->tuples[i];
        }
    }
    new_list->count = new_count;
    return new_list;
}

int main() {
    TupleList *list = create_tuple_list(3);
    if (list == NULL) return 1;

    list->tuples[0] = *create_tuple(2);
    list->tuples[1] = *create_tuple(0);
    list->tuples[2] = *create_tuple(3);

    TupleList *new_list = remove_empty_tuples(list);
    if (new_list == NULL) {
        free_tuple_list(list);
        return 1;
    }

    for (size_t i = 0; i < new_list->count; ++i) {
        printf("Tuple %zu: Length = %zu\n", i, new_list->tuples[i].length);
    }

    free_tuple_list(list);
    free_tuple_list(new_list);
    return 0;
}