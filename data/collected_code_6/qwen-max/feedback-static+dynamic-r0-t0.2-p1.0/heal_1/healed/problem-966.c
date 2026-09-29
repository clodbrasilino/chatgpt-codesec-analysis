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

Tuple* create_tuple(size_t length) {
    Tuple *new_tuple = (Tuple *)malloc(sizeof(Tuple));
    if (!new_tuple) return NULL;
    new_tuple->data = (int *)malloc(length * sizeof(int));
    if (!new_tuple->data) {
        free(new_tuple);
        return NULL;
    }
    new_tuple->length = length;
    return new_tuple;
}

TupleList* create_tuple_list() {
    TupleList *list = (TupleList *)malloc(sizeof(TupleList));
    if (!list) return NULL;
    list->tuples = NULL;
    list->count = 0;
    return list;
}

void add_tuple(TupleList *list, Tuple *tuple) {
    list->tuples = realloc(list->tuples, (list->count + 1) * sizeof(Tuple *));
    if (list->tuples) {
        list->tuples[list->count] = tuple;
        list->count++;
    }
}

void remove_empty_tuples(TupleList *list) {
    for (size_t i = 0; i < list->count; ) {
        if (list->tuples[i]->length == 0) {
            free_tuple(list->tuples[i]);
            for (size_t j = i; j < list->count - 1; j++) {
                list->tuples[j] = list->tuples[j + 1];
            }
            list->count--;
        } else {
            i++;
        }
    }
}

void free_tuple_list(TupleList *list) {
    for (size_t i = 0; i < list->count; i++) {
        free_tuple(list->tuples[i]);
    }
    free(list->tuples);
    free(list);
}

int main() {
    TupleList *list = create_tuple_list();
    if (!list) return 1;

    Tuple *t1 = create_tuple(2);
    t1->data[0] = 1;
    t1->data[1] = 2;
    add_tuple(list, t1);

    Tuple *t2 = create_tuple(0);
    add_tuple(list, t2);

    Tuple *t3 = create_tuple(1);
    t3->data[0] = 3;
    add_tuple(list, t3);

    remove_empty_tuples(list);

    for (size_t i = 0; i < list->count; i++) {
        for (size_t j = 0; j < list->tuples[i]->length; j++) {
            printf("%d ", list->tuples[i]->data[j]);
        }
        printf("\n");
    }

    free_tuple_list(list);
    return 0;
}