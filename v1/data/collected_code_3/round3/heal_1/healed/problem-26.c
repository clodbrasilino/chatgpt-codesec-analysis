#include <stdio.h>
#include <stdlib.h>

typedef struct Tuple {
    int *elements;
    int size;
} Tuple;

int checkTuple(Tuple *tupleList, int tupleCount, int k) {
    for(int i = 0; i < tupleCount; i++) {
        if(tupleList[i].size != k) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int tupleCount = 3;
    int k = 2;

    Tuple *tupleList = malloc(sizeof(Tuple) * tupleCount);
    if (!tupleList) {
        printf("Failed to allocate memory for tupleList.\n");
        return -1;
    }

    for(int i = 0; i < tupleCount; i++) {
        tupleList[i].elements = malloc(sizeof(int) * k);
        if (!tupleList[i].elements) {
            printf("Failed to allocate memory for elements.\n");

            /* Clean up any previously allocated elements */
            for(int j = 0; j< i; j++) {
                free(tupleList[j].elements);
            }
            
            /* Clean up tupleList */
            free(tupleList);
            return -1;
        }
        tupleList[i].size = k;
    }

    if(checkTuple(tupleList, tupleCount, k)) {
        printf("All tuples have %d elements.\n", k);
    } else {
        printf("Not all tuples have %d elements.\n", k);
    }

    for(int i = 0; i < tupleCount; i++) {
        free(tupleList[i].elements);
    }

    free(tupleList);

    return 0;
}