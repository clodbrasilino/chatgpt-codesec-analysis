#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double cone_lateral_surface_area(double radius, double height)
{
    double slant_height;

    slant_height = sqrt((radius * radius) + (height * height));
    return M_PI * radius * slant_height;
}

int main(void)
{
    double radius;
    double height;
    double area;
    int result;

    printf("Enter the radius of the cone: ");
    result = scanf("%lf", &radius);
    if (result != 1) {
        fprintf(stderr, "Error: invalid input for radius.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the height of the cone: ");
    result = scanf("%lf", &height);
    if (result != 1) {
        fprintf(stderr, "Error: invalid input for height.\n");
        return EXIT_FAILURE;
    }

    if (radius < 0.0 || height < 0.0) {
        fprintf(stderr, "Error: radius and height must be non-negative.\n");
        return EXIT_FAILURE;
    }

    area = cone_lateral_surface_area(radius, height);
    printf("Lateral surface area of the cone: %.6f\n", area);

    return EXIT_SUCCESS;
}