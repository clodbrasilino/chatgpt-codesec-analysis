#include <stdio.h>

double lateral_surface_area_cube(double side) {
    return 4 * side * side;
}

int main() {
    double side;
    printf("Enter the length of a side of the cube: ");
    if (scanf("%lf", &side) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    printf("The lateral surface area of the cube is: %f\n", lateral_surface_area_cube(side));
    return 0;
}