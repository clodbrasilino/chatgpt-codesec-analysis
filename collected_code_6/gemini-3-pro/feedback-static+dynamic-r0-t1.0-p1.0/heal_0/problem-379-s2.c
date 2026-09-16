#include <stdio.h>
#include <stdlib.h>

double calculate_cuboid_surface_area(double length, double width, double height) {
    if (length <= 0.0 || width <= 0.0 || height <= 0.0) {
        return -1.0;
    }
    return 2.0 * ((length * width) + (length * height) + (width * height));
}

int main(void) {
    double length = 5.0;
    double width = 3.0;
    double height = 4.0;
    double surface_area;

    surface_area = calculate_cuboid_surface_area(length, width, height);

    if (surface_area < 0.0) {
        fprintf(stderr, "Invalid dimensions provided for the cuboid.\n");
        return EXIT_FAILURE;
    }

    printf("Surface area: %.2f\n", surface_area);

    return EXIT_SUCCESS;
}