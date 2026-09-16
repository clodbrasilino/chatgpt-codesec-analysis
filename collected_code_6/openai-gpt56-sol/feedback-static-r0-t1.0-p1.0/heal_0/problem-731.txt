#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int cone_lateral_surface_area(double radius, double slant_height, double *area)
{
    const double pi = acos(-1.0);

    if (area == NULL || !isfinite(radius) || !isfinite(slant_height) ||
        radius < 0.0 || slant_height < 0.0) {
        return -1;
    }

    *area = pi * radius * slant_height;

    if (!isfinite(*area)) {
        return -1;
    }

    return 0;
}

int main(void)
{
    double radius = 0.0;
    double slant_height = 0.0;
    double area = 0.0;

    printf("Enter the radius and slant height: ");

    if (scanf("%lf %lf", &radius, &slant_height) != 2) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (cone_lateral_surface_area(radius, slant_height, &area) != 0) {
        fprintf(stderr, "Unable to calculate the lateral surface area.\n");
        return EXIT_FAILURE;
    }

    printf("Lateral surface area: %.6f\n", area);

    return EXIT_SUCCESS;
}