#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double calculate_cylinder_surface_area(double radius, double height) {
    if (radius < 0.0 || height < 0.0) {
        return -1.0;
    }
    return 2.0 * M_PI * radius * (radius + height);
}

int main(void) {
    double radius = 0.0;
    double height = 0.0;
    double surface_area = 0.0;
    int result = 0;

    printf("Enter the radius of the cylinder: ");
    result = scanf("%lf", &radius);
    if (result != 1 || radius < 0.0) {
        fprintf(stderr, "Invalid input for radius.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the height of the cylinder: ");
    result = scanf("%lf", &height);
    if (result != 1 || height < 0.0) {
        fprintf(stderr, "Invalid input for height.\n");
        return EXIT_FAILURE;
    }

    surface_area = calculate_cylinder_surface_area(radius, height);
    if (surface_area < 0.0) {
        fprintf(stderr, "Error calculating surface area.\n");
        return EXIT_FAILURE;
    }

    printf("The surface area of the cylinder is: %.2lf\n", surface_area);

    return EXIT_SUCCESS;
}