#include <stdio.h>
#include <stdlib.h>

double negative_ratio(const int *array, size_t size) {
    if (array == NULL || size == 0) {
        return 0.0;
    }
    
    size_t negative_count = 0;
    for (size_t i = 0; i < size; i++) {
        if (array[i] < 0) {
            negative_count++;
        }
    }
    
    return (double)negative_count / (double)size;
}

int main(void) {
    int test_array[] = {-5, 3, -2, 0, -1, 4, -7};
    size_t size = sizeof(test_array) / sizeof(test_array[0]);
    
    double ratio = negative_ratio(test_array, size);
    printf("Ratio of negative numbers: %.4f\n", ratio);
    
    return EXIT_SUCCESS;
}