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
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'newList' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    newList->tuples = (Tuple*) malloc(sizeof(Tuple) * list->size);
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
            /* Possible weaknesses found:
             *  dereference of possibly-NULL '*newList.tuples + (long unsigned int)*newList.size * 16' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            newList->tuples[newList->size] = list->tuples[i];
            newList->size++;
        }
    }
    return newList;
}

int main() {
    int i, j;
    TupleList list;
    list.size = 3;
    list.tuples = (Tuple*) malloc(sizeof(Tuple) * list.size);

    for(i = 0; i < list.size; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'list.tuples' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        list.tuples[i].size = 3;
        list.tuples[i].data = (int*) malloc(sizeof(int) * list.tuples[i].size);
        for(j = 0; j < list.tuples[i].size; j++) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL '*_21 + _23.data + (long unsigned int)j * 4' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            list.tuples[i].data[j] = i;
        }
    }

    TupleList *newList = removeEmptyTuples(&list);

    for(i = 0; i < newList->size; i++) {
        for(j = 0; j < newList->tuples[i].size; j++) {
            printf("%d ", newList->tuples[i].data[j]);
        }
        printf("\n");
    }

    return 0;
}