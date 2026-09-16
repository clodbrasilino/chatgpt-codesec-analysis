#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static double cylinder_lateral_surface_area(double radius, double height)
{
    return 2.0 * acos(-1.0) * radius * height;
}

int main(void)
{
    double radius;
    double height;

    if (printf("Enter radius and height: ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%lf %lf", &radius, &height) != 2) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (!isfinite(radius) || !isfinite(height) ||
        radius < 0.0 || height < 0.0) {
        fprintf(stderr, "Radius and height must be finite and nonnegative.\n");
        return EXIT_FAILURE;
    }

    const double area = cylinder_lateral_surface_area(radius, height);

    if (!isfinite(area)) {
        fprintf(stderr, "Unable to calculate a finite area.\n");
        return EXIT_FAILURE;
    }

    if (printf("Lateral surface area: %.6f\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}