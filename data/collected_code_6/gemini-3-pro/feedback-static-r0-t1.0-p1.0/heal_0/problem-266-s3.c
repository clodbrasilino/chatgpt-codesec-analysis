#include <stdio.h>
#include <stdlib.h>

double lateral_surface_area_cube(double side) {
    if (side <= 0.0) {
        return -1.0;
    }
    return 4.0 * side * side;
}

int main(void) {
    double side = 5.0;
    double area = lateral_surface_area_cube(side);

    if (area < 0.0) {
        fprintf(stderr, "Error: Side length must be a positive number.\n");
        return EXIT_FAILURE;
    }

    printf("The lateral surface area of the cube with side %.2f is %.2f\n", side, area);

    return EXIT_SUCCESS;
}