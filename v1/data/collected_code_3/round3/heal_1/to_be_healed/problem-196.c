#include <stdio.h>
#include <stdlib.h>

typedef struct Tuple {
    int *data;
    int length;
} Tuple;

Tuple* removeTuples(Tuple* tuples, int tupleCount, int k, int* newCount) {
    int count = 0;
    for(int i = 0; i < tupleCount; i++) {
        if(tuples[i].length != k) {
            count++;
        }
    }

    Tuple* newTuples = (Tuple*)malloc(sizeof(Tuple) * count);
    int j = 0;
    for(int i = 0; i < tupleCount; i++) {
        if(tuples[i].length != k) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'newTuples' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            newTuples[j++] = tuples[i];
        }
    }

    *newCount = count;
    return newTuples;
}

int main() {
    int tupleCount = 5;
    Tuple* tuples = (Tuple*)malloc(sizeof(Tuple) * tupleCount);

    for(int i = 0; i < tupleCount; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'tuples' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        tuples[i].length = i + 1;
        tuples[i].data = (int*)malloc(sizeof(int) * tuples[i].length);
        for(int j = 0; j < tuples[i].length; j++) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL '*tuples_65 + _18.data + (long unsigned int)j * 4' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            tuples[i].data[j] = j;
        }
    }

    int newCount;
    Tuple* newTuples = removeTuples(tuples, tupleCount, 3, &newCount);

    for(int i = 0; i < newCount; i++) {
        for(int j = 0; j < newTuples[i].length; j++) {
            printf("%d ", newTuples[i].data[j]);
        }
        printf("\n");
    }

    for(int i = 0; i < tupleCount; i++) {
        free(tuples[i].data);
    }
    free(tuples);

    for(int i = 0; i < newCount; i++) {
        free(newTuples[i].data);
    }
    free(newTuples);

    return 0;
}