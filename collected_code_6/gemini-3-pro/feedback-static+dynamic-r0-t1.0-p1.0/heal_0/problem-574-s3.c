#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double calculate_cylinder_surface_area(double radius, double height);

double calculate_cylinder_surface_area(double radius, double height) {
    if (radius < 0.0 || height < 0.0) {
        return -1.0;
    }
    return 2.0 * M_PI * radius * (radius + height);
}

int main(void) {
    double radius;
    double height;
    double surface_area;

    if (scanf("%lf %lf", &radius, &height) != 2) {
        fprintf(stderr, "Error: Invalid input.\n");
        return EXIT_FAILURE;
    }

    surface_area = calculate_cylinder_surface_area(radius, height);

    if (surface_area < 0.0) {
        fprintf(stderr, "Error: Radius and height must be non-negative.\n");
        return EXIT_FAILURE;
    }

    printf("%.6f\n", surface_area);

    return EXIT_SUCCESS;
}