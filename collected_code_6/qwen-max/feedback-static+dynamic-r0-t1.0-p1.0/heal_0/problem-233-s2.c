#include <stdio.h>
#include <math.h>

double lateral_surface_area_cylinder(double radius, double height) {
    return 2 * M_PI * radius * height;
}

int main() {
    double radius = 5.0;
    double height = 10.0;

    double area = lateral_surface_area_cylinder(radius, height);

    printf("The lateral surface area of the cylinder is: %f\n", area);

    return 0;
}