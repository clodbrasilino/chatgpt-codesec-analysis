#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double babylonian_sqrt(double number, double epsilon) {
    double guess;
    double previous;
    
    if (number < 0) {
        fprintf(stderr, "Error: Cannot compute square root of negative number\n");
        exit(EXIT_FAILURE);
    }
    
    if (number == 0) {
        return 0;
    }
    
    if (epsilon <= 0) {
        fprintf(stderr, "Error: Epsilon must be positive\n");
        exit(EXIT_FAILURE);
    }
    
    guess = number / 2.0;
    
    do {
        previous = guess;
        guess = (previous + number / previous) / 2.0;
    } while (fabs(guess - previous) > epsilon);
    
    return guess;
}

int main(void) {
    double number;
    double epsilon;
    double result;
    
    printf("Enter a number: ");
    if (scanf("%lf", &number) != 1) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter epsilon: ");
    if (scanf("%lf", &epsilon) != 1) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    
    result = babylonian_sqrt(number, epsilon);
    printf("Square root of %.6f is approximately %.6f\n", number, result);
    
    return EXIT_SUCCESS;
}