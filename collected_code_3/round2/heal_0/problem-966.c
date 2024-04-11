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
    for (i = 0; i < list->size; i++) {
        if (list->tuples[i]->size == 0) {
            free(list->tuples[i]);
            for (j = i; j < list->size - 1; j++) {
                list->tuples[j] = list->tuples[j + 1];
            }
            list->size--;
            i--;
        }
    }
}

int main() {
    TupleList *list = malloc(sizeof(TupleList));
    list->size = 3;
    list->tuples = malloc(sizeof(Tuple*) * list->size);

    Tuple *tuple1 = malloc(sizeof(Tuple));
    tuple1->size = 0;
    tuple1->elements = NULL;

    Tuple *tuple2 = malloc(sizeof(Tuple));
    tuple2->size = 2;
    tuple2->elements = malloc(sizeof(int) * tuple2->size);
    tuple2->elements[0] = 1;
    tuple2->elements[1] = 2;

    Tuple *tuple3 = malloc(sizeof(Tuple));
    tuple3->size = 0;
    tuple3->elements = NULL;

    list->tuples[0] = tuple1;
    list->tuples[1] = tuple2;
    list->tuples[2] = tuple3;

    removeEmptyTuples(list);

    printf("Size of list after removing empty tuples: %d\n", list->size);

    free(tuple2->elements);
    free(list->tuples);
    free(list);

    return 0;
}