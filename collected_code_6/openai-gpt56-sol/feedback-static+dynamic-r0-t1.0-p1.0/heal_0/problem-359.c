#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool has_root_twice_the_other(double a, double b, double c)
{
    const double tolerance = 1e-12;
    const double discriminant = b * b - 4.0 * a * c;
    double scale;
    double square_root;
    double root1;
    double root2;

    if (!isfinite(a) || !isfinite(b) || !isfinite(c) || a == 0.0) {
        return false;
    }

    scale = fabs(b * b) + fabs(4.0 * a * c) + 1.0;

    if (discriminant < -tolerance * scale) {
        return false;
    }

    square_root = sqrt(fmax(0.0, discriminant));
    root1 = (-b + square_root) / (2.0 * a);
    root2 = (-b - square_root) / (2.0 * a);

    return fabs(root1 - 2.0 * root2) <=
               tolerance * fmax(1.0, fmax(fabs(root1), fabs(2.0 * root2))) ||
           fabs(root2 - 2.0 * root1) <=
               tolerance * fmax(1.0, fmax(fabs(root2), fabs(2.0 * root1)));
}

int main(void)
{
    double a;
    double b;
    double c;

    if (printf("Enter coefficients a, b, and c: ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (a == 0.0 || !isfinite(a) || !isfinite(b) || !isfinite(c)) {
        fputs("The coefficients must be finite and a must be nonzero.\n", stderr);
        return EXIT_FAILURE;
    }

    if (has_root_twice_the_other(a, b, c)) {
        puts("Yes");
    } else {
        puts("No");
    }

    return EXIT_SUCCESS;
}