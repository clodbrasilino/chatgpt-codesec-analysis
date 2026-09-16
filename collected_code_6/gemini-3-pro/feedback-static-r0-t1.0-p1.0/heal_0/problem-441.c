#include <stdio.h>
#include <stdlib.h>

double calculate_cube_surface_area(double side_length) {
    if (side_length < 0) {
        return -1.0;
    }
    return 6.0 * side_length * side_length;
}

int main(void) {
    double side = 5.0;
    double surface_area = calculate_cube_surface_area(side);

    if (surface_area < 0) {
        fprintf(stderr, "Invalid side length\n");
        return EXIT_FAILURE;
    }

    printf("Surface area of cube: %f\n", surface_area);

    return EXIT_SUCCESS;
}