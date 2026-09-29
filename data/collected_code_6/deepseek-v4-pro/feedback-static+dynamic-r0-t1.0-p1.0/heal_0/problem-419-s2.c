#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double sum_rounded_numbers(const double *numbers, int length) {
    double total = 0.0;
    for (int i = 0; i < length; i++) {
        total += round(numbers[i]);
    }
    return total * length;
}

int main(void) {
    double numbers[] = {1.2, 2.6, 3.5, 4.4, 5.8};
    int length = sizeof(numbers) / sizeof(numbers[0]);
    
    double result = sum_rounded_numbers(numbers, length);
    printf("Result: %.2f\n", result);
    
    return 0;
}