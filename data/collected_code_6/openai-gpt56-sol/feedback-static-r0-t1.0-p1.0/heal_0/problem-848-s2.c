#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static int trapezium_area(double base1, double base2, double height, double *area)
{
    if (area == NULL || !isfinite(base1) || !isfinite(base2) ||
        !isfinite(height) || base1 < 0.0 || base2 < 0.0 || height < 0.0) {
        return 0;
    }

    *area = 0.5 * (base1 + base2) * height;

    return isfinite(*area);
}

int main(void)
{
    double base1;
    double base2;
    double height;
    double area;

    if (scanf("%lf %lf %lf", &base1, &base2, &height) != 3) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!trapezium_area(base1, base2, height, &area)) {
        fputs("Unable to calculate area\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.2f\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}