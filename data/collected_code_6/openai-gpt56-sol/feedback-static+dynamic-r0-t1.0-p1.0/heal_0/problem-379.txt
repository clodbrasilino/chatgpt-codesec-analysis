#include <stdio.h>
#include <stdlib.h>

static int calculate_surface_area(double length, double width, double height,
                                  double *surface_area)
{
    if (length < 0.0 || width < 0.0 || height < 0.0 || surface_area == NULL) {
        return EXIT_FAILURE;
    }

    *surface_area = 2.0 * (length * width + length * height + width * height);
    return EXIT_SUCCESS;
}

int main(void)
{
    double length;
    double width;
    double height;
    double surface_area;

    if (scanf("%lf %lf %lf", &length, &width, &height) != 3) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (calculate_surface_area(length, width, height, &surface_area) != EXIT_SUCCESS) {
        fputs("Dimensions must be non-negative\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.2f\n", surface_area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}