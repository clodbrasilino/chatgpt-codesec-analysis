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

Tuple *create_tuple(size_t length) {
    Tuple *tuple = malloc(sizeof(Tuple));
    if (!tuple) return NULL;
    tuple->data = malloc(length * sizeof(int));
    if (!tuple->data) {
        free(tuple);
        return NULL;
    }
    tuple->length = length;
    return tuple;
}

TupleList *create_tuple_list(size_t count) {
    TupleList *list = malloc(sizeof(TupleList));
    if (!list) return NULL;
    list->tuples = malloc(count * sizeof(Tuple *));
    if (!list->tuples) {
        free(list);
        return NULL;
    }
    list->count = count;
    return list;
}

void free_tuple_list(TupleList *list) {
    for (size_t i = 0; i < list->count; ++i) {
        free_tuple(list->tuples[i]);
    }
    free(list->tuples);
    free(list);
}

int remove_empty_tuples(TupleList *list) {
    if (!list || !list->tuples) return -1;
    size_t new_count = 0;
    for (size_t i = 0; i < list->count; ++i) {
        if (list->tuples[i]->length > 0) {
            list->tuples[new_count++] = list->tuples[i];
        } else {
            free_tuple(list->tuples[i]);
        }
    }
    list->count = new_count;
    return 0;
}

int main() {
    TupleList *list = create_tuple_list(5);
    if (!list) return 1;

    list->tuples[0] = create_tuple(2);
    list->tuples[1] = create_tuple(0);
    list->tuples[2] = create_tuple(3);
    list->tuples[3] = create_tuple(0);
    list->tuples[4] = create_tuple(1);

    if (remove_empty_tuples(list) != 0) {
        free_tuple_list(list);
        return 1;
    }

    for (size_t i = 0; i < list->count; ++i) {
        printf("Tuple %zu: Length = %zu\n", i, list->tuples[i]->length);
    }

    free_tuple_list(list);
    return 0;
}