#include <stdio.h>
#include <stdlib.h>

double multiply_and_divide(const int *arr, size_t len, int *error) {
    if (arr == NULL || len == 0) {
        *error = 1;
        return 0.0;
    }
    
    *error = 0;
    double product = 1.0;
    
    for (size_t i = 0; i < len; i++) {
        product *= arr[i];
    }
    
    return product / (double)len;
}

int main(void) {
    int numbers[] = {2, 3, 4, 5};
    size_t length = sizeof(numbers) / sizeof(numbers[0]);
    int error = 0;
    
    double result = multiply_and_divide(numbers, length, &error);
    
    if (error != 0) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    
    printf("Result: %.2f\n", result);
    
    return EXIT_SUCCESS;
}