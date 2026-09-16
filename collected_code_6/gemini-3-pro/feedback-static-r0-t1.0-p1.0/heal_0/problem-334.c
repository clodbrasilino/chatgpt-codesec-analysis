#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool isValidTriangle(double sideA, double sideB, double sideC) {
    if (sideA <= 0.0 || sideB <= 0.0 || sideC <= 0.0) {
        return false;
    }
    
    if ((sideA + sideB > sideC) && 
        (sideA + sideC > sideB) && 
        (sideB + sideC > sideA)) {
        return true;
    }
    
    return false;
}

int main(void) {
    double sideA = 0.0;
    double sideB = 0.0;
    double sideC = 0.0;
    
    if (scanf("%lf %lf %lf", &sideA, &sideB, &sideC) != 3) {
        fprintf(stderr, "Error: Invalid input.\n");
        return EXIT_FAILURE;
    }
    
    if (isValidTriangle(sideA, sideB, sideC)) {
        printf("The triangle is valid.\n");
    } else {
        printf("The triangle is not valid.\n");
    }
    
    return EXIT_SUCCESS;
}