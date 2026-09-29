#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double calculate_sphere_surface_area(double radius) {
    if (radius < 0.0) {
        return -1.0;
    }
    return 4.0 * M_PI * radius * radius;
}

int main(void) {
    double radius;
    double surface_area;
    int result;

    printf("Enter the radius of the sphere: ");
    result = scanf("%lf", &radius);

    if (result != 1) {
        printf("Invalid input.\n");
        return EXIT_FAILURE;
    }

    surface_area = calculate_sphere_surface_area(radius);

    if (surface_area < 0.0) {
        printf("Radius cannot be negative.\n");
        return EXIT_FAILURE;
    }

    printf("The surface area of the sphere is: %.2f\n", surface_area);

    return EXIT_SUCCESS;
}