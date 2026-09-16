#include <stdio.h>
#include <stdlib.h>

double calculate_cube_surface_area(double side_length) {
    if (side_length < 0.0) {
        return -1.0;
    }
    return 6.0 * side_length * side_length;
}

int main(void) {
    double side_length = 5.0;
    double surface_area;

    surface_area = calculate_cube_surface_area(side_length);

    if (surface_area < 0.0) {
        fprintf(stderr, "Error: Side length cannot be negative.\n");
        return EXIT_FAILURE;
    }

    printf("The surface area of the cube with side length %.2f is %.2f\n", side_length, surface_area);

    return EXIT_SUCCESS;
}