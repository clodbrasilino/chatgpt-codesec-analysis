#include <stdio.h>
#include <stdlib.h>

double power(double a, int b) {
    double result = 1.0;
    int exp = b;
    
    if (a == 0.0 && b <= 0) {
        fprintf(stderr, "Error: 0 cannot be raised to a non-positive power\n");
        exit(EXIT_FAILURE);
    }
    
    if (exp < 0) {
        a = 1.0 / a;
        exp = -exp;
    }
    
    while (exp > 0) {
        if (exp % 2 == 1) {
            result *= a;
        }
        a *= a;
        exp /= 2;
    }
    
    return result;
}

int main(void) {
    double base;
    int exponent;
    
    printf("Enter base: ");
    if (scanf("%lf", &base) != 1) {
        fprintf(stderr, "Error: Invalid input for base\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter exponent: ");
    if (scanf("%d", &exponent) != 1) {
        fprintf(stderr, "Error: Invalid input for exponent\n");
        return EXIT_FAILURE;
    }
    
    double result = power(base, exponent);
    printf("%.2f^%d = %.10f\n", base, exponent, result);
    
    return EXIT_SUCCESS;
}