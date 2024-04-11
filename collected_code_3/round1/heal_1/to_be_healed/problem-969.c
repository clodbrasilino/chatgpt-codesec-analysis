#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* first;
    char* second;
} Tuple;

Tuple* joinTuples(Tuple* tuples, int size) {
    Tuple* result = malloc(sizeof(Tuple) * size);
    int count = 0;

    for(int i = 0; i < size; i++) {
        for(int j = i + 1; j < size; j++) {
            if(strcmp(tuples[i].first, tuples[j].first) == 0) {
                Tuple newTuple;
                newTuple.first = tuples[i].first;
                newTuple.second = malloc(strlen(tuples[i].second) + strlen(tuples[j].second) + 1);
                strcpy(newTuple.second, tuples[i].second);
                strcat(newTuple.second, tuples[j].second);
                /* Possible weaknesses found:
                 *  dereference of possibly-NULL 'result' [CWE-690] [-Wanalyzer-possible-null-dereference]
                 */
                result[count++] = newTuple;
            }
        }
    }

    return result;
}

int main() {
    Tuple tuples[] = {
        {"apple", "red"},
        {"banana", "yellow"},
        {"apple", "green"},
        {"banana", "ripe"},
        {"grape", "purple"}
    };

    int size = sizeof(tuples) / sizeof(Tuple);
    Tuple* result = joinTuples(tuples, size);

    for(int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'result' [CWE-690] [-Wanalyzer-possible-null-dereference]
         *  use of uninitialized value '*result_24 + _2.second' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
         */
        printf("%s: %s\n", result[i].first, result[i].second);
    }

    return 0;
}