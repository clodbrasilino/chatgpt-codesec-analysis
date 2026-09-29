#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double cylinder_surface_area(double radius)
{
    return M_PI * radius * radius;
}

int main(void)
{
    double radius = 0.0;
    double area = 0.0;

    printf("Enter the radius of the cylinder: ");

    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (radius < 0.0) {
        fprintf(stderr, "Error: radius cannot be negative.\n");
        return EXIT_FAILURE;
    }

    if (!isfinite(radius)) {
        fprintf(stderr, "Error: radius must be a finite number.\n");
        return EXIT_FAILURE;
    }

    area = cylinder_surface_area(radius);

    if (!isfinite(area)) {
        fprintf(stderr, "Error: computation overflow.\n");
        return EXIT_FAILURE;
    }

    printf("The top/bottom surface area of the cylinder is: %.6f\n", area);

    return EXIT_SUCCESS;
}