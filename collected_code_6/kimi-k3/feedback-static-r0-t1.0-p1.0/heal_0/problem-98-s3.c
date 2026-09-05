#include <stdio.h>
#include <stdlib.h>

double multiply_and_divide(const double *list, size_t length) {
    if (list == NULL || length == 0) {
        return 0.0;
    }
    
    double product = 1.0;
    for (size_t i = 0; i < length; i++) {
        product *= list[i];
    }
    
    return product / (double)length;
}

int main(void) {
    double numbers[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    size_t length = sizeof(numbers) / sizeof(numbers[0]);
    
    double result = multiply_and_divide(numbers, length);
    printf("Result: %.2f\n", result);
    
    return 0;
}