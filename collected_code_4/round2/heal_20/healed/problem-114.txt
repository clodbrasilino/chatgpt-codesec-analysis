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
    if (tupleCount == 0 || results == NULL || resultCount == NULL) return;

    TupleFrequency* temp = (TupleFrequency*)malloc(sizeof(TupleFrequency) * tupleCount);
    if (temp == NULL) return;

    *resultCount = 0;

    for (int i = 0; i < tupleCount; i++) {
        int j;

        for (j = 0; j < *resultCount; j++) {
            if (temp[j].tuple.first == tuples[i].first &&
                temp[j].tuple.second == tuples[i].second) {
                temp[j].frequency++;
                break;
            }
        }

        if (j == *resultCount) {
            temp[*resultCount].tuple = tuples[i];
            temp[(*resultCount)++].frequency = 1;
        }
    }

    *results = (TupleFrequency*)realloc(temp, sizeof(TupleFrequency) * (*resultCount));

    if(*results == NULL) {
        *resultCount = 0;
        free(temp);
    }
}

int main() {
    Tuple tuples[] = {{1, 2},{1, 2},{3, 4}};
    TupleFrequency *results = NULL;
    int resultCount = 0;

    assignFrequencies(tuples, sizeof(tuples) / sizeof(Tuple), &results, &resultCount);

    for (int i = 0; i < resultCount; i++) {
        printf("{(%d, %d), %d}\n", results[i].tuple.first, results[i].tuple.second, results[i].frequency);
    }

    free(results);
    results = NULL;

    return 0;
}