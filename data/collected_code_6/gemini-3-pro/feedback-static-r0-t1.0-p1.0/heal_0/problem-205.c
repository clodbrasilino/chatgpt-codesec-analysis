#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

void findInversions(Tuple* tuples, int numTuples, Tuple** inversions, int* numInversions) {
    if (tuples == NULL || inversions == NULL || numInversions == NULL || numTuples <= 0) {
        return;
    }

    *inversions = (Tuple*)malloc(numTuples * sizeof(Tuple));
    if (*inversions == NULL) {
        *numInversions = 0;
        return;
    }

    *numInversions = numTuples;

    for (int i = 0; i < numTuples; i++) {
        (*inversions)[i].first = tuples[i].second;
        (*inversions)[i].second = tuples[i].first;
    }
}

int main() {
    Tuple tuples[] = {{1, 2}, {3, 4}, {5, 6}};
    int numTuples = sizeof(tuples) / sizeof(tuples[0]);

    Tuple* inversions = NULL;
    int numInversions = 0;

    findInversions(tuples, numTuples, &inversions, &numInversions);

    for (int i = 0; i < numInversions; i++) {
        printf("(%d, %d)\n", inversions[i].first, inversions[i].second);
    }

    if (inversions != NULL) {
        free(inversions);
        inversions = NULL;
    }

    return 0;
}