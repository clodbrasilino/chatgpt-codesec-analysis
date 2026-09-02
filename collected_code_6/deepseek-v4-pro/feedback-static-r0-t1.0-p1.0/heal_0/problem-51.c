#include <stdio.h>
#include <math.h>

int is_equilateral(double side1, double side2, double side3) {
    if (side1 <= 0 || side2 <= 0 || side3 <= 0) {
        return 0;
    }
    if (isnan(side1) || isnan(side2) || isnan(side3) ||
        isinf(side1) || isinf(side2) || isinf(side3)) {
        return 0;
    }
    if (fabs(side1 - side2) < 1e-9 && fabs(side2 - side3) < 1e-9) {
        return 1;
    }
    return 0;
}

int main(void) {
    double side1, side2, side3;
    
    printf("Enter three sides of a triangle: ");
    if (scanf("%lf %lf %lf", &side1, &side2, &side3) != 3) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (is_equilateral(side1, side2, side3)) {
        printf("The triangle is equilateral\n");
    } else {
        printf("The triangle is not equilateral\n");
    }
    
    return 0;
}