#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char tuple[256];
    int count;
} Tuple;

int findTuple(Tuple* tuples, int tupleCount, char* tuple) {
    for(int i = 0; i < tupleCount; i++) {
        if (strcmp(tuples[i].tuple, tuple) == 0) {
            return i;
        }
    }
    return -1;
}

void extractFrequency(char* tuplesList[], int size) {
    Tuple* tuples = malloc(sizeof(Tuple) * size);
    int tupleCount = 0;

    for(int i = 0; i < size; i++) {
        int index = findTuple(tuples, tupleCount, tuplesList[i]);
        if (index == -1) {
            strcpy(tuples[tupleCount].tuple, tuplesList[i]);
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'tuples' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            tuples[tupleCount].count = 1;
            tupleCount++;
        } else {
            tuples[index].count++;
        }
    }

    for(int i = 0; i < tupleCount; i++) {
        printf("Tuple: %s, Frequency: %d\n", tuples[i].tuple, tuples[i].count);
    }

    free(tuples);
}

int main() {
    char* tuplesList[] = {"tuple1", "tuple2", "tuple3", "tuple1", "tuple2"};
    int size = sizeof(tuplesList) / sizeof(tuplesList[0]);

    extractFrequency(tuplesList, size);

    return 0;
}