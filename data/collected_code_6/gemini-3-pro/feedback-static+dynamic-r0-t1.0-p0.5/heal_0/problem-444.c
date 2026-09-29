#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
} TupleList;

int trim_tuples(TupleList *list, size_t k) {
    if (!list || !list->tuples) {
        return -1;
    }

    for (size_t i = 0; i < list->count; ++i) {
        if (list->tuples[i].size > k) {
            size_t new_size = list->tuples[i].size - k;
            int *new_elements = realloc(list->tuples[i].elements, new_size * sizeof(int));
            if (!new_elements && new_size > 0) {
                return -1;
            }
            list->tuples[i].elements = new_elements;
            list->tuples[i].size = new_size;
        } else {
            free(list->tuples[i].elements);
            list->tuples[i].elements = NULL;
            list->tuples[i].size = 0;
        }
    }

    return 0;
}

void free_tuple_list(TupleList *list) {
    if (!list || !list->tuples) {
        return;
    }
    for (size_t i = 0; i < list->count; ++i) {
        free(list->tuples[i].elements);
    }
    free(list->tuples);
    list->tuples = NULL;
    list->count = 0;
}

int main(void) {
    TupleList list;
    list.count = 2;
    list.tuples = malloc(list.count * sizeof(Tuple));
    if (!list.tuples) {
        return 1;
    }

    list.tuples[0].size = 5;
    list.tuples[0].elements = malloc(5 * sizeof(int));
    if (!list.tuples[0].elements) {
        free(list.tuples);
        return 1;
    }
    for (int i = 0; i < 5; ++i) list.tuples[0].elements[i] = i;

    list.tuples[1].size = 3;
    list.tuples[1].elements = malloc(3 * sizeof(int));
    if (!list.tuples[1].elements) {
        free(list.tuples[0].elements);
        free(list.tuples);
        return 1;
    }
    for (int i = 0; i < 3; ++i) list.tuples[1].elements[i] = i;

    if (trim_tuples(&list, 2) != 0) {
        free_tuple_list(&list);
        return 1;
    }

    for (size_t i = 0; i < list.count; ++i) {
        for (size_t j = 0; j < list.tuples[i].size; ++j) {
            printf("%d ", list.tuples[i].elements[j]);
        }
        printf("\n");
    }

    free_tuple_list(&list);
    return 0;
}