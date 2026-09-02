#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
} Tuple;

int product_at_k(Tuple *tuples, int tuple_count, int k) {
    if (tuples == NULL || tuple_count <= 0 || k < 0) {
        return 0;
    }
    
    int product = 1;
    int found_any = 0;
    
    for (int i = 0; i < tuple_count; i++) {
        if (tuples[i].data != NULL && k < tuples[i].size) {
            product *= tuples[i].data[k];
            found_any = 1;
        }
    }
    
    if (!found_any) {
        return 0;
    }
    
    return product;
}

int main(void) {
    int data1[] = {1, 2, 3, 4};
    int data2[] = {5, 6, 7, 8};
    int data3[] = {9, 10, 11, 12};
    
    Tuple tuples[3];
    tuples[0].data = data1;
    tuples[0].size = 4;
    tuples[1].data = data2;
    tuples[1].size = 4;
    tuples[2].data = data3;
    tuples[2].size = 4;
    
    int k = 2;
    int result = product_at_k(tuples, 3, k);
    printf("Product at index %d: %d\n", k, result);
    
    Tuple empty_tuples[2];
    empty_tuples[0].data = NULL;
    empty_tuples[0].size = 0;
    empty_tuples[1].data = NULL;
    empty_tuples[1].size = 0;
    
    int empty_result = product_at_k(empty_tuples, 2, 0);
    printf("Product with empty tuples: %d\n", empty_result);
    
    int invalid_result = product_at_k(NULL, 0, 0);
    printf("Product with NULL input: %d\n", invalid_result);
    
    return 0;
}