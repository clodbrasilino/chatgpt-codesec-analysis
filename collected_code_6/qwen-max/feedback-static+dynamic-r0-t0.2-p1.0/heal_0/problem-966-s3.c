#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t length;
} Tuple;

typedef struct {
    Tuple **tuples;
    size_t count;
} TupleList;

void free_tuple(Tuple *tuple) {
    if (tuple->data) {
        free(tuple->data);
    }
    free(tuple);
}

Tuple *create_tuple(size_t length) {
    Tuple *tuple = (Tuple *)malloc(sizeof(Tuple));
    if (!tuple) return NULL;
    tuple->data = (int *)malloc(length * sizeof(int));
    if (!tuple->data) {
        free(tuple);
        return NULL;
    }
    tuple->length = length;
    return tuple;
}

TupleList *create_tuple_list() {
    TupleList *list = (TupleList *)malloc(sizeof(TupleList));
    if (!list) return NULL;
    list->tuples = NULL;
    list->count = 0;
    return list;
}

int add_tuple(TupleList *list, Tuple *tuple) {
    list->tuples = (Tuple **)realloc(list->tuples, (list->count + 1) * sizeof(Tuple *));
    if (!list->tuples) return -1;
    list->tuples[list->count++] = tuple;
    return 0;
}

int remove_empty_tuples(TupleList *list) {
    for (size_t i = 0; i < list->count; ) {
        if (list->tuples[i]->length == 0) {
            free_tuple(list->tuples[i]);
            for (size_t j = i; j < list->count - 1; ++j) {
                list->tuples[j] = list->tuples[j + 1];
            }
            --list->count;
            list->tuples = (Tuple **)realloc(list->tuples, list->count * sizeof(Tuple *));
            if (!list->tuples) return -1;
        } else {
            ++i;
        }
    }
    return 0;
}

void print_tuple_list(TupleList *list) {
    for (size_t i = 0; i < list->count; ++i) {
        printf("Tuple %zu: [", i);
        for (size_t j = 0; j < list->tuples[i]->length; ++j) {
            printf("%d", list->tuples[i]->data[j]);
            if (j < list->tuples[i]->length - 1) printf(", ");
        }
        printf("]\n");
    }
}

void free_tuple_list(TupleList *list) {
    for (size_t i = 0; i < list->count; ++i) {
        free_tuple(list->tuples[i]);
    }
    free(list->tuples);
    free(list);
}

int main() {
    TupleList *list = create_tuple_list();
    if (!list) return -1;

    Tuple *t1 = create_tuple(2);
    t1->data[0] = 1;
    t1->data[1] = 2;
    add_tuple(list, t1);

    Tuple *t2 = create_tuple(0);
    add_tuple(list, t2);

    Tuple *t3 = create_tuple(3);
    t3->data[0] = 3;
    t3->data[1] = 4;
    t3->data[2] = 5;
    add_tuple(list, t3);

    printf("Before removal:\n");
    print_tuple_list(list);

    remove_empty_tuples(list);

    printf("After removal:\n");
    print_tuple_list(list);

    free_tuple_list(list);
    return 0;
}