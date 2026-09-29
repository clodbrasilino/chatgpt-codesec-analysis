#include <stdio.h>

double cubeSurfaceArea(double side) {
    return 6 * side * side;
}

int main() {
    double side;
    printf("Enter the side of the cube: ");
    scanf("%lf", &side);
    printf("Surface area of the cube is: %.2lf", cubeSurfaceArea(side));
    return 0;
}