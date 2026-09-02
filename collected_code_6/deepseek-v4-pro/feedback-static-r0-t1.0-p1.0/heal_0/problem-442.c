#include <stdio.h>
#include <stdlib.h>

double ratio_of_positive_numbers(const int *array, size_t size) {
    if (array == NULL || size == 0) {
        return 0.0;
    }
    
    size_t positive_count = 0;
    for (size_t i = 0; i < size; i++) {
        if (array[i] > 0) {
            positive_count++;
        }
    }
    
    return (double)positive_count / (double)size;
}

int main(void) {
    int test_array[] = {-1, 2, 3, -4, 5, -6, 7, 8, 9, 10};
    size_t test_size = sizeof(test_array) / sizeof(test_array[0]);
    
    double ratio = ratio_of_positive_numbers(test_array, test_size);
    printf("Ratio of positive numbers: %.4f\n", ratio);
    
    double empty_ratio = ratio_of_positive_numbers(NULL, 0);
    printf("Ratio for NULL/empty: %.4f\n", empty_ratio);
    
    return 0;
}