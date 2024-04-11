#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tuple {
    char *initial;
    char *rest;
} Tuple;

Tuple* joinTuples(Tuple *tuples, int size) {
    if (tuples == NULL) {
        return NULL;
    }

    Tuple *result = (Tuple *) malloc(sizeof(Tuple) * size);
    if (result == NULL) {
        return NULL;
    }
    
    int count = 0;

    for(int i = 0; i < size; i++) {
        for(int j = i + 1; j < size; j++) {
            if(strcmp(tuples[i].initial, tuples[j].initial) == 0) {
                Tuple newTuple;
                newTuple.initial = tuples[i].initial;
                int length = strlen(tuples[i].rest) + strlen(tuples[j].rest) + 1;
                newTuple.rest = (char *) malloc(length);
                if (newTuple.rest != NULL) {
                    strcpy(newTuple.rest, tuples[i].rest);
                    strcat(newTuple.rest, tuples[j].rest);
                    result[count++] = newTuple;
                }
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

    if (result != NULL) {
        for(int i = 0; i < size; i++) {
            if (result[i].rest != NULL && result[i].initial != NULL) {
                printf("Initial: %s, Rest: %s\n", result[i].initial, result[i].rest);
            }
        }
    }

    free(result);

    return 0;
}