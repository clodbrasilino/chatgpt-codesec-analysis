#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int triangle_perimeter(double a, double b, double c, double *perimeter)
{
    if (perimeter == NULL ||
        !isfinite(a) || !isfinite(b) || !isfinite(c) ||
        a <= 0.0 || b <= 0.0 || c <= 0.0 ||
        a > b + c || b > a + c || c > a + b) {
        return 0;
    }

    *perimeter = a + b + c;
    return isfinite(*perimeter);
}

int main(void)
{
    double a;
    double b;
    double c;
    double perimeter;

    errno = 0;
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3 || errno == ERANGE) {
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