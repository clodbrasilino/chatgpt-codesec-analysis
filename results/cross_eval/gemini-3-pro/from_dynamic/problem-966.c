#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t size;
    size_t capacity;
} TupleList;

void init_tuple_list(TupleList *list, size_t capacity) {
    if (list != NULL) {
        list->tuples = (Tuple *)malloc(capacity * sizeof(Tuple));
        if (list->tuples != NULL) {
            list->size = 0;
            list->capacity = capacity;
        } else {
            list->size = 0;
            list->capacity = 0;
        }
    }
}

void add_tuple(TupleList *list, int *elements, size_t size) {
    if (list != NULL && list->tuples != NULL && list->size < list->capacity) {
        list->tuples[list->size].elements = elements;
        list->tuples[list->size].size = size;
        list->size++;
    }
}

void remove_empty_tuples(TupleList *list) {
    if (list == NULL || list->tuples == NULL) {
        return;
    }

    size_t new_size = 0;
    for (size_t i = 0; i < list->size; i++) {
        if (list->tuples[i].size > 0) {
            list->tuples[new_size] = list->tuples[i];
            new_size++;
        } else {
            if (list->tuples[i].elements != NULL) {
                free(list->tuples[i].elements);
            }
        }
    }
    list->size = new_size;
}

void free_tuple_list(TupleList *list) {
    if (list != NULL && list->tuples != NULL) {
        for (size_t i = 0; i < list->size; i++) {
            if (list->tuples[i].elements != NULL) {
                free(list->tuples[i].elements);
            }
        }
        free(list->tuples);
        list->tuples = NULL;
        list->size = 0;
        list->capacity = 0;
    }
}

int main(void) {
    TupleList list;
    init_tuple_list(&list, 5);

    if (list.tuples == NULL) {
        return 1;
    }

    int *t1_elems = (int *)malloc(2 * sizeof(int));
    if (t1_elems != NULL) {
        t1_elems[0] = 1;
        t1_elems[1] = 2;
        add_tuple(&list, t1_elems, 2);
    }

    int *t2_elems = (int *)malloc(0);
    add_tuple(&list, t2_elems, 0);

    int *t3_elems = (int *)malloc(3 * sizeof(int));
    if (t3_elems != NULL) {
        t3_elems[0] = 3;
        t3_elems[1] = 4;
        t3_elems[2] = 5;
        add_tuple(&list, t3_elems, 3);
    }

    remove_empty_tuples(&list);

    for (size_t i = 0; i < list.size; i++) {
        printf("Tuple %zu size: %zu\n", i, list.tuples[i].size);
    }

    free_tuple_list(&list);

    return 0;
}