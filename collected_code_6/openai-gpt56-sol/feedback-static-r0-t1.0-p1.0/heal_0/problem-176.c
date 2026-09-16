#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int triangle_perimeter(double a, double b, double c, double *perimeter)
{
    if (perimeter == NULL ||
        !isfinite(a) || !isfinite(b) || !isfinite(c) ||
        a <= 0.0 || b <= 0.0 || c <= 0.0 ||
        a > DBL_MAX - b || a + b <= c ||
        a > DBL_MAX - c || a + c <= b ||
        b > DBL_MAX - c || b + c <= a) {
        return 0;
    }

    if (a > DBL_MAX - b || a + b > DBL_MAX - c) {
        return 0;
    }

    *perimeter = a + b + c;
    return 1;
}

int main(void)
{
    double a;
    double b;
    double c;
    double perimeter;

    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!triangle_perimeter(a, b, c, &perimeter)) {
        fputs("Invalid triangle\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.2f\n", perimeter) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}