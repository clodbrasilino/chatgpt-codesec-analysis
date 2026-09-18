#include<stdio.h>
#include<stdlib.h>

int areTupleLengthsEqual(int **tuples, int *lengths, int numberOfTuples) {
    int i;
    for(i = 1; i < numberOfTuples; i++) {
        if(lengths[i] != lengths[0]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int numberOfTuples = 3;
    int lengths[3] = {5, 5, 5};
    int **tuples = (int **)malloc(numberOfTuples * sizeof(int *));

    if (tuples == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for(int i = 0; i < numberOfTuples; i++) {
        tuples[i] = (int *)malloc(lengths[i] * sizeof(int));

        if (tuples[i] == NULL) {
            printf("Memory allocation for tuple %d failed.\n", i);

            // Free previously allocated memory
            for (int j = 0; j < i; j++)
                free(tuples[j]);
            free(tuples);
            return 1;
        }
    }

    if (areTupleLengthsEqual(tuples, lengths, numberOfTuples)) {
        printf("All Tuples have equal length\n");
    } else {
        printf("All Tuples do not have equal length\n");
    }

    for(int i = 0; i < numberOfTuples; i++) {
        free(tuples[i]);
    }
    free(tuples);

    return 0;
}