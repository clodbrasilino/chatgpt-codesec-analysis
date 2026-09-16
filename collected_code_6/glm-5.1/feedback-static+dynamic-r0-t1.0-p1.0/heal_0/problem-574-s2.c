#include <stdio.h>
#include <math.h>

double calculate_cylinder_surface_area(double radius, double height) {
    if (radius < 0.0 || height < 0.0) {
        return -1.0;
    }

    double base_area = M_PI * radius * radius;
    double lateral_area = 2.0 * M_PI * radius * height;

    return 2.0 * base_area + lateral_area;
}

int main(void) {
    double radius = 3.0;
    double height = 5.0;

    double surface_area = calculate_cylinder_surface_area(radius, height);

    if (surface_area < 0.0) {
        return 1;
    }

    printf("%f\n", surface_area);

    return 0;
}