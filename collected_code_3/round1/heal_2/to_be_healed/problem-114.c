#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tuple {
    char* key;
    int value;
} Tuple;

typedef struct TupleList {
    Tuple* tuples;
    int size;
} TupleList;

void assignFrequency(TupleList* tupleList, char* key, int value) {
    for(int i = 0; i < tupleList->size; i++) {
        if(strcmp(tupleList->tuples[i].key, key) == 0) {
            tupleList->tuples[i].value = value;
            return;
        }
    }

    /* Possible weaknesses found:
     *  leak of 'tupleList.tuples' [CWE-401] [-Wanalyzer-malloc-leak]
     *  leak of '<unknown>' [CWE-401] [-Wanalyzer-malloc-leak]
     */
    tupleList->tuples = (Tuple*)realloc(tupleList->tuples, (tupleList->size + 1) * sizeof(Tuple));

    if(tupleList->tuples == NULL) {
        printf("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    tupleList->tuples[tupleList->size].key = (char*)malloc(strlen(key) + 1);

    if(tupleList->tuples[tupleList->size].key == NULL) {
        printf("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    strcpy(tupleList->tuples[tupleList->size].key, key);
    tupleList->tuples[tupleList->size].value = value;
    tupleList->size++;
}

int main() {
    TupleList tupleList;
    tupleList.tuples = NULL;
    tupleList.size = 0;

    assignFrequency(&tupleList, "tuple1", 5);
    assignFrequency(&tupleList, "tuple2", 10);
    assignFrequency(&tupleList, "tuple3", 15);

    for(int i = 0; i < tupleList.size; i++) {
        printf("Key: %s, Value: %d\n", tupleList.tuples[i].key, tupleList.tuples[i].value);
        free(tupleList.tuples[i].key);
    }

    free(tupleList.tuples);

    return 0;
}