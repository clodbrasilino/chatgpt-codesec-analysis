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
    
    if (scanf("%lf %lf %lf", &side1, &side2, &side3) != 3) {
        printf("False\n");
        return 0;
    }
    
    if (isValidTriangle(side1, side2, side3)) {
        printf("True\n");
    } else {
        printf("False\n");
    }
    
    return 0;
}