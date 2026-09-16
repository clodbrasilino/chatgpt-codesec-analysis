#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static int cuboid_volume(double length, double width, double height, double *volume)
{
    if (volume == NULL ||
        !isfinite(length) || !isfinite(width) || !isfinite(height) ||
        length < 0.0 || width < 0.0 || height < 0.0) {
        return -1;
    }

    *volume = length * width * height;

    if (!isfinite(*volume)) {
        return -1;
    }

    return 0;
}

int main(void)
{
    double length;
    double width;
    double height;
    double volume;

    if (scanf("%lf %lf %lf", &length, &width, &height) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (cuboid_volume(length, width, height, &volume) != 0) {
        fprintf(stderr, "Unable to calculate volume\n");
        return EXIT_FAILURE;
    }

    printf("%.6f\n", volume);
    return EXIT_SUCCESS;
}