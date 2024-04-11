#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tuple {
    char *initial;
    char *value;
} Tuple;

Tuple* joinTuples(Tuple *tuples, int size, int *newSize) {
    Tuple *result = (Tuple*)malloc(sizeof(Tuple) * size);
    if(result == NULL) {
        return NULL;
    }

    int count = 0;

    for(int i = 0; i < size; i++) {
        if(i > 0 && strcmp(tuples[i].initial, tuples[i-1].initial) == 0) {
            char *temp = result[count-1].value;
            /* Possible weaknesses found:
             *  use of possibly-NULL 'temp' where non-null expected [CWE-690] [-Wanalyzer-possible-null-argument]
             */
            size_t len = strlen(temp) + strlen(tuples[i].value) + 1;
            temp = realloc(temp, len);
            strcat(temp, tuples[i].value);
            result[count-1].value = temp;
        } else {
            result[count].initial = strdup(tuples[i].initial);
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

    if(result == NULL) {
        return 1;
    }

    for(int i = 0; i < newSize; i++) {
        printf("%s %s\n", result[i].initial, result[i].value);
        free(result[i].initial);
        free(result[i].value);
    }

    free(result);

    return 0;
}