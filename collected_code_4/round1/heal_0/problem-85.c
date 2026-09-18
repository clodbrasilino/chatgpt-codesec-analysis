#include <stdio.h>
#include <math.h>

double sphere_surface_area(double radius) {
    return 4 * M_PI * radius * radius;
}

int main() {
    double radius;
    printf("Enter the radius of the sphere: ");
    if(scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Failed to read input\n");
        return 1;
    }

    if(radius <= 0) {
        fprintf(stderr, "Radius should be greater than 0\n");
        return 1;
    }

    double surface_area = sphere_surface_area(radius);

    printf("The surface area of the sphere is: %.2lf\n", surface_area);

    return 0;
}