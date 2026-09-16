#include <stdio.h>
#include <math.h>

double sphere_surface_area(double radius);

int main(void) {
    double radius;
    int scan_result;

    printf("Enter the radius of the sphere: ");
    scan_result = scanf("%lf", &radius);

    if (scan_result != 1 || radius < 0.0) {
        fprintf(stderr, "Invalid input. Radius must be a non-negative number.\n");
        return 1;
    }

    printf("Surface area: %f\n", sphere_surface_area(radius));

    return 0;
}

double sphere_surface_area(double radius) {
    return 4.0 * M_PI * radius * radius;
}