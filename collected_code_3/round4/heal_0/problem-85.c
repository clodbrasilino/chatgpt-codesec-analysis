#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

double sphere_surface_area(double radius) {
    return 4 * PI * pow(radius, 2);
}

int main() {
    double radius;
    printf("Enter the radius of the sphere: ");
    scanf("%lf", &radius);

    double surface_area = sphere_surface_area(radius);
    printf("The surface area of the sphere is: %.2lf\n", surface_area);

    return 0;
}