#include <stdio.h>
#include <stdlib.h>

int find_product(int **tuples, int num_tuples, int tuple_size, int k) {
    if (tuples == NULL || num_tuples <= 0 || k < 0 || k >= tuple_size) {
        return -1;
    }
    
    int product = 1;
    for (int i = 0; i < num_tuples; i++) {
        if (tuples[i] == NULL) {
            return -1;
        }
        product *= tuples[i][k];
    }
    return product;
}

int main(void) {
    int **tuples = NULL;
    int num_tuples = 3;
    int tuple_size = 4;
    int k = 2;
    int result;
    
    tuples = (int **)malloc(num_tuples * sizeof(int *));
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
    
    tuples[0][0] = 1; tuples[0][1] = 2; tuples[0][2] = 3; tuples[0][3] = 4;
    tuples[1][0] = 5; tuples[1][1] = 6; tuples[1][2] = 7; tuples[1][3] = 8;
    tuples[2][0] = 9; tuples[2][1] = 10; tuples[2][2] = 11; tuples[2][3] = 12;
    
    result = find_product(tuples, num_tuples, tuple_size, k);
    
    if (result != -1) {
        printf("Product of elements at index %d: %d\n", k, result);
    } else {
        printf("Invalid input parameters\n");
    }
    
    for (int i = 0; i < num_tuples; i++) {
        free(tuples[i]);
    }
    free(tuples);
    
    return EXIT_SUCCESS;
}