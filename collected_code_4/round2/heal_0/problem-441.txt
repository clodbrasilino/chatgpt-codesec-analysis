#include <stdio.h>

double calculateSurfaceArea(double sideLength) {
    if (sideLength <= 0) {
        fprintf(stderr, "Invalid input: side length must be greater than 0.\n");
        return -1;
    }

    return 6 * sideLength * sideLength;
}

int main() {
    double sideLength;
    
    printf("Enter the length of a side of the cube: ");
    scanf("%lf", &sideLength);
    
    double surfaceArea = calculateSurfaceArea(sideLength);
    
    if (surfaceArea != -1) {
        printf("The surface area of the cube is: %.2f\n", surfaceArea);
    }

    return 0;
}