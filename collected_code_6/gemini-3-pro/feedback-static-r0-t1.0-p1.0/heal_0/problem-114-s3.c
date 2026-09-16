#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    int value;
} Tuple;

typedef struct {
    Tuple tuple;
    int frequency;
} TupleFrequency;

TupleFrequency* calculate_frequencies(Tuple* tuples, int num_tuples, int* num_unique) {
    if (tuples == NULL || num_tuples <= 0 || num_unique == NULL) {
        return NULL;
    }

    TupleFrequency* frequencies = (TupleFrequency*)malloc(num_tuples * sizeof(TupleFrequency));
    if (frequencies == NULL) {
        return NULL;
    }

    int unique_count = 0;

    for (int i = 0; i < num_tuples; ++i) {
        int found = 0;
        for (int j = 0; j < unique_count; ++j) {
            if (frequencies[j].tuple.id == tuples[i].id && frequencies[j].tuple.value == tuples[i].value) {
                frequencies[j].frequency++;
                found = 1;
                break;
            }
        }
        if (!found) {
            frequencies[unique_count].tuple = tuples[i];
            frequencies[unique_count].frequency = 1;
            unique_count++;
        }
    }

    *num_unique = unique_count;

    TupleFrequency* resized = (TupleFrequency*)realloc(frequencies, unique_count * sizeof(TupleFrequency));
    if (resized != NULL) {
        frequencies = resized;
    }

    return frequencies;
}

int main(void) {
    Tuple tuples[] = {
        {1, 10},
        {2, 20},
        {1, 10},
        {3, 30},
        {2, 20},
        {1, 10}
    };
    int num_tuples = sizeof(tuples) / sizeof(tuples[0]);
    int num_unique = 0;

    TupleFrequency* frequencies = calculate_frequencies(tuples, num_tuples, &num_unique);

    if (frequencies != NULL) {
        for (int i = 0; i < num_unique; ++i) {
            printf("Tuple(%d, %d): Frequency = %d\n", frequencies[i].tuple.id, frequencies[i].tuple.value, frequencies[i].frequency);
        }
        free(frequencies);
    } else {
        printf("Error calculating frequencies.\n");
    }

    return 0;
}