#include <stdio.h>
#include <stdlib.h>

int** add_k_elements(int** tuples, int num_tuples, int tuple_size, const int* k_elements, int k) {
    if (!tuples || !k_elements || num_tuples <= 0 || tuple_size <= 0 || k <= 0) {
        return NULL;
    }

    int** new_tuples = (int**)malloc(num_tuples * sizeof(int*));
    if (!new_tuples) {
        return NULL;
    }

    for (int i = 0; i < num_tuples; i++) {
        if (!tuples[i]) {
            for (int j = 0; j < i; j++) {
                free(new_tuples[j]);
            }
            free(new_tuples);
            return NULL;
        }

        new_tuples[i] = (int*)malloc((tuple_size + k) * sizeof(int));
        if (!new_tuples[i]) {
            for (int j = 0; j < i; j++) {
                free(new_tuples[j]);
            }
            free(new_tuples);
            return NULL;
        }

        for (int j = 0; j < tuple_size; j++) {
            new_tuples[i][j] = tuples[i][j];
        }

        for (int j = 0; j < k; j++) {
            new_tuples[i][tuple_size + j] = k_elements[j];
        }
    }

    return new_tuples;
}

int main(void) {
    int num_tuples = 2;
    int tuple_size = 2;
    int k = 2;

    int** tuples = (int**)malloc(num_tuples * sizeof(int*));
    if (!tuples) {
        return 1;
    }

    for (int i = 0; i < num_tuples; i++) {
        tuples[i] = (int*)malloc(tuple_size * sizeof(int));
        if (!tuples[i]) {
            for (int j = 0; j < i; j++) {
                free(tuples[j]);
            }
            free(tuples);
            return 1;
        }
    }

    tuples[0][0] = 1;
    tuples[0][1] = 2;
    tuples[1][0] = 3;
    tuples[1][1] = 4;

    /* Possible weaknesses found:
     *  Variable 'k_elements' can be declared as const array [constVariable]
     */
    int k_elements[2] = {5, 6};

    int** result = add_k_elements(tuples, num_tuples, tuple_size, k_elements, k);
    if (!result) {
        for (int i = 0; i < num_tuples; i++) {
            free(tuples[i]);
        }
        free(tuples);
        return 1;
    }

    for (int i = 0; i < num_tuples; i++) {
        for (int j = 0; j < tuple_size + k; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < num_tuples; i++) {
        free(tuples[i]);
        free(result[i]);
    }
    free(tuples);
    free(result);

    return 0;
}