#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int is_equilateral(double a, double b, double c)
{
    const double scale = fmax(a, fmax(b, c));
    const double tolerance = scale * 1e-9;

    return a > 0.0 && b > 0.0 && c > 0.0 &&
           isfinite(a) && isfinite(b) && isfinite(c) &&
           fabs(a - b) <= tolerance &&
           fabs(b - c) <= tolerance;
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

    if (is_equilateral(a, b, c)) {
        printf("The triangle is equilateral.\n");
    } else {
        printf("The triangle is not equilateral.\n");
    }

    return EXIT_SUCCESS;
}