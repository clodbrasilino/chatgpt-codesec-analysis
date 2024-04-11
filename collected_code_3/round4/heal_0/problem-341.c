#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int compare(const void *a, const void *b) {
    Tuple *tupleA = (Tuple *)a;
    Tuple *tupleB = (Tuple *)b;

    if (tupleA->first != tupleB->first) {
        return tupleA->first - tupleB->first;
    } else {
        return tupleA->second - tupleB->second;
    }
}

void convertToOrderedTuples(int *set, int setSize, Tuple *tuples) {
    for (int i = 0; i < setSize; i += 2) {
        tuples[i / 2].first = set[i];
        tuples[i / 2].second = set[i + 1];
    }

    qsort(tuples, setSize / 2, sizeof(Tuple), compare);
}

int main() {
    int set[] = {5, 2, 3, 1, 4, 6};
    int setSize = sizeof(set) / sizeof(set[0]);

    Tuple *tuples = malloc(sizeof(Tuple) * setSize / 2);

    convertToOrderedTuples(set, setSize, tuples);

    for (int i = 0; i < setSize / 2; i++) {
        printf("(%d, %d)\n", tuples[i].first, tuples[i].second);
    }

    free(tuples);

    return 0;
}