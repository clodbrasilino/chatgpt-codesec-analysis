#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool roots_are_opposite(double a, double b, double c)
{
    if (!isfinite(a) || !isfinite(b) || !isfinite(c) || a == 0.0) {
        return false;
    }

    const double scale = fmax(fabs(a), fmax(fabs(b), fabs(c)));
    const double tolerance = 1e-12 * fmax(1.0, scale);

    if (fabs(b) > tolerance) {
        return false;
    }

    return (a > 0.0 && c <= 0.0) || (a < 0.0 && c >= 0.0);
}

int main(void)
{
    double a;
    double b;
    double c;

    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    puts(roots_are_opposite(a, b, c) ? "Yes" : "No");
    return EXIT_SUCCESS;
}