#include <stdio.h>

int isValidTriangle(double a, double b, double c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return 0;
    }
    
    if (a + b <= c || b + c <= a || a + c <= b) {
        return 0;
    }
    
    return 1;
}

int main(void) {
    double side1, side2, side3;
    
    printf("Enter three sides of triangle: ");
    if (scanf("%lf %lf %lf", &side1, &side2, &side3) != 3) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (isValidTriangle(side1, side2, side3)) {
        printf("Valid triangle\n");
    } else {
        printf("Invalid triangle\n");
    }
    
    return 0;
}