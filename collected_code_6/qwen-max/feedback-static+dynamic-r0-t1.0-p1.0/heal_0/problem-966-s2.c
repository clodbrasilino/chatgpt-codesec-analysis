#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t length;
} TupleList;

void removeEmptyTuple(TupleList *list) {
    int j = 0;
    for (int i = 0; i < list->length; i++) {
        if (list->tuples[i].a != 0 || list->tuples[i].b != 0) {
            if (i != j) {
                list->tuples[j] = list->tuples[i];
            }
            j++;
        }
    }
    list->length = j;
}

int main() {
    TupleList list;
    list.length = 4;
    list.tuples = malloc(list.length * sizeof(Tuple));
    list.tuples[0].a = 1;
    list.tuples[0].b = 2;
    list.tuples[1].a = 0;
    list.tuples[1].b = 0;
    list.tuples[2].a = 3;
    list.tuples[2].b = 4;
    list.tuples[3].a = 0;
    list.tuples[3].b = 0;

    removeEmptyTuple(&list);

    for (size_t i = 0; i < list.length; i++) {
        printf("(%d, %d)\n", list.tuples[i].a, list.tuples[i].b);
    }

    free(list.tuples);
    return 0;
}