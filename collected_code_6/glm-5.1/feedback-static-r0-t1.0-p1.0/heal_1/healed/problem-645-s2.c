#include <stdio.h>
#include <stdlib.h>

int product_of_kth_index(int **tuples, int num_tuples, int tuple_size, int k) {
    if (tuples == NULL || num_tuples <= 0 || tuple_size <= 0 || k < 0 || k >= tuple_size) {
        return 0;
    }

    int product = 1;
    for (int i = 0; i < num_tuples; i++) {
        if (tuples[i] == NULL) {
            return 0;
        }
        product *= tuples[i][k];
    }
    return product;
}

int main(void) {
    int num_tuples = 3;
    int k = 1;
    
    int **tuples = (int **)malloc(num_tuples * sizeof(int *));
    if (tuples == NULL) {
        return 1;
    }

    const int sizes[] = {3, 3, 3};

    for (int i = 0; i < num_tuples; i++) {
        tuples[i] = (int *)malloc(sizes[i] * sizeof(int));
        if (tuples[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(tuples[j]);
            }
            free(tuples);
            return 1;
        }
    }

    tuples[0][0] = 1; tuples[0][1] = 2; tuples[0][2] = 3;
    tuples[1][0] = 4; tuples[1][1] = 5; tuples[1][2] = 6;
    tuples[2][0] = 7; tuples[2][1] = 8; tuples[2][2] = 9;

    int result = product_of_kth_index(tuples, num_tuples, sizes[0], k);
    printf("%d\n", result);

    for (int i = 0; i < num_tuples; i++) {
        free(tuples[i]);
    }
    free(tuples);

    return 0;
}