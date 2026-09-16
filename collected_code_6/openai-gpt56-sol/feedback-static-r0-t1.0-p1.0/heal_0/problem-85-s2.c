#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int sphere_surface_area(double radius, double *area)
{
    if (area == NULL || !isfinite(radius) || radius < 0.0) {
        return 0;
    }

    errno = 0;
    *area = 4.0 * acos(-1.0) * radius * radius;

    if (errno != 0 || !isfinite(*area)) {
        return 0;
    }

    return 1;
}

int main(void)
{
    double radius;
    double area;

    printf("Enter the radius: ");
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (!sphere_surface_area(radius, &area)) {
        fprintf(stderr, "Unable to calculate the surface area.\n");
        return EXIT_FAILURE;
    }

    printf("Surface area: %.6f\n", area);
    return EXIT_SUCCESS;
}