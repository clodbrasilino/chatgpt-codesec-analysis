#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tuple {
    char *initial;
    char *value;
} Tuple;

Tuple* joinTuples(Tuple *tuples, int size, int *newSize) {
    Tuple *result = (Tuple*)malloc(sizeof(Tuple) * size);
    int count = 0;

    for(int i = 0; i < size; i++) {
        if(i > 0 && strcmp(tuples[i].initial, tuples[i-1].initial) == 0) {
            strcat(result[count-1].value, tuples[i].value);
        } else {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'result' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            result[count] = tuples[i];
            result[count].value = strdup(tuples[i].value);
            count++;
        }
    }

    *newSize = count;
    return result;
}

int main() {
    int size = 4;
    Tuple tuples[] = {
        {"A", "1"},
        {"A", "2"},
        {"B", "3"},
        {"B", "4"}
    };

    int newSize;
    Tuple *result = joinTuples(tuples, size, &newSize);

    for(int i = 0; i < newSize; i++) {
        printf("%s %s\n", result[i].initial, result[i].value);
        free(result[i].value);
    }

    free(result);

    return 0;
}