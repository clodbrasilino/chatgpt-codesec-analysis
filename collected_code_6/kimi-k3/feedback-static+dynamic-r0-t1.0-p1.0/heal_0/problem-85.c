#include <stdio.h>
#include <math.h>

double calculate_sphere_surface_area(double radius) {
    if (radius < 0.0) {
        return -1.0;
    }
    return 4.0 * M_PI * radius * radius;
}

int main(void) {
    double radius;
    double surface_area;

    printf("Enter the radius of the sphere: ");
    
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Error: Invalid input\n");
        return 1;
    }

    surface_area = calculate_sphere_surface_area(radius);

    if (surface_area < 0.0) {
        fprintf(stderr, "Error: Radius cannot be negative\n");
        return 1;
    }

    printf("Surface area of the sphere: %.2f\n", surface_area);

    return 0;
}