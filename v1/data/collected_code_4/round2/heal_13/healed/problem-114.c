#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    Tuple tuple;
    int frequency;
} TupleFrequency;

void assignFrequencies(Tuple *tuples, int tupleCount, TupleFrequency **results, int *resultCount) {
    if (tupleCount == 0 || results == NULL || resultCount == NULL)
        return;

    *results = (TupleFrequency*)malloc(sizeof(TupleFrequency) * tupleCount);

    if (*results == NULL)
        return;

    *resultCount = 0;

    for (int i = 0; i < tupleCount; i++) {
        int j;
        for (j = 0; j < *resultCount; j++) {
            if ((*results)[j].tuple.first == tuples[i].first &&
                (*results)[j].tuple.second == tuples[i].second) {
                (*results)[j].frequency++;
                break;
            }
        }

        if (j == *resultCount) {
            (*results)[*resultCount].tuple = tuples[i];
            (*results)[(*resultCount)++].frequency = 1;
        }
    }

    *results = (TupleFrequency*)realloc(*results, sizeof(TupleFrequency) * (*resultCount));

    if(*results == NULL) {
        *resultCount = 0;
    }
}

int main() {
    Tuple tuples[] = {{1, 2},{1, 2},{3, 4}};
    TupleFrequency *results = NULL;
    int resultCount;

    assignFrequencies(tuples, sizeof(tuples) / sizeof(tuples[0]), &results, &resultCount);

    if (results != NULL) {
        for (int i = 0; i < resultCount; i++) {
            printf("{(%d, %d), %d}\n", results[i].tuple.first, results[i].tuple.second, results[i].frequency);
        }

        free(results);
        results = NULL;
    }

    return 0;
}