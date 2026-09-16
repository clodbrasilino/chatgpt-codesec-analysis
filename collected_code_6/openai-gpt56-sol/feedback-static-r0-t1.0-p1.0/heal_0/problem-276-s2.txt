#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static double cylinder_volume(double radius, double height)
{
    return M_PI * radius * radius * height;
}

int main(void)
{
    double radius;
    double height;

    if (scanf("%lf %lf", &radius, &height) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!isfinite(radius) || !isfinite(height) || radius < 0.0 || height < 0.0) {
        fprintf(stderr, "Radius and height must be finite and nonnegative\n");
        return EXIT_FAILURE;
    }

    const double volume = cylinder_volume(radius, height);

    if (!isfinite(volume)) {
        fprintf(stderr, "Volume is outside the representable range\n");
        return EXIT_FAILURE;
    }

    printf("%.6f\n", volume);
    return EXIT_SUCCESS;
}