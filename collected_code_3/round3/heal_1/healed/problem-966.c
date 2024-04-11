#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int size;
    int *elements;
} Tuple;

typedef struct {
    int size;
    Tuple **tuples;
} TupleList;

void removeEmptyTuples(TupleList *list) {
    int i, j;
    if (list) {
        for (i = 0; i < list->size; i++) {
            if (list->tuples[i] && list->tuples[i]->size == 0) {
                free(list->tuples[i]);
                for (j = i; j < list->size - 1; j++) {
                    list->tuples[j] = list->tuples[j + 1];
                }
                list->size--;
                i--;
            }
        }
    }
}

int main() {
    TupleList *list = malloc(sizeof(TupleList));
    if (!list)
        return -1;

    list->size = 3;
    list->tuples = malloc(sizeof(Tuple*) * list->size);

    if (!list->tuples) {
        free(list);
        return -1;
    }

    list->tuples[0] = malloc(sizeof(Tuple));
    if (list->tuples[0]) {
        list->tuples[0]->size = 0;
    }

    list->tuples[1] = malloc(sizeof(Tuple));
    if (list->tuples[1]) {
        list->tuples[1]->size = 2;
        list->tuples[1]->elements = malloc(sizeof(int) * 2);
        if (list->tuples[1]->elements) {
            list->tuples[1]->elements[0] = 1;
            list->tuples[1]->elements[1] = 2;
        }
    }

    list->tuples[2] = malloc(sizeof(Tuple));
    if (list->tuples[2]) {
        list->tuples[2]->size = 0;
    }

    removeEmptyTuples(list);

    printf("Size of list after removing empty tuples: %d\n", list->size);

    return 0;
}