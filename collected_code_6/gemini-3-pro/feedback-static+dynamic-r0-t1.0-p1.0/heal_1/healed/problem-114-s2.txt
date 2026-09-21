#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    const char* name;
} Tuple;

typedef struct {
    Tuple tuple;
    int frequency;
} TupleFrequency;

TupleFrequency* calculateTupleFrequencies(Tuple* tuples, int numTuples, int* numUniqueTuples) {
    if (tuples == NULL || numTuples <= 0 || numUniqueTuples == NULL) {
        return NULL;
    }

    TupleFrequency* frequencies = (TupleFrequency*)malloc(numTuples * sizeof(TupleFrequency));
    if (frequencies == NULL) {
        return NULL;
    }

    int uniqueCount = 0;

    for (int i = 0; i < numTuples; i++) {
        int found = 0;
        for (int j = 0; j < uniqueCount; j++) {
            if (tuples[i].id == frequencies[j].tuple.id &&
                strcmp(tuples[i].name, frequencies[j].tuple.name) == 0) {
                frequencies[j].frequency++;
                found = 1;
                break;
            }
        }
        if (!found) {
            frequencies[uniqueCount].tuple = tuples[i];
            frequencies[uniqueCount].frequency = 1;
            uniqueCount++;
        }
    }

    *numUniqueTuples = uniqueCount;
    return frequencies;
}

int main(void) {
    Tuple tuples[] = {
        {1, "Alice"},
        {2, "Bob"},
        {1, "Alice"},
        {3, "Charlie"},
        {2, "Bob"},
        {1, "Alice"}
    };
    
    int numTuples = sizeof(tuples) / sizeof(tuples[0]);
    int numUniqueTuples = 0;

    TupleFrequency* frequencies = calculateTupleFrequencies(tuples, numTuples, &numUniqueTuples);

    if (frequencies != NULL) {
        for (int i = 0; i < numUniqueTuples; i++) {
            printf("Tuple: {%d, '%s'}, Frequency: %d\n", 
                   frequencies[i].tuple.id, 
                   frequencies[i].tuple.name, 
                   frequencies[i].frequency);
        }
        free(frequencies);
    } else {
        printf("Failed to calculate frequencies or memory allocation error.\n");
    }

    return 0;
}