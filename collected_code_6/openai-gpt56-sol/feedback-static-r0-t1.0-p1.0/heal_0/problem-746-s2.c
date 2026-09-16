#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int sector_area(double radius, double angle_degrees, double *area)
{
    const double pi = 3.14159265358979323846;

    if (area == NULL || !isfinite(radius) || !isfinite(angle_degrees) ||
        radius < 0.0 || angle_degrees < 0.0 || angle_degrees > 360.0) {
        return 0;
    }

    *area = (angle_degrees / 360.0) * pi * radius * radius;

    return isfinite(*area);
}

int main(void)
{
    double radius;
    double angle_degrees;
    double area;

    printf("Enter radius and angle in degrees: ");

    if (scanf("%lf %lf", &radius, &angle_degrees) != 2) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (!sector_area(radius, angle_degrees, &area)) {
        fprintf(stderr, "Radius and angle must be finite, with radius nonnegative and angle between 0 and 360 degrees.\n");
        return EXIT_FAILURE;
    }

    printf("Area of the sector: %.6f\n", area);

    return EXIT_SUCCESS;
}