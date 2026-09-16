#include <math.h>
#include <stdbool.h>
#include <stdio.h>

static bool one_root_is_twice_the_other(double a, double b, double c)
{
    const double epsilon = 1e-12;
    double discriminant;
    double root1;
    double root2;
    double scale;

    if (!isfinite(a) || !isfinite(b) || !isfinite(c) || a == 0.0) {
        return false;
    }

    discriminant = b * b - 4.0 * a * c;
    if (!isfinite(discriminant) || discriminant < 0.0) {
        return false;
    }

    root1 = (-b + sqrt(discriminant)) / (2.0 * a);
    root2 = (-b - sqrt(discriminant)) / (2.0 * a);

    if (!isfinite(root1) || !isfinite(root2)) {
        return false;
    }

    scale = fmax(1.0, fmax(fabs(root1), fabs(root2)));

    return fabs(root1 - 2.0 * root2) <= epsilon * scale ||
           fabs(root2 - 2.0 * root1) <= epsilon * scale;
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

    puts(one_root_is_twice_the_other(a, b, c) ? "Yes" : "No");
    return 0;
}