#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static double lateral_surface_area(double length, double width, double height)
{
    return 2.0 * (length + width) * height;
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

    if (!isfinite(length) || !isfinite(width) || !isfinite(height) ||
        length < 0.0 || width < 0.0 || height < 0.0) {
        fputs("Dimensions must be finite and non-negative\n", stderr);
        return EXIT_FAILURE;
    }

    const double area = lateral_surface_area(length, width, height);

    if (!isfinite(area)) {
        fputs("Result is out of range\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%.2f\n", area);
    return EXIT_SUCCESS;
}