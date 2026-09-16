#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int is_equilateral(double a, double b, double c)
{
    double maximum;
    double tolerance;

    if (!isfinite(a) || !isfinite(b) || !isfinite(c) ||
        a <= 0.0 || b <= 0.0 || c <= 0.0) {
        return 0;
    }

    maximum = fmax(a, fmax(b, c));
    tolerance = maximum * 1e-9;

    return fabs(a - b) <= tolerance &&
           fabs(b - c) <= tolerance;
}

int main(void)
{
    double a;
    double b;
    double c;
    int result;

    result = scanf("%lf %lf %lf", &a, &b, &c);
    if (result != 3) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (is_equilateral(a, b, c)) {
        puts("The triangle is equilateral.");
    } else {
        puts("The triangle is not equilateral.");
    }

    return EXIT_SUCCESS;
}