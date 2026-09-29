#include <stdio.h>

void check_isosceles(double a, double b, double c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        printf("Invalid triangle sides\n");
        return;
    }
    
    if (a + b <= c || a + c <= b || b + c <= a) {
        printf("Not a valid triangle\n");
        return;
    }
    
    if (a == b || b == c || a == c) {
        printf("The triangle is isosceles\n");
    } else {
        printf("The triangle is not isosceles\n");
    }
}

int main(void) {
    double side1, side2, side3;
    
    printf("Enter three sides of a triangle: ");
    if (scanf("%lf %lf %lf", &side1, &side2, &side3) != 3) {
        printf("Invalid input\n");
        return 1;
    }
    
    check_isosceles(side1, side2, side3);
    
    return 0;
}