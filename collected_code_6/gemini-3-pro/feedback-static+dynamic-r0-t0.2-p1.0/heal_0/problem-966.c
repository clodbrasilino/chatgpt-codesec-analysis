#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t size;
} TupleList;

void remove_empty_tuples(TupleList *list) {
    if (list == NULL || list->tuples == NULL) {
        return;
    }

    size_t write_index = 0;

    for (size_t i = 0; i < list->size; i++) {
        if (list->tuples[i].size > 0) {
            if (write_index != i) {
                list->tuples[write_index] = list->tuples[i];
            }
            write_index++;
        } else {
            free(list->tuples[i].elements);
            list->tuples[i].elements = NULL;
        }
    }

    list->size = write_index;
}

int main(void) {
    TupleList list;
    list.size = 3;
    list.tuples = malloc(list.size * sizeof(Tuple));
    if (list.tuples == NULL) {
        return 1;
    }

    list.tuples[0].size = 2;
    list.tuples[0].elements = malloc(2 * sizeof(int));
    if (list.tuples[0].elements != NULL) {
        list.tuples[0].elements[0] = 1;
        list.tuples[0].elements[1] = 2;
    }

    list.tuples[1].size = 0;
    list.tuples[1].elements = NULL;

    list.tuples[2].size = 1;
    list.tuples[2].elements = malloc(1 * sizeof(int));
    if (list.tuples[2].elements != NULL) {
        list.tuples[2].elements[0] = 3;
    }

    remove_empty_tuples(&list);

    for (size_t i = 0; i < list.size; i++) {
        printf("Tuple %zu size: %zu\n", i, list.tuples[i].size);
        free(list.tuples[i].elements);
    }

    free(list.tuples);

    return 0;
}