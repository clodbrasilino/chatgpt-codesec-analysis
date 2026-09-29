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
    if (!list) return NULL;
    TupleList* newList = malloc(sizeof(TupleList));
    if (!newList) return NULL;

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

    newList->tuples = malloc(sizeof(Tuple) * nonNullTuples);
    if (!newList->tuples) {
        free(newList);
        return NULL;
    }
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
            newList->tuples[m] = list->tuples[i];
            m++;
        }
    }
    
    return newList;
}

int main() {
    TupleList* list = malloc(sizeof(TupleList));
    if (!list) return 1;
    list->size = 3;

    list->tuples = malloc(sizeof(Tuple) * list->size);
    if (!list->tuples) {
        free(list);
        return 1;
    }

    for(int i = 0; i < list->size; i++) {
       list->tuples[i].values = malloc(sizeof(int) * 3);
       if (!list->tuples[i].values) {
           for (int j = 0; j < i; j++)
               free(list->tuples[j].values);
           free(list->tuples);
           free(list);
           return 1;
       }
       list->tuples[i].size = 3;
       for(int j = 0; j < 3; j++) {
           list->tuples[i].values[j] = (i == j) ? 0 : i+j;
       }
    }

    TupleList* newList = removeNoneValuesTuples(list);
    if (!newList) {
        for(int i=0; i<list->size; i++) {
            free(list->tuples[i].values);
        }
        free(list->tuples);
        free(list);
        return 1;
    }
    
    for(int i=0; i<newList->size; i++) {
        for(int j=0; j<newList->tuples[i].size; j++) {
            printf("%d ", newList->tuples[i].values[j]);
        }
	printf("\n");
    }

    for(int i=0; i<newList->size; i++) {
        free(newList->tuples[i].values);
    }

    free(newList->tuples);
    free(newList);

    for(int i=0; i<list->size; i++) {
        free(list->tuples[i].values);
    }
    free(list->tuples);
    free(list);

    return 0;
}