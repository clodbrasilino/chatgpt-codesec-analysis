#include <stdio.h>
#include <stdlib.h>

static double cuboid_lateral_surface_area(double length, double width, double height)
{
    return 2.0 * height * (length + width);
}

int main(void)
{
    double length;
    double width;
    double height;

    if (scanf("%lf %lf %lf", &length, &width, &height) != 3) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (length < 0.0 || width < 0.0 || height < 0.0) {
        fputs("Dimensions must be non-negative\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%.2f\n", cuboid_lateral_surface_area(length, width, height));

    return EXIT_SUCCESS;
}