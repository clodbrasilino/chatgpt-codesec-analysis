#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    int length;
} Tuple;

void removeTuplesWithLengthK(Tuple **tuples, int *numTuples, int k) {
    if (!tuples || !*tuples || !numTuples) {
        return;
    }

    int i = 0;
    while (i < *numTuples) {
        if ((*tuples)[i].length == k) {
            free((*tuples)[i].elements);
            (*tuples)[i].elements = NULL;

            for (int j = i; j < *numTuples - 1; j++) {
                (*tuples)[j] = (*tuples)[j + 1];
            }
            (*numTuples)--;
        } else {
            i++;
        }
    }
}

int main() {
    int numTuples = 4;
    Tuple *tuples = malloc(numTuples * sizeof(Tuple));
    if (!tuples) {
        return 1;
    }

    for (int i = 0; i < numTuples; i++) {
        tuples[i].length = i + 1;
        tuples[i].elements = malloc(tuples[i].length * sizeof(int));
        if (!tuples[i].elements) {
            for (int j = 0; j < i; j++) {
                free(tuples[j].elements);
            }
            free(tuples);
            return 1;
        }
        for (int j = 0; j < tuples[i].length; j++) {
            tuples[i].elements[j] = j;
        }
    }

    int k = 2;
    removeTuplesWithLengthK(&tuples, &numTuples, k);

    for (int i = 0; i < numTuples; i++) {
        for (int j = 0; j < tuples[i].length; j++) {
            printf("%d ", tuples[i].elements[j]);
        }
        printf("\n");
        free(tuples[i].elements);
    }
    
    free(tuples);
    return 0;
}