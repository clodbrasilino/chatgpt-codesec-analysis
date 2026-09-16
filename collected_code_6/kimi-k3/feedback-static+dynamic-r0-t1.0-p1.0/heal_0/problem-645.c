#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int get_kth_product(int **tuples, int num_tuples, int tuple_size, int k, int *result) {
    if (tuples == NULL || result == NULL) {
        return -1;
    }
    if (num_tuples <= 0 || tuple_size <= 0) {
        return -1;
    }
    if (k < 0 || k >= tuple_size) {
        return -1;
    }
    
    long long product = 1;
    for (int i = 0; i < num_tuples; i++) {
        if (tuples[i] == NULL) {
            return -1;
        }
        if (tuples[i][k] != 0 && llabs(product) > LLONG_MAX / llabs(tuples[i][k])) {
            return -1;
        }
        product *= tuples[i][k];
    }
    
    if (product > INT_MAX || product < INT_MIN) {
        return -1;
    }
    
    *result = (int)product;
    return 0;
}

int main(void) {
    int num_tuples = 3;
    int tuple_size = 3;
    int k = 1;
    
    int **tuples = malloc(num_tuples * sizeof(int *));
    if (tuples == NULL) {
        return 1;
    }
    
    for (int i = 0; i < num_tuples; i++) {
        tuples[i] = malloc(tuple_size * sizeof(int));
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
    
    int result = 0;
    if (get_kth_product(tuples, num_tuples, tuple_size, k, &result) == 0) {
        printf("%d\n", result);
    } else {
        printf("Error\n");
    }
    
    for (int i = 0; i < num_tuples; i++) {
        free(tuples[i]);
    }
    free(tuples);
    
    return 0;
}