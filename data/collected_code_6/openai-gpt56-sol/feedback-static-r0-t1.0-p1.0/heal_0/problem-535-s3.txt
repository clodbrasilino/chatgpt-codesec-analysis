#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static int calculate_surface_area(double radius, double *area)
{
    if (area == NULL || !isfinite(radius) || radius < 0.0) {
        return 0;
    }

    *area = acos(-1.0) * radius * radius;

    if (!isfinite(*area)) {
        return 0;
    }

    return 1;
}

int main(void)
{
    double radius;
    double area;

    printf("Enter the cylinder radius: ");

    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (!calculate_surface_area(radius, &area)) {
        fprintf(stderr, "Unable to calculate the surface area.\n");
        return EXIT_FAILURE;
    }

    printf("Top or bottom surface area: %.6f\n", area);

    return EXIT_SUCCESS;
}