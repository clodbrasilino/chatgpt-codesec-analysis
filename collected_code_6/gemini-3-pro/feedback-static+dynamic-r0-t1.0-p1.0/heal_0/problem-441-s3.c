#include <stdio.h>
#include <stdlib.h>

double calculate_cube_surface_area(double side_length) {
    if (side_length < 0.0) {
        return -1.0;
    }
    return 6.0 * side_length * side_length;
}

int main(void) {
    double side_length;
    double surface_area;

    if (scanf("%lf", &side_length) != 1) {
        return EXIT_FAILURE;
    }

    surface_area = calculate_cube_surface_area(side_length);

    if (surface_area < 0.0) {
        return EXIT_FAILURE;
    }

    printf("%f\n", surface_area);

    return EXIT_SUCCESS;
}