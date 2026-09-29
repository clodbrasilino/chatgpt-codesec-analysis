#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846

double sector_area(double radius, double angle_degrees)
{
    return (angle_degrees / 360.0) * PI * radius * radius;
}

int main(void)
{
    double radius = 0.0;
    double angle = 0.0;
    double area = 0.0;

    printf("Enter the radius of the circle: ");
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Error: invalid input for radius.\n");
        return EXIT_FAILURE;
    }

    if (radius < 0.0) {
        fprintf(stderr, "Error: radius cannot be negative.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the angle of the sector in degrees: ");
    if (scanf("%lf", &angle) != 1) {
        fprintf(stderr, "Error: invalid input for angle.\n");
        return EXIT_FAILURE;
    }

    if (angle < 0.0 || angle > 360.0) {
        fprintf(stderr, "Error: angle must be between 0 and 360 degrees.\n");
        return EXIT_FAILURE;
    }

    area = sector_area(radius, angle);

    if (isnan(area) || isinf(area)) {
        fprintf(stderr, "Error: computed area is not a valid number.\n");
        return EXIT_FAILURE;
    }

    printf("The area of the sector is: %.6f\n", area);

    return EXIT_SUCCESS;
}