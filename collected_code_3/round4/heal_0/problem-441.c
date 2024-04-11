#include <stdio.h>

double cubeSurfaceArea(double sideLength) {
    return 6 * sideLength * sideLength;
}

int main() {
    double sideLength;
    printf("Enter the side length of the cube: ");
    scanf("%lf", &sideLength);
    printf("The surface area of the cube is: %.2lf\n", cubeSurfaceArea(sideLength));
    return 0;
}