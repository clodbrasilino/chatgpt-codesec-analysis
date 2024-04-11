#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} Tuple;

typedef struct {
    Tuple *tuples;
    int size;
} TupleList;

TupleList* removeEmptyTuples(TupleList *list) {
    int i, j, isEmpty;
    TupleList *newList = (TupleList*) malloc(sizeof(TupleList));

    if (newList) {
        newList->tuples = (Tuple*) malloc(sizeof(Tuple) * list->size);
        if (newList->tuples) {
            newList->size = 0;

            for(i = 0; i < list->size; i++) {
                isEmpty = 1;
                for(j = 0; j < list->tuples[i].size; j++) {
                    if(list->tuples[i].data[j] != 0) {
                        isEmpty = 0;
                        break;
                    }
                }
                if(!isEmpty) {
                    newList->tuples[newList->size] = list->tuples[i];
                    newList->size++;
                }
            }
        }
    }

    return newList;
}

int main() {
    int i, j;
    TupleList list;
    list.size = 3;
    list.tuples = (Tuple*) malloc(sizeof(Tuple) * list.size);

    if (list.tuples) {
        for(i = 0; i < list.size; i++) {
            list.tuples[i].size = 3;
            list.tuples[i].data = (int*) malloc(sizeof(int) * list.tuples[i].size);
            if (list.tuples[i].data) {
                for(j = 0; j < list.tuples[i].size; j++) {
                    list.tuples[i].data[j] = i;
                }
            }
        }
    }

    TupleList *newList = removeEmptyTuples(&list);

    if (newList && newList->tuples) {
        for(i = 0; i < newList->size; i++) {
            for(j = 0; j < newList->tuples[i].size; j++) {
                printf("%d ", newList->tuples[i].data[j]);
            }
            printf("\n");
        }
    }

    return 0;
}