#include <stdio.h>
#include <math.h>

double calculate_cylinder_surface_area(double radius, double height) {
    if (radius < 0.0 || height < 0.0) {
        return -1.0;
    }

    double area = 2.0 * M_PI * radius * (radius + height);

    if (isinf(area) || isnan(area)) {
        return -1.0;
    }

    return area;
}

int main(void) {
    double radius = 5.0;
    double height = 10.0;

    double result = calculate_cylinder_surface_area(radius, height);

    if (result < 0.0) {
        return 1;
    }

    printf("%f\n", result);

    return 0;
}