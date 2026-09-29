#include <stdio.h>

double surfaceAreaOfCube(double side) {
    return 6 * side * side;
}

int main() {
    double side;
    printf("Enter the side length of the cube: ");
    scanf("%lf", &side);
    double surfaceArea = surfaceAreaOfCube(side);
    printf("The surface area of the cube is: %.2lf", surfaceArea);

    return 0;
}