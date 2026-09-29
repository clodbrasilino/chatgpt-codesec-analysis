#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int sector_area(double radius, double angle_degrees, double *area)
{
    const double pi = acos(-1.0);

    if (area == NULL || !isfinite(radius) || !isfinite(angle_degrees) ||
        radius < 0.0 || angle_degrees < 0.0 || angle_degrees > 360.0) {
        return 0;
    }

    errno = 0;
    *area = pi * radius * radius * angle_degrees / 360.0;

    return errno == 0 && isfinite(*area);
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
        fprintf(stderr, "Unable to calculate the sector area.\n");
        return EXIT_FAILURE;
    }

    printf("Area of the sector: %.6f\n", area);
    return EXIT_SUCCESS;
}