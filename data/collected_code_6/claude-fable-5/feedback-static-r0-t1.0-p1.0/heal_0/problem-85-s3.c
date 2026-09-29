#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double sphere_surface_area(double radius)
{
    return 4.0 * M_PI * radius * radius;
}

int main(void)
{
    double radius = 0.0;
    double area = 0.0;

    printf("Enter the radius of the sphere: ");

    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (radius < 0.0) {
        fprintf(stderr, "Error: radius cannot be negative.\n");
        return EXIT_FAILURE;
    }

    area = sphere_surface_area(radius);

    if (isinf(area) || isnan(area)) {
        fprintf(stderr, "Error: computation overflow.\n");
        return EXIT_FAILURE;
    }

    printf("Surface area of the sphere: %.6f\n", area);

    return EXIT_SUCCESS;
}