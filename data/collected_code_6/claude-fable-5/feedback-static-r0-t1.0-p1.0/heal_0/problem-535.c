#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

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
    int result = 0;

    printf("Enter the radius of the cylinder: ");
    result = scanf("%lf", &radius);

    if (result != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (radius < 0.0) {
        fprintf(stderr, "Error: radius cannot be negative.\n");
        return EXIT_FAILURE;
    }

    if (radius > sqrt(DBL_MAX / M_PI)) {
        fprintf(stderr, "Error: radius too large, result would overflow.\n");
        return EXIT_FAILURE;
    }

    area = cylinder_surface_area(radius);
    printf("The top/bottom surface area of the cylinder is: %f\n", area);

    return EXIT_SUCCESS;
}