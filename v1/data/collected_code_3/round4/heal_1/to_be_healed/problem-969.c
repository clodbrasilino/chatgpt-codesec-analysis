#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tuple {
    char *initial;
    char *rest;
} Tuple;

Tuple* joinTuples(Tuple *tuples, int size) {
    Tuple *result = malloc(sizeof(Tuple) * size);
    int count = 0;

    for(int i = 0; i < size; i++) {
        for(int j = i + 1; j < size; j++) {
            if(strcmp(tuples[i].initial, tuples[j].initial) == 0) {
                Tuple newTuple;
                newTuple.initial = tuples[i].initial;
                newTuple.rest = malloc(strlen(tuples[i].rest) + strlen(tuples[j].rest) + 1);
                strcpy(newTuple.rest, tuples[i].rest);
                strcat(newTuple.rest, tuples[j].rest);
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
        {"A", "123"},
        {"B", "456"},
        {"A", "789"},
        {"B", "012"}
    };

    int size = sizeof(tuples) / sizeof(Tuple);
    Tuple *result = joinTuples(tuples, size);

    for(int i = 0; i < size; i++) {
        /* Possible weaknesses found:
         *  use of uninitialized value '*result_22 + _2.rest' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
         *  dereference of possibly-NULL 'result' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        printf("Initial: %s, Rest: %s\n", result[i].initial, result[i].rest);
    }

    return 0;
}