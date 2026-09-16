#include <math.h>
#include <stdbool.h>
#include <stdio.h>

static bool roots_are_reciprocal(double a, double b, double c)
{
    const double epsilon = 1e-12;
    const double scale = fmax(fabs(a), fabs(c));

    if (!isfinite(a) || !isfinite(b) || !isfinite(c) || a == 0.0) {
        return false;
    }

    if (b * b - 4.0 * a * c < 0.0) {
        return false;
    }

    return fabs(a - c) <= epsilon * fmax(1.0, scale);
}

int main(void)
{
    double a;
    double b;
    double c;

    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (!isfinite(a) || !isfinite(b) || !isfinite(c) || a == 0.0) {
        fputs("Invalid quadratic equation\n", stderr);
        return 1;
    }

    puts(roots_are_reciprocal(a, b, c) ? "Yes" : "No");
    return 0;
}