#include <stdio.h>
#include <math.h>

double sphere_surface_area(double radius) {
    return 4 * M_PI * pow(radius, 2);
}

int main() {
    double radius = 5.0;
    double area = sphere_surface_area(radius);
    printf("The surface area of the sphere is: %f\n", area);
    return 0;
}