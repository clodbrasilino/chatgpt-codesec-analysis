#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int cone_surface_area(double radius, double height, double *area)
{
    double slant_height;
    double result;

    if (area == NULL || !isfinite(radius) || !isfinite(height) ||
        radius < 0.0 || height < 0.0) {
        return 0;
    }

    slant_height = hypot(radius, height);
    result = M_PI * radius * (radius + slant_height);

    if (!isfinite(result)) {
        return 0;
    }

    *area = result;
    return 1;
}

int main(void)
{
    double radius;
    double height;
    double area;

    printf("Enter the radius and height of the cone: ");
    fflush(stdout);

    if (scanf("%lf %lf", &radius, &height) != 2) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (!cone_surface_area(radius, height, &area)) {
        fprintf(stderr, "Unable to calculate the surface area.\n");
        return EXIT_FAILURE;
    }

    printf("Surface area: %.6f\n", area);
    return EXIT_SUCCESS;
}