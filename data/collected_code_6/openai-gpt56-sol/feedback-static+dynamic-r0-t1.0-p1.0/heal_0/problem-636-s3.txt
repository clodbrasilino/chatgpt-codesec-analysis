#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static int roots_are_reciprocal(double a, double b, double c)
{
    const double tolerance = 1e-12;
    double scale;

    if (!isfinite(a) || !isfinite(b) || !isfinite(c) || a == 0.0) {
        return 0;
    }

    if (b * b < 4.0 * a * c) {
        return 0;
    }

    scale = fmax(fabs(a), fabs(c));
    return fabs(a - c) <= tolerance * fmax(1.0, scale);
}

int main(void)
{
    double a;
    double b;
    double c;

    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (roots_are_reciprocal(a, b, c)) {
        printf("The roots are reciprocal of each other.\n");
    } else {
        printf("The roots are not reciprocal of each other.\n");
    }

    return EXIT_SUCCESS;
}