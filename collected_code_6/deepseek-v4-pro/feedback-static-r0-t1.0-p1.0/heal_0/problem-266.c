#include <stdio.h>

double cube_lateral_surface_area(double side) {
    return 4.0 * side * side;
}

int main(void) {
    double side;

    printf("Enter the side length of the cube: ");
    if (scanf("%lf", &side) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    if (side < 0.0) {
        printf("Side length cannot be negative.\n");
        return 1;
    }

    double area = cube_lateral_surface_area(side);
    printf("Lateral surface area: %.2f\n", area);

    return 0;
}