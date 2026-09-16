#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define PI 3.14159265358979323846

double surface_area_cylinder(double radius, double height) {
    if (radius < 0 || height < 0) {
        fprintf(stderr, "Error: Radius and height must be non-negative\n");
        exit(EXIT_FAILURE);
    }
    return 2.0 * PI * radius * (radius + height);
}

int main(void) {
    double radius = 0.0;
    double height = 0.0;
    double area = 0.0;

    printf("Enter radius: ");
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Invalid input for radius\n");
        return EXIT_FAILURE;
    }

    printf("Enter height: ");
    if (scanf("%lf", &height) != 1) {
        fprintf(stderr, "Invalid input for height\n");
        return EXIT_FAILURE;
    }

    if (radius < 0 || height < 0) {
        fprintf(stderr, "Error: Radius and height must be non-negative\n");
        return EXIT_FAILURE;
    }

    area = surface_area_cylinder(radius, height);
    printf("Surface area: %.2f\n", area);

    return EXIT_SUCCESS;
}