#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

static int largest_triangle_area(long double semi_major,
                                 long double semi_minor,
                                 long double *area)
{
    const long double coefficient = 0.75L * sqrtl(3.0L);
    long double product;

    if (area == NULL ||
        !isfinite(semi_major) ||
        !isfinite(semi_minor) ||
        semi_major <= 0.0L ||
        semi_minor <= 0.0L) {
        return 0;
    }

    if (semi_minor > 1.0L &&
        semi_major > LDBL_MAX / semi_minor) {
        return 0;
    }

    product = semi_major * semi_minor;

    if (!isfinite(product) ||
        product > LDBL_MAX / coefficient) {
        return 0;
    }

    *area = coefficient * product;
    return isfinite(*area);
}

int main(void)
{
    long double semi_major;
    long double semi_minor;
    long double area;

    if (scanf("%Lf %Lf", &semi_major, &semi_minor) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!largest_triangle_area(semi_major, semi_minor, &area)) {
        fprintf(stderr, "Invalid ellipse dimensions or result overflow\n");
        return EXIT_FAILURE;
    }

    if (printf("%.10Lf\n", area) < 0 || fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}