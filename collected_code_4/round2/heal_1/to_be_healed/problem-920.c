#include <stdio.h>
#include <stdlib.h>

typedef struct Tuple {
    int* values;
    size_t size;
} Tuple;

typedef struct TupleList {
    Tuple* tuples;
    size_t size;
} TupleList;

TupleList* removeNoneValuesTuples(TupleList* list) {
    TupleList* newList = malloc(sizeof(TupleList));
    int nonNullTuples = 0;
    for(int i=0; i < list->size; i++) {
        int isAllNull = 1;
        for(int j=0; j < list->tuples[i].size; j++) {
            if(list->tuples[i].values[j] != 0) {
                isAllNull = 0;
                break;
            }
        }
        if(!isAllNull) {
            nonNullTuples++;
        }
    }

    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'newList' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    newList->tuples = malloc(sizeof(Tuple) * nonNullTuples);
    newList->size = nonNullTuples;

    int m = 0;
    for(int i=0; i < list->size; i++) {
        int isAllNull = 1;
        for(int j=0; j < list->tuples[i].size; j++) {
            if(list->tuples[i].values[j] != 0) {
                isAllNull = 0;
                break;
            }
        }
        if(!isAllNull) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL '*newList.tuples + (long unsigned int)m * 16' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            newList->tuples[m] = list->tuples[i];
            m++;
        }
    }

    free(list->tuples);
    free(list);
    return newList;
}

int main() {
    TupleList* list = malloc(sizeof(TupleList));
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'list' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    list->size = 3;

    list->tuples = malloc(sizeof(Tuple) * list->size);

    for(int i = 0; i < list->size; i++) {
       /* Possible weaknesses found:
        *  dereference of possibly-NULL '*list.tuples + (long unsigned int)i * 16' [CWE-690] [-Wanalyzer-possible-null-dereference]
        */
       list->tuples[i].values = malloc(sizeof(int) * 3);
       list->tuples[i].size = 3;
       for(int j = 0; j < 3; j++) {
           /* Possible weaknesses found:
            *  dereference of possibly-NULL '*_13 + _15.values + (long unsigned int)j * 4' [CWE-690] [-Wanalyzer-possible-null-dereference]
            */
           list->tuples[i].values[j] = (i == j) ? 0 : i+j;
       }
    }

    TupleList* newList = removeNoneValuesTuples(list);

    for(int i=0; i<newList->size; i++) {
        for(int j=0; j< newList->tuples[i].size; j++) {
            printf("%d ", newList->tuples[i].values[j]);
        }
	printf("\n");
    }

    for(int i=0; i<newList->size; i++) {
        free(newList->tuples[i].values);
    }

    free(newList->tuples);
    free(newList);

    return 0;
}