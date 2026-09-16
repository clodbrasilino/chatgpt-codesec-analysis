#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double babylonian_sqrt(double value) {
    if (value < 0.0) {
        fprintf(stderr, "Error: cannot compute square root of negative number\n");
        exit(EXIT_FAILURE);
    }
    if (value == 0.0) {
        return 0.0;
    }
    
    double guess = value;
    double epsilon = 1e-10;
    
    while (fabs(guess * guess - value) > epsilon) {
        guess = (guess + value / guess) / 2.0;
    }
    
    return guess;
}

int main(void) {
    double numbers[] = {0.0, 1.0, 2.0, 4.0, 9.0, 16.0, 25.0, 100.0};
    size_t count = sizeof(numbers) / sizeof(numbers[0]);
    
    for (size_t i = 0; i < count; i++) {
        double result = babylonian_sqrt(numbers[i]);
        printf("sqrt(%f) = %f\n", numbers[i], result);
    }
    
    return 0;
}