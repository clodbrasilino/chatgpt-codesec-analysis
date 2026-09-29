#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *data;
    size_t length;
} Tuple;

bool checkEqualLengthTuples(Tuple *tuples, size_t numTuples) {
    if (tuples == NULL || numTuples == 0) {
        return false;
    }

    size_t firstLength = tuples[0].length;

    for (size_t i = 1; i < numTuples; ++i) {
        if (tuples[i].length != firstLength) {
            return false;
        }
    }

    return true;
}

int main(void) {
    size_t numTuples = 3;
    Tuple *tuples = (Tuple *)malloc(numTuples * sizeof(Tuple));
    if (tuples == NULL) {
        return EXIT_FAILURE;
    }

    tuples[0].length = 5;
    tuples[0].data = (int *)malloc(tuples[0].length * sizeof(int));

    tuples[1].length = 5;
    tuples[1].data = (int *)malloc(tuples[1].length * sizeof(int));

    tuples[2].length = 5;
    tuples[2].data = (int *)malloc(tuples[2].length * sizeof(int));

    if (tuples[0].data == NULL || tuples[1].data == NULL || tuples[2].data == NULL) {
        free(tuples[0].data);
        free(tuples[1].data);
        free(tuples[2].data);
        free(tuples);
        return EXIT_FAILURE;
    }

    bool result = checkEqualLengthTuples(tuples, numTuples);
    
    if (result) {
        printf("All tuples have equal length.\n");
    } else {
        printf("Tuples have different lengths.\n");
    }

    for (size_t i = 0; i < numTuples; ++i) {
        free(tuples[i].data);
    }
    free(tuples);

    return EXIT_SUCCESS;
}