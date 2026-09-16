#include <math.h>
#include <stdbool.h>
#include <stdio.h>

static bool roots_are_opposite(double a, double b, double c)
{
    double discriminant;
    double root1;
    double root2;
    double scale;
    double tolerance;

    if (!isfinite(a) || !isfinite(b) || !isfinite(c) || a == 0.0) {
        return false;
    }

    discriminant = fma(b, b, -4.0 * a * c);
    if (!isfinite(discriminant) || discriminant < 0.0) {
        return false;
    }

    root1 = (-b + sqrt(discriminant)) / (2.0 * a);
    root2 = (-b - sqrt(discriminant)) / (2.0 * a);

    if (!isfinite(root1) || !isfinite(root2)) {
        return false;
    }

    scale = fmax(1.0, fmax(fabs(root1), fabs(root2)));
    tolerance = 1e-12 * scale;

    return fabs(root1 + root2) <= tolerance;
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

    puts(roots_are_opposite(a, b, c) ? "Yes" : "No");
    return 0;
}