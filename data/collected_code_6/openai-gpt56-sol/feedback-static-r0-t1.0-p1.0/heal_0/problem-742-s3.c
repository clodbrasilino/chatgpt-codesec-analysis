#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int tetrahedron_area(double a, double b, double c, double d,
                            double e, double f, double *area)
{
    double expression;

    if (area == NULL ||
        !isfinite(a) || !isfinite(b) || !isfinite(c) ||
        !isfinite(d) || !isfinite(e) || !isfinite(f) ||
        a <= 0.0 || b <= 0.0 || c <= 0.0 ||
        d <= 0.0 || e <= 0.0 || f <= 0.0) {
        return -1;
    }

    expression =
        4.0 * a * a * b * b * c * c
        - a * a * pow(b * b + c * c - d * d, 2.0)
        - b * b * pow(c * c + a * a - e * e, 2.0)
        - c * c * pow(a * a + b * b - f * f, 2.0)
        + (b * b + c * c - d * d)
        * (c * c + a * a - e * e)
        * (a * a + b * b - f * f);

    if (!isfinite(expression) || expression <= 0.0) {
        return -1;
    }

    *area = sqrt(expression) / 12.0;

    return isfinite(*area) ? 0 : -1;
}

int main(void)
{
    double a;
    double b;
    double c;
    double d;
    double e;
    double f;
    double area;

    if (scanf("%lf %lf %lf %lf %lf %lf", &a, &b, &c, &d, &e, &f) != 6) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (tetrahedron_area(a, b, c, d, e, f, &area) != 0) {
        fputs("Invalid tetrahedron\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}