#include <stdio.h>
#include <stdlib.h>

static int calculate_slope(double x1, double y1, double x2, double y2, double *slope)
{
    if (slope == NULL || x1 == x2) {
        return 0;
    }

    *slope = (y2 - y1) / (x2 - x1);
    return 1;
}

int main(void)
{
    double x1;
    double y1;
    double x2;
    double y2;
    double slope;

    if (scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2) != 4) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!calculate_slope(x1, y1, x2, y2, &slope)) {
        fprintf(stderr, "Slope is undefined for a vertical line\n");
        return EXIT_FAILURE;
    }

    printf("%.10g\n", slope);
    return EXIT_SUCCESS;
}