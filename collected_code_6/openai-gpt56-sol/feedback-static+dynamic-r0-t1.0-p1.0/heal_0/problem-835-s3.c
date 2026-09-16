#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static int calculate_slope(double x1, double y1, double x2, double y2, double *slope)
{
    if (slope == NULL || !isfinite(x1) || !isfinite(y1) ||
        !isfinite(x2) || !isfinite(y2) || x1 == x2) {
        return 0;
    }

    *slope = (y2 - y1) / (x2 - x1);
    return isfinite(*slope) ? 1 : 0;
}

int main(void)
{
    double x1;
    double y1;
    double x2;
    double y2;
    double slope;

    if (scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2) != 4) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!calculate_slope(x1, y1, x2, y2, &slope)) {
        fputs("The slope is undefined or not representable\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.17g\n", slope) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}