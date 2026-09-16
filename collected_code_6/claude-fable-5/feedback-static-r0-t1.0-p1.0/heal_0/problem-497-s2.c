#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double cone_surface_area(double radius, double height)
{
    double slant = sqrt((radius * radius) + (height * height));
    return M_PI * radius * (radius + slant);
}

int main(void)
{
    double radius = 0.0;
    double height = 0.0;
    double area = 0.0;

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

    area = cone_surface_area(radius, height);

    if (isnan(area) || isinf(area)) {
        fprintf(stderr, "Error: computation resulted in an invalid value.\n");
        return EXIT_FAILURE;
    }

    printf("Surface area of the cone: %f\n", area);

    return EXIT_SUCCESS;
}