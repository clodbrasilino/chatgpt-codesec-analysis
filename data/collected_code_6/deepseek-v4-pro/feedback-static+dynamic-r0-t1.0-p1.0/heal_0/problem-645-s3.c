#include <stdio.h>
#include <stdlib.h>

int product_kth_index(int **tuples, int tuple_count, int k) {
    if (tuples == NULL || tuple_count <= 0 || k < 0) {
        return 1;
    }
    
    int product = 1;
    int valid_elements = 0;
    
    for (int i = 0; i < tuple_count; i++) {
        if (tuples[i] != NULL) {
            product *= tuples[i][k];
            valid_elements++;
        }
    }
    
    if (valid_elements == 0) {
        return 1;
    }
    
    return product;
}

int main(void) {
    int tuple1[] = {1, 2, 3, 4, 5};
    int tuple2[] = {6, 7, 8, 9, 10};
    int tuple3[] = {11, 12, 13, 14, 15};
    
    int *tuples[] = {tuple1, tuple2, tuple3};
    
    int k = 2;
    int result = product_kth_index(tuples, 3, k);
    
    printf("Product of %dth index: %d\n", k, result);
    
    return 0;
}