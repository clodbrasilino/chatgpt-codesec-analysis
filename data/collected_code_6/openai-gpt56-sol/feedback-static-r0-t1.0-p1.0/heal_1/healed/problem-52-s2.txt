#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_parallelogram_area(double base, double height, double *area)
{
    if (area == NULL ||
        !isfinite(base) ||
        !isfinite(height) ||
        base < 0.0 ||
        height < 0.0) {
        return -1;
    }

    if (base != 0.0 && height > DBL_MAX / base) {
        return -1;
    }

    *area = base * height;
    return 0;
}

int main(void)
{
    double base;
    double height;
    double area;

    printf("Enter base and height: ");

    if (scanf("%lf %lf", &base, &height) != 2) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (calculate_parallelogram_area(base, height, &area) != 0) {
        fputs("Base and height must be finite, non-negative, and within range.\n",
              stderr);
        return EXIT_FAILURE;
    }

    printf("Area: %.2f\n", area);
    return EXIT_SUCCESS;
}