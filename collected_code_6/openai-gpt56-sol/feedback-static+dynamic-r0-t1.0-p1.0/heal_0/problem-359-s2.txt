#include <math.h>
#include <stdbool.h>
#include <stdio.h>

static bool has_root_twice_the_other(double a, double b, double c)
{
    const double epsilon = 1e-12;
    double discriminant;
    double scale;

    if (!isfinite(a) || !isfinite(b) || !isfinite(c) || a == 0.0) {
        return false;
    }

    discriminant = b * b - 4.0 * a * c;
    scale = fmax(fabs(b * b), fabs(4.0 * a * c));

    return fabs(b * b - 4.5 * a * c) <= epsilon * fmax(1.0, scale) &&
           discriminant >= -epsilon * fmax(1.0, scale);
}

int main(void)
{
    double a;
    double b;
    double c;

    if (printf("Enter coefficients a, b, and c: ") < 0) {
        return 1;
    }

    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    if (a == 0.0) {
        fprintf(stderr, "Coefficient a must be nonzero.\n");
        return 1;
    }

    if (has_root_twice_the_other(a, b, c)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }

    return 0;
}