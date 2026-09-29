#include <math.h>
#include <stdbool.h>
#include <stdio.h>

static bool roots_are_opposite(double a, double b, double c)
{
    double discriminant;
    double sqrt_discriminant;
    double root1;
    double root2;
    double scale;

    if (!isfinite(a) || !isfinite(b) || !isfinite(c) || a == 0.0) {
        return false;
    }

    discriminant = fma(b, b, -4.0 * a * c);
    if (!isfinite(discriminant) || discriminant < 0.0) {
        return false;
    }

    sqrt_discriminant = sqrt(discriminant);
    root1 = (-b + sqrt_discriminant) / (2.0 * a);
    root2 = (-b - sqrt_discriminant) / (2.0 * a);

    if (!isfinite(root1) || !isfinite(root2)) {
        return false;
    }

    scale = fmax(1.0, fmax(fabs(root1), fabs(root2)));
    return fabs(root1 + root2) <= 1e-12 * scale;
}

int main(void)
{
    double a;
    double b;
    double c;

    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    printf("%s\n", roots_are_opposite(a, b, c) ? "Yes" : "No");
    return 0;
}