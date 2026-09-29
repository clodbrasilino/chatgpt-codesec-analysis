#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double find_third_side(double a, double b, double c) {
    if (a <= 0 || b <= 0 || c < 0) {
        fprintf(stderr, "Invalid input\n");
        exit(EXIT_FAILURE);
    }
    
    if (c == 0) {
        return sqrt(a * a + b * b);
    }
    
    if (c <= a && c <= b) {
        fprintf(stderr, "Invalid triangle\n");
        exit(EXIT_FAILURE);
    }
    
    if (c == a || c == b) {
        fprintf(stderr, "Invalid triangle\n");
        exit(EXIT_FAILURE);
    }
    
    if (c > a && c > b) {
        return sqrt(c * c - a * a);
    }
    
    if (a > b) {
        return sqrt(a * a - b * b);
    }
    
    return sqrt(b * b - a * a);
}

int main(void) {
    double a, b, c, result;
    
    printf("Enter two sides and hypotenuse (0 for unknown): ");
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    result = find_third_side(a, b, c);
    printf("Third side: %.2f\n", result);
    
    return 0;
}