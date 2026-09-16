#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int **elements;
    size_t size;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t size;
    size_t capacity;
} TupleList;

int is_all_none(const Tuple *t) {
    if (t == NULL || t->elements == NULL) {
        return 1;
    }
    for (size_t i = 0; i < t->size; i++) {
        if (t->elements[i] != NULL) {
            return 0;
        }
    }
    return 1;
}

void remove_all_none_tuples(TupleList *list) {
    if (list == NULL) {
        return;
    }
    if (list->tuples == NULL) {
        list->size = 0;
        return;
    }
    size_t write_idx = 0;
    for (size_t i = 0; i < list->size; i++) {
        if (is_all_none(&list->tuples[i])) {
            free(list->tuples[i].elements);
            list->tuples[i].elements = NULL;
            list->tuples[i].size = 0;
        } else {
            if (write_idx != i) {
                list->tuples[write_idx] = list->tuples[i];
                list->tuples[i].elements = NULL;
                list->tuples[i].size = 0;
            }
            write_idx++;
        }
    }
    list->size = write_idx;
}

int main(void) {
    int val1 = 1;
    TupleList list;
    list.capacity = 4;
    list.size = 0;
    list.tuples = malloc(list.capacity * sizeof(Tuple));
    if (list.tuples == NULL) {
        return 1;
    }

    for (size_t i = 0; i < list.capacity; i++) {
        list.tuples[i].elements = NULL;
        list.tuples[i].size = 0;
    }

    list.tuples[0].size = 2;
    list.tuples[0].elements = malloc(2 * sizeof(int *));
    if (list.tuples[0].elements == NULL) goto cleanup;
    list.tuples[0].elements[0] = NULL;
    list.tuples[0].elements[1] = NULL;
    list.size = 1;

    list.tuples[1].size = 2;
    list.tuples[1].elements = malloc(2 * sizeof(int *));
    if (list.tuples[1].elements == NULL) goto cleanup;
    list.tuples[1].elements[0] = &val1;
    list.tuples[1].elements[1] = NULL;
    list.size = 2;

    list.tuples[2].size = 3;
    list.tuples[2].elements = malloc(3 * sizeof(int *));
    if (list.tuples[2].elements == NULL) goto cleanup;
    list.tuples[2].elements[0] = NULL;
    list.tuples[2].elements[1] = NULL;
    list.tuples[2].elements[2] = NULL;
    list.size = 3;

    remove_all_none_tuples(&list);

    for (size_t i = 0; i < list.size; i++) {
        printf("Tuple %zu: ", i);
        for (size_t j = 0; j < list.tuples[i].size; j++) {
            if (list.tuples[i].elements[j] != NULL) {
                printf("%d ", *list.tuples[i].elements[j]);
            } else {
                printf("None ");
            }
        }
        printf("\n");
    }

cleanup:
    for (size_t i = 0; i < list.capacity; i++) {
        free(list.tuples[i].elements);
    }
    free(list.tuples);

    return 0;
}