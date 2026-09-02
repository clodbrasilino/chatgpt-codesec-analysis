#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double triangle_perimeter(double side1, double side2, double side3) {
    if (side1 <= 0 || side2 <= 0 || side3 <= 0) {
        fprintf(stderr, "Error: Side lengths must be positive numbers.\n");
        exit(EXIT_FAILURE);
    }
    
    if (side1 + side2 <= side3 || side1 + side3 <= side2 || side2 + side3 <= side1) {
        fprintf(stderr, "Error: Invalid triangle. Sum of any two sides must exceed the third side.\n");
        exit(EXIT_FAILURE);
    }
    
    return side1 + side2 + side3;
}

int main(void) {
    double a, b, c;
    double perimeter;
    
    printf("Enter the lengths of the three sides of the triangle: ");
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fprintf(stderr, "Error: Invalid input. Please enter three numeric values.\n");
        return EXIT_FAILURE;
    }
    
    perimeter = triangle_perimeter(a, b, c);
    
    printf("The perimeter of the triangle is: %.2f\n", perimeter);
    
    return EXIT_SUCCESS;
}