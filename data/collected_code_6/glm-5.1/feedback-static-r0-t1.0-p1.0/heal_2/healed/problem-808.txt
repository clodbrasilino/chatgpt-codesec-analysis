#include <stdio.h>
#include <stdlib.h>

int tuple_contains_k(const int *array, size_t num_tuples, size_t tuple_size, int k) {
    if (array == NULL || num_tuples == 0 || tuple_size == 0) {
        return 0;
    }
    
    size_t total_elements = num_tuples * tuple_size;
    
    for (size_t i = 0; i < total_elements; i++) {
        if (array[i] == k) {
            return 1;
        }
    }
    
    return 0;
}

int main(void) {
    const int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t num_tuples = 5;
    size_t tuple_size = 2;
    int k = 5;
    
    int result = tuple_contains_k(data, num_tuples, tuple_size, k);
    
    printf("%d\n", result);
    
    return 0;
}