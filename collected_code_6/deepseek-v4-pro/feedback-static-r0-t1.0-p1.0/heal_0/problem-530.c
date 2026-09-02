#include <stdio.h>
#include <stdlib.h>

double ratio_of_negatives(const int *arr, size_t size) {
    if (arr == NULL || size == 0) {
        return 0.0;
    }
    
    size_t negative_count = 0;
    for (size_t i = 0; i < size; i++) {
        if (arr[i] < 0) {
            negative_count++;
        }
    }
    
    return (double)negative_count / (double)size;
}

int main(void) {
    int test_array[] = {-5, 2, -3, 1, -8, 4, -1, 0, -7, 3};
    size_t array_size = sizeof(test_array) / sizeof(test_array[0]);
    
    double result = ratio_of_negatives(test_array, array_size);
    printf("Ratio of negative numbers: %.2f\n", result);
    
    return EXIT_SUCCESS;
}