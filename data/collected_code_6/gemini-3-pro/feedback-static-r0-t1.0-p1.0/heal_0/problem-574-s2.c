#include <stdio.h>
#include <stdlib.h>

#define PI 3.14159265358979323846

double calculate_cylinder_surface_area(double radius, double height) {
    if (radius < 0.0 || height < 0.0) {
        return -1.0;
    }
    return 2.0 * PI * radius * (radius + height);
}

int main(void) {
    double radius = 0.0;
    double height = 0.0;
    double surface_area = 0.0;

    if (scanf("%lf %lf", &radius, &height) != 2) {
        return EXIT_FAILURE;
    }

    surface_area = calculate_cylinder_surface_area(radius, height);

    if (surface_area < 0.0) {
        return EXIT_FAILURE;
    }

    printf("%f\n", surface_area);

    return EXIT_SUCCESS;
}