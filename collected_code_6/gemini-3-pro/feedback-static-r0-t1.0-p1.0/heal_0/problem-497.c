#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int calculate_cone_surface_area(double radius, double height, double *surface_area) {
    if (radius < 0.0 || height < 0.0 || surface_area == NULL) {
        return -1;
    }

    double slant_height = sqrt((radius * radius) + (height * height));
    *surface_area = M_PI * radius * (radius + slant_height);

    return 0;
}

int main(void) {
    double radius = 5.0;
    double height = 12.0;
    double surface_area = 0.0;

    int status = calculate_cone_surface_area(radius, height, &surface_area);

    if (status == 0) {
        printf("Surface Area: %.6f\n", surface_area);
    } else {
        fprintf(stderr, "Error: Invalid input parameters.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}