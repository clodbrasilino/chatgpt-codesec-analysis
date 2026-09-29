#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int quadratic_solution_count(double a, double b, double c)
{
    double discriminant;
    double tolerance;

    if (!isfinite(a) || !isfinite(b) || !isfinite(c)) {
        return -1;
    }

    if (a == 0.0) {
        if (b != 0.0) {
            return 1;
        }

        return (c == 0.0) ? -2 : 0;
    }

    discriminant = fma(b, b, -4.0 * a * c);

    if (!isfinite(discriminant)) {
        return -1;
    }

    tolerance = 16.0 * DBL_EPSILON *
                fmax(fabs(b * b), fabs(4.0 * a * c));

    if (fabs(discriminant) <= tolerance) {
        return 1;
    }

    return (discriminant > 0.0) ? 2 : 0;
}

int main(void)
{
    double a;
    double b;
    double c;
    int count;

    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    count = quadratic_solution_count(a, b, c);

    if (count == -1) {
        fputs("Invalid coefficients\n", stderr);
        return EXIT_FAILURE;
    }

    if (count == -2) {
        puts("Infinite solutions");
    } else {
        printf("%d\n", count);
    }

    return EXIT_SUCCESS;
}