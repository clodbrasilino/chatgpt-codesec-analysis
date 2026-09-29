#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int tetrahedron_volume(double a, double b, double c, double d,
                              double e, double f, double *volume)
{
    if (volume == NULL || !isfinite(a) || !isfinite(b) || !isfinite(c) ||
        !isfinite(d) || !isfinite(e) || !isfinite(f) ||
        a <= 0.0 || b <= 0.0 || c <= 0.0 ||
        d <= 0.0 || e <= 0.0 || f <= 0.0) {
        return 0;
    }

    const double a2 = a * a;
    const double b2 = b * b;
    const double c2 = c * c;
    const double d2 = d * d;
    const double e2 = e * e;
    const double f2 = f * f;

    const double determinant =
        4.0 * a2 * b2 * c2
        - a2 * (b2 + c2 - f2) * (b2 + c2 - f2)
        - b2 * (c2 + a2 - e2) * (c2 + a2 - e2)
        - c2 * (a2 + b2 - d2) * (a2 + b2 - d2)
        + (b2 + c2 - f2) *
          (c2 + a2 - e2) *
          (a2 + b2 - d2);

    if (!isfinite(determinant) || determinant <= 0.0) {
        return 0;
    }

    *volume = sqrt(determinant) / 12.0;
    return isfinite(*volume);
}

int main(void)
{
    double a;
    double b;
    double c;
    double d;
    double e;
    double f;
    double volume;

    if (scanf("%lf %lf %lf %lf %lf %lf", &a, &b, &c, &d, &e, &f) != 6) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!tetrahedron_volume(a, b, c, d, e, f, &volume)) {
        fputs("Invalid tetrahedron\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", volume) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}