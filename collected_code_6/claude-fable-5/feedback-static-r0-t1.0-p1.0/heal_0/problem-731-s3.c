#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double cone_lateral_surface_area(double radius, double height)
{
    double slant;

    slant = sqrt((radius * radius) + (height * height));
    return M_PI * radius * slant;
}

int main(void)
{
    double radius;
    double height;
    double area;

    printf("Enter the radius of the cone: ");
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Error: invalid input for radius.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the height of the cone: ");
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

    area = cone_lateral_surface_area(radius, height);

    if (!isfinite(area)) {
        fprintf(stderr, "Error: computation resulted in overflow.\n");
        return EXIT_FAILURE;
    }

    printf("Lateral surface area of the cone: %.6f\n", area);

    return EXIT_SUCCESS;
}