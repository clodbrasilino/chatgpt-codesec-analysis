#include <stdio.h>
#include <math.h>

double lateral_surface_area(double radius, double height)
{
    return 2.0 * M_PI * radius * height;
}

int main(void)
{
    double radius = 0.0;
    double height = 0.0;

    printf("Enter the radius of the cylinder: ");
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Error: invalid input for radius.\n");
        return 1;
    }

    printf("Enter the height of the cylinder: ");
    if (scanf("%lf", &height) != 1) {
        fprintf(stderr, "Error: invalid input for height.\n");
        return 1;
    }

    if (radius < 0.0 || height < 0.0) {
        fprintf(stderr, "Error: radius and height must be non-negative.\n");
        return 1;
    }

    if (!isfinite(radius) || !isfinite(height)) {
        fprintf(stderr, "Error: inputs must be finite numbers.\n");
        return 1;
    }

    double area = lateral_surface_area(radius, height);

    if (!isfinite(area)) {
        fprintf(stderr, "Error: result overflowed.\n");
        return 1;
    }

    printf("Lateral surface area of the cylinder: %.6f\n", area);

    return 0;
}