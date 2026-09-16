#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double calculate_cone_surface_area(double radius, double height);

double calculate_cone_surface_area(double radius, double height) {
    double slant_height;

    if (radius < 0.0 || height < 0.0) {
        return -1.0;
    }

    slant_height = sqrt((radius * radius) + (height * height));
    
    return M_PI * radius * (radius + slant_height);
}

int main(void) {
    double radius = 0.0;
    double height = 0.0;
    double surface_area = 0.0;

    if (scanf("%lf %lf", &radius, &height) != 2) {
        return EXIT_FAILURE;
    }

    surface_area = calculate_cone_surface_area(radius, height);

    if (surface_area < 0.0) {
        return EXIT_FAILURE;
    }

    printf("%.6f\n", surface_area);

    return EXIT_SUCCESS;
}