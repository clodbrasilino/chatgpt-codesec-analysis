#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

double calculate_pentagon_perimeter(double side1, double side2, double side3, double side4, double side5) {
    if (side1 <= 0.0 || side2 <= 0.0 || side3 <= 0.0 || side4 <= 0.0 || side5 <= 0.0) {
        return -1.0;
    }
    
    if (isinf(side1) || isinf(side2) || isinf(side3) || isinf(side4) || isinf(side5) ||
        isnan(side1) || isnan(side2) || isnan(side3) || isnan(side4) || isnan(side5)) {
        return -1.0;
    }
    
    return side1 + side2 + side3 + side4 + side5;
}

int main(void) {
    double sides[5];
    double perimeter;
    int i;
    
    printf("Enter the lengths of the 5 sides of the pentagon: ");
    
    for (i = 0; i < 5; i++) {
        if (scanf("%lf", &sides[i]) != 1) {
            fprintf(stderr, "Error: Invalid input\n");
            return EXIT_FAILURE;
        }
    }
    
    perimeter = calculate_pentagon_perimeter(sides[0], sides[1], sides[2], sides[3], sides[4]);
    
    if (perimeter < 0.0) {
        fprintf(stderr, "Error: Invalid side lengths\n");
        return EXIT_FAILURE;
    }
    
    printf("Perimeter of the pentagon: %.2f\n", perimeter);
    
    return EXIT_SUCCESS;
}