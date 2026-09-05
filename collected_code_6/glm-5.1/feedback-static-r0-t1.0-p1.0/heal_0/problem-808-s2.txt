#include <stdio.h>
#include <stdlib.h>

int contains_k(int **tuples, int num_tuples, int tuple_size, int k) {
    if (tuples == NULL || num_tuples <= 0 || tuple_size <= 0) {
        return 0;
    }
    for (int i = 0; i < num_tuples; i++) {
        if (tuples[i] == NULL) {
            return 0;
        }
        for (int j = 0; j < tuple_size; j++) {
            if (tuples[i][j] == k) {
                return 1;
            }
        }
    }
    return 0;
}

int main(void) {
    int num_tuples = 3;
    int tuple_size = 3;
    int **tuples = (int **)malloc(num_tuples * sizeof(int *));
    if (tuples == NULL) {
        return EXIT_FAILURE;
    }
    for (int i = 0; i < num_tuples; i++) {
        tuples[i] = (int *)malloc(tuple_size * sizeof(int));
        if (tuples[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(tuples[j]);
            }
            free(tuples);
            return EXIT_FAILURE;
        }
    }
    tuples[0][0] = 1; tuples[0][1] = 2; tuples[0][2] = 3;
    tuples[1][0] = 4; tuples[1][1] = 5; tuples[1][2] = 6;
    tuples[2][0] = 7; tuples[2][1] = 8; tuples[2][2] = 9;
    int k = 5;
    int result = contains_k(tuples, num_tuples, tuple_size, k);
    printf("%d\n", result);
    for (int i = 0; i < num_tuples; i++) {
        free(tuples[i]);
    }
    free(tuples);
    return EXIT_SUCCESS;
}