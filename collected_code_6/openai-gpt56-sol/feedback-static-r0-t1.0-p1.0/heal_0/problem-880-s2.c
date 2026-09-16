#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int quadratic_solution_count(double a, double b, double c, int *count)
{
    double discriminant;
    double tolerance;
    double scale;

    if (count == NULL || !isfinite(a) || !isfinite(b) || !isfinite(c)) {
        return 0;
    }

    scale = fmax(fabs(a), fmax(fabs(b), fabs(c)));
    tolerance = 1e-12 * fmax(1.0, scale);

    if (fabs(a) <= tolerance) {
        *count = fabs(b) <= tolerance ? (fabs(c) <= tolerance ? -1 : 0) : 1;
        return 1;
    }

    discriminant = fma(b, b, -4.0 * a * c);

    if (!isfinite(discriminant)) {
        return 0;
    }

    tolerance = 1e-12 * fmax(1.0, fabs(b * b) + fabs(4.0 * a * c));

    if (discriminant > tolerance) {
        *count = 2;
    } else if (discriminant < -tolerance) {
        *count = 0;
    } else {
        *count = 1;
    }

    return 1;
}

int main(void)
{
    double a;
    double b;
    double c;
    int count;

    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!quadratic_solution_count(a, b, c, &count)) {
        fprintf(stderr, "Unable to determine the number of solutions\n");
        return EXIT_FAILURE;
    }

    if (count < 0) {
        printf("Infinite solutions\n");
    } else {
        printf("%d\n", count);
    }

    return EXIT_SUCCESS;
}