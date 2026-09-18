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
    *results = malloc(sizeof(TupleFrequency) * tupleCount);
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
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'results' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            (*results)[*resultCount].tuple = tuples[i];
            (*results)[(*resultCount)++].frequency = 1;
        }
    }
    /* Possible weaknesses found:
     *  leak of 'results' [CWE-401] [-Wanalyzer-malloc-leak]
     */
    *results = realloc(*results, sizeof(TupleFrequency) * (*resultCount));
}

int main() {
    Tuple tuples[] = {
        {1, 2},
        {1, 2},
        {3, 4}
    };

    TupleFrequency *results;
    int resultCount;

    assignFrequencies(tuples, sizeof(tuples) / sizeof(tuples[0]), &results, &resultCount);

    for (int i = 0; i < resultCount; i++) {
        /* Possible weaknesses found:
         *  dereference of NULL '0' [CWE-476] [-Wanalyzer-null-dereference]
         */
        printf("{(%d, %d), %d}\n", results[i].tuple.first, results[i].tuple.second, results[i].frequency);
    }

    free(results);

    return 0;
}