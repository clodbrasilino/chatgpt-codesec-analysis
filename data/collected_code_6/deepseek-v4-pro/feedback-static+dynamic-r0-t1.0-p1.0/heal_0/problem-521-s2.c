#include <stdio.h>
#include <math.h>

int is_scalene(double a, double b, double c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return 0;
    }
    if (a + b <= c || a + c <= b || b + c <= a) {
        return 0;
    }
    if (fabs(a - b) < 1e-9 || fabs(b - c) < 1e-9 || fabs(a - c) < 1e-9) {
        return 0;
    }
    return 1;
}

int main(void) {
    double a, b, c;
    
    printf("Enter three sides of a triangle: ");
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (is_scalene(a, b, c)) {
        printf("The triangle is scalene\n");
    } else {
        printf("The triangle is not scalene\n");
    }
    
    return 0;
}