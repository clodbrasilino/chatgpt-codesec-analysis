#include <stdio.h>
#include <stdlib.h>

int calculate_cuboid_surface_area(double length, double width, double height, double *surface_area) {
    if (surface_area == NULL) {
        return -1;
    }

    if (length < 0.0 || width < 0.0 || height < 0.0) {
        return -1;
    }

    *surface_area = 2.0 * ((length * width) + (width * height) + (height * length));
    
    return 0;
}

int main(void) {
    double length = 5.5;
    double width = 3.2;
    double height = 2.0;
    double surface_area = 0.0;

    int status = calculate_cuboid_surface_area(length, width, height, &surface_area);

    if (status != 0) {
        fprintf(stderr, "Error: Invalid dimensions or null pointer provided.\n");
        return EXIT_FAILURE;
    }

    printf("Surface Area: %.2f\n", surface_area);

    return EXIT_SUCCESS;
}