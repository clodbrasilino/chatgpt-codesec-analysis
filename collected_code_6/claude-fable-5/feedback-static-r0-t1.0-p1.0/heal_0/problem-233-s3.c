#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double lateral_surface_area(double radius, double height)
{
    return 2.0 * M_PI * radius * height;
}

int main(void)
{
    double radius;
    double height;
    double area;

    printf("Enter the radius of the cylinder: ");
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Error: invalid input for radius.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the height of the cylinder: ");
    if (scanf("%lf", &height) != 1) {
        fprintf(stderr, "Error: invalid input for height.\n");
        return EXIT_FAILURE;
    }

    if (radius < 0.0 || height < 0.0) {
        fprintf(stderr, "Error: radius and height must be non-negative.\n");
        return EXIT_FAILURE;
    }

    if (!isfinite(radius) || !isfinite(height)) {
        fprintf(stderr, "Error: radius and height must be finite values.\n");
        return EXIT_FAILURE;
    }

    area = lateral_surface_area(radius, height);

    if (!isfinite(area)) {
        fprintf(stderr, "Error: computation resulted in overflow.\n");
        return EXIT_FAILURE;
    }

    printf("Lateral surface area of the cylinder: %.6f\n", area);

    return EXIT_SUCCESS;
}