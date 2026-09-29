#include <stdio.h>
#include <stdlib.h>

int product_of_kth_index(int **tuples, int num_tuples, int tuple_size, int k) {
    if (tuples == NULL || num_tuples <= 0 || tuple_size <= 0) {
        return 0;
    }
    if (k < 0 || k >= tuple_size) {
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
    int row0[] = {1, 2, 3};
    int row1[] = {4, 5, 6};
    int row2[] = {7, 8, 9};
    int num_tuples = 3;
    int tuple_size = 3;
    int **tuples = (int **)malloc(num_tuples * sizeof(int *));
    if (tuples == NULL) {
        return 1;
    }
    tuples[0] = row0;
    tuples[1] = row1;
    tuples[2] = row2;
    int k = 1;
    int result = product_of_kth_index(tuples, num_tuples, tuple_size, k);
    printf("%d\n", result);
    free(tuples);
    return 0;
}